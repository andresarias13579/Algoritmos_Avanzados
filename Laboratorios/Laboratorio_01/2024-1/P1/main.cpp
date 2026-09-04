#include <iostream>
#include <iomanip>

#define N 10

using namespace std;

bool diferenciaValida(int pedido[],int canEnPedido,int diferenciaMax) {
    if (canEnPedido == 1) return true;
    for (int i = 0; i < canEnPedido; ++i) {
        for (int j = i+1; j < canEnPedido; ++j) {
            if (abs(pedido[i] - pedido[j]) <= diferenciaMax) return true;
        }
    }
    return false;
}

void imprimirSolucion(int pedido[],int canEnPedido) {
    int bandera = true;
    for (int i = 0; i < canEnPedido; ++i) {
        if (bandera) {
            cout<<"{";
            bandera = false;
        }else cout<<",";
        cout << setw(2)<<pedido[i] ;
    }
    cout << "}"<<endl;
}

bool buscarPedidos(int arrCortes[],int cantCortes, bool usado[], int i, int pesoActual, int pedido[], int canEnPedido, int P, int K) {
    if (pesoActual == P) {
        if (diferenciaValida(pedido,canEnPedido,K)) {
             imprimirSolucion(pedido,canEnPedido);
            return true;
        }
        return false;
    }
    if (i == cantCortes) {
        return false;
    }

    bool encontrado = false;

    if (usado[i] == false and (pesoActual+arrCortes[i]) <= P) {
        pedido[canEnPedido] = arrCortes[i];
        usado[i] = true;
        encontrado = buscarPedidos(arrCortes,cantCortes,usado,i+1,pesoActual + arrCortes[i],pedido,canEnPedido + 1,P, K);

        if (!encontrado) {
            usado[i] = false;
        }
    }

    if (!encontrado) {
        encontrado = buscarPedidos(arrCortes,cantCortes,usado,i+1, pesoActual,pedido,canEnPedido ,P, K);
    }

    return encontrado;
}

int main() {
    int arrCortes[]{2,8,9,6,7,6};
    int numCortes = sizeof(arrCortes)/sizeof(arrCortes[0]);
    int P = 15;
    int K = 4;
    int pedido[10]{},numPedidos = 0;
    bool usado[numCortes]{};
    bool sigueBuscando = true;
    while (sigueBuscando) {
        for (int j = 0; j < 10; j++) pedido[j] = 0; // limpiar pedido temporal
        sigueBuscando = buscarPedidos(arrCortes, numCortes, usado, 0, 0, pedido, 0, P, K);
        if (sigueBuscando) numPedidos++;
    }

    return 0;
}