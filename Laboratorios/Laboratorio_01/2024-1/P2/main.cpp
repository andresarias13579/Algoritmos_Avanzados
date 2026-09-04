#include <iostream>
#include <string>

using namespace std;

// backtracking: en cada "espacio" entre dígitos, decide si separa o no
void buscarFormaciones(int equipos[], int cantEquipos, string actual, int espacio) {

    // Caso base: ya se decidió en todos los espacios posibles
    if (espacio == cantEquipos - 1) {
        cout << actual << endl;
        return;
    }

    // Rama 1: NO separar (el siguiente dígito se pega directo, sin espacio)
    buscarFormaciones(equipos, cantEquipos, actual + to_string(equipos[espacio + 1]), espacio + 1);

    // Rama 2: SÍ separar (se agrega un espacio en blanco antes del siguiente dígito)
    buscarFormaciones(equipos, cantEquipos, actual + " " + to_string(equipos[espacio + 1]), espacio + 1);
}

int main() {
    int equipos[]{4, 5, 9, 2};
    int cantEquipos = sizeof(equipos) / sizeof(equipos[0]);

    // el string arranca ya con el primer dígito puesto (no hay espacio "antes" del primero)
    string inicial = to_string(equipos[0]);

    buscarFormaciones(equipos, cantEquipos, inicial, 0);

    return 0;
}