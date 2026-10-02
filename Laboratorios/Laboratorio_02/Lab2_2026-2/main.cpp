#include <iostream>
#include <iomanip>
using namespace std;

#define N 6          // cantidad de eventos
#define DESCANSO 1   // horas obligatorias de limpieza entre eventos
#define BONO 15      // bono si el siguiente evento empieza justo tras el descanso

/*
 * Estrategia: PROGRAMACIÓN DINÁMICA (tabulación / bottom-up, sin recursión).
 * dp[i]    = máxima ganancia de una agenda cuyo ÚLTIMO evento es el evento i.
 * padre[i] = índice del evento anterior en esa mejor agenda (-1 si i va solo).
 * Recurrencia:
 *   dp[i] = pago[i] + max( 0 , max sobre j<i compatibles de ( dp[j] + bono(j,i) ) )
 *   j es compatible con i si fin[j] + DESCANSO <= ini[i]
 *   bono(j,i) = BONO si fin[j] + DESCANSO == ini[i], si no 0
 * Devuelve el índice del evento donde termina la mejor agenda.
 */
int calcularGanancia(int n, int ini[], int fin[], int pago[], int dp[], int padre[]) {
    for (int i = 0; i < n; i++) {
        dp[i] = pago[i];          // caso base: el evento i solo, sin anteriores
        padre[i] = -1;
        for (int j = 0; j < i; j++) {                  // probamos cada evento anterior j
            if (fin[j] + DESCANSO <= ini[i]) {         // ¿respeta el descanso?
                int bono = 0;
                if (fin[j] + DESCANSO == ini[i])       // ¿empieza justo después del descanso?
                    bono = BONO;
                int candidato = dp[j] + bono + pago[i];
                if (candidato > dp[i]) {               // nos quedamos con el mejor predecesor
                    dp[i] = candidato;
                    padre[i] = j;
                }
            }
        }
    }
    // La agenda óptima termina en el evento con mayor dp
    int mejor = 0;
    for (int i = 1; i < n; i++)
        if (dp[i] > dp[mejor])
            mejor = i;
    return mejor;
}

int main() {
    // Eventos ordenados por hora de fin (datos fijos del enunciado)
    int ini[N]  = {1, 4, 6, 6, 5, 8};
    int fin[N]  = {3, 5, 8, 8, 9, 12};
    int pago[N] = {30, 10, 60, 20, 50, 40};
    int dp[N], padre[N];

    int ultimo = calcularGanancia(N, ini, fin, pago, dp, padre);

    // Mostrar el arreglo de soluciones dp (y padre)
    cout << "Evento  : ";
    for (int i = 0; i < N; i++) cout << setw(5) << i + 1;
    cout << endl << "dp      : ";
    for (int i = 0; i < N; i++) cout << setw(5) << dp[i];
    cout << endl << "padre   : ";
    for (int i = 0; i < N; i++) cout << setw(5) << (padre[i] == -1 ? 0 : padre[i] + 1);
    cout << endl << endl;

    cout << "Ganancia maxima: S/. " << dp[ultimo] << endl;

    // Reconstrucción iterativa de los eventos elegidos (de atrás hacia adelante)
    int sel[N], cant = 0;
    for (int k = ultimo; k != -1; k = padre[k])
        sel[cant++] = k;
    cout << "Eventos elegidos:";
    for (int k = cant - 1; k >= 0; k--)
        cout << " E" << sel[k] + 1;
    cout << endl;
    return 0;
}