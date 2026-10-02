#include <iostream>
#include <vector>

using namespace std;

void agregarSolucion(vector<vector<int>> &soluciones, int moneda) {
    for (vector<int> &solucion : soluciones) {
        if (solucion[0] == moneda) {
            solucion[1]++;
            return;
        }
    }
    vector<int> solucion;
    solucion.push_back(moneda);
    solucion.push_back(1);
    soluciones.push_back(solucion);
}

int sumar(vector<vector<int>> soluciones) {
    int suma = 0;
    for (vector<int> solucion : soluciones) {
        suma += solucion[0]*solucion[1];
    }
    return suma;
}

bool cumple(vector<vector<int>> soluciones,int montoSolicitado) {
    return sumar(soluciones) == montoSolicitado;
}

int buscarOpcionFactible(int montoSolicitado,vector<int> monedas,int cantMonedas,vector<vector<int>> &soluciones) {
    int total = 0;
    while (!monedas.empty() and !cumple(soluciones,montoSolicitado)) {
        int moneda = monedas.back();
        if (montoSolicitado >= moneda + sumar(soluciones)) {
            agregarSolucion(soluciones,moneda);
            total++;
        }else monedas.pop_back();
    }
    if (monedas.empty() and !cumple(soluciones,montoSolicitado)) return -1;
    return total;
}

int main() {

    vector<int> monedas{1,3,4};
    int cantMonedas = monedas.size();
    int montoSolicitado = 6;

    vector<vector<int>> soluciones;

    int totalMonedasUtilizadas = buscarOpcionFactible(montoSolicitado,monedas,cantMonedas,soluciones);

    if (totalMonedasUtilizadas != -1) {
        cout<<"Se usaron "<<totalMonedasUtilizadas<<" monedas"<<endl;
        cout<<"----------------------"<<endl;
        for (vector<int> solu : soluciones) {
            cout<<"Se uso "<<solu[1]<<" monedas de "<<solu[0]<<endl;
        }
    }else {
        cout<<"No hay solucion"<<endl;
    }


    return 0;
}