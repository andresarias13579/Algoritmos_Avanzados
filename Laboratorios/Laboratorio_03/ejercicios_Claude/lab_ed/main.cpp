#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct opcion {
    int fila;
    int columna;
    int valor;
    int diferencia;
};

bool compara(opcion a, opcion b) {
    return a.diferencia < b.diferencia;
}

bool visitado(vector<vector<int>> usados, int fila, int columna) {
    return usados[fila][columna] == 1;
}

void solve(vector<vector<int>> matriz, int objetivo) {

    int n = matriz.size();

    int fila = 0;
    int columna = 0;

    vector<vector<int>> usados(
        n,
        vector<int>(n, 0)
    );

    while (true) {

        cout << "Estoy en: "
             << matriz[fila][columna]
             << endl;

        // Encontré el número
        if (matriz[fila][columna] == objetivo) {

            cout << "Numero encontrado" << endl;
            return;
        }

        // Marco actual como visitado
        usados[fila][columna] = 1;

        vector<opcion> opciones;

        // Arriba
        if (fila - 1 >= 0 &&
            !visitado(usados, fila - 1, columna)) {

            int valor = matriz[fila - 1][columna];

            opciones.push_back({
                fila - 1,
                columna,
                valor,
                abs(valor - objetivo)
            });
        }

        // Abajo
        if (fila + 1 < n &&
            !visitado(usados, fila + 1, columna)) {

            int valor = matriz[fila + 1][columna];

            opciones.push_back({
                fila + 1,
                columna,
                valor,
                abs(valor - objetivo)
            });
        }

        // Izquierda
        if (columna - 1 >= 0 &&
            !visitado(usados, fila, columna - 1)) {

            int valor = matriz[fila][columna - 1];

            opciones.push_back({
                fila,
                columna - 1,
                valor,
                abs(valor - objetivo)
            });
        }

        // Derecha
        if (columna + 1 < n &&
            !visitado(usados, fila, columna + 1)) {

            int valor = matriz[fila][columna + 1];

            opciones.push_back({
                fila,
                columna + 1,
                valor,
                abs(valor - objetivo)
            });
        }

        // No hay más movimientos
        if (opciones.empty()) {
            cout << "No se encontro el numero" << endl;
            return;
        }

        // La opción con menor diferencia queda primero
        sort(
            opciones.begin(),
            opciones.end(),
            compara
        );

        // Principio voraz:
        // tomo el vecino que parece mas cercano al objetivo
        fila = opciones[0].fila;
        columna = opciones[0].columna;
    }
}

int main() {

    vector<vector<int>> matriz = {
        {1, 8, 17, 21, 36},
        {6, 14, 28, 33, 38},
        {9, 16, 29, 35, 41},
        {10, 20, 30, 37, 45},
        {13, 31, 32, 43, 50}
    };

    int objetivo = 29;

    solve(matriz, objetivo);

    return 0;
}


// #include <iostream>
// using namespace std;
//
// /* Estrategia: búsqueda recursiva "en escalera" desde la esquina superior derecha.
//    Como las filas crecen hacia la derecha y las columnas hacia abajo:
//    - Si el valor actual == objetivo        -> lo encontré.
//    - Si el valor actual > objetivo         -> todo lo que está debajo en esa columna
//                                               es aún mayor, descarto la columna (col - 1).
//    - Si el valor actual < objetivo         -> todo lo que está a la izquierda en esa fila
//                                               es aún menor, descarto la fila (fila + 1).
//    Cada llamada elimina una fila o una columna: máximo 2n llamadas -> O(n). */
// #include <iostream>
// #include <vector>
// using namespace std;

/* Estrategia VORAZ: empiezo en la esquina superior derecha (0, n-1).
   En cada paso tomo la decisión localmente óptima e irrevocable:
   - valor == objetivo -> lo encontré.
   - valor >  objetivo -> todo lo de abajo en esa columna es aún mayor:
                          descarto la columna (me muevo a la izquierda).
   - valor <  objetivo -> todo lo de la izquierda en esa fila es aún menor:
                          descarto la fila (me muevo hacia abajo).
   Cada paso elimina una fila o una columna -> máximo 2n pasos -> O(n).
   No necesito matriz de visitados: nunca regreso a una celda. */
// bool solve(const vector<vector<int>> &matriz, int objetivo) {
//     int n = matriz.size();
//     int fila = 0;
//     int columna = n - 1;
//
//     while (fila < n && columna >= 0) {
//         int valor = matriz[fila][columna];
//         cout << "Estoy en: " << valor << endl;
//
//         if (valor == objetivo)
//             return true;
//
//         if (valor > objetivo)
//             columna--;      // descarto la columna
//         else
//             fila++;         // descarto la fila
//     }
//     return false;           // me salí de la matriz: no está
// }
//
// int main() {
//     vector<vector<int>> matriz = {
//         {1,  8,  17, 21, 36},
//         {6,  14, 28, 33, 38},
//         {9,  16, 29, 35, 41},
//         {10, 20, 30, 37, 45},
//         {13, 31, 32, 43, 50}
//     };
//
//     int objetivos[] = {29, 18, 36};
//     for (int objetivo : objetivos) {
//         if (solve(matriz, objetivo))
//             cout << "Numero " << objetivo << " encontrado\n" << endl;
//         else
//             cout << "No se encontro el numero " << objetivo << "\n" << endl;
//     }
//     return 0;
// }