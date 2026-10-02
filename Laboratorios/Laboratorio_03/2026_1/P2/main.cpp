#include <iostream>
#include <vector>

using namespace std;
#include "Ciudad.h"

int obtenerMejorRuta(vector<int> &rutas,int &gasolina,vector<Ciudad> &visitados) {
    int mejorRuta = -1;
    int mayorGasto = 0;
    for (int i=0; i<rutas.size(); i++) {
        if (rutas[i] <= gasolina and visitados[i].visitado == false and rutas[i]!=0) {
            if (rutas[i] > mayorGasto) {
                mejorRuta = i;
                mayorGasto = rutas[i];
            }
        }
    }
    if (mejorRuta!=-1) gasolina = gasolina - rutas[mejorRuta];
    return mejorRuta;
}

bool todosVisitados(vector<Ciudad> visitados) {
    for (Ciudad ciudad : visitados) {
        if (ciudad.visitado == false) return false;
    }
    return true;
}

void ordenar(vector<vector<int>> rutas,vector<Ciudad>visitados,int gasolina,int inicio,int fin) {
    int actual = inicio;
    visitados[actual].visitado = true;
    int gasolinaInicial = gasolina;
    cout<<actual;
    while (!todosVisitados(visitados)) {
        if (actual == fin) {
            cout<<endl;
            cout<<"Si pudo llegar"<<endl;
            return;
        }

        int mejorDireccion = obtenerMejorRuta(rutas[actual],gasolina,visitados);
        if (mejorDireccion == -1) {
            break;
        }else {
            cout<<"->"<<mejorDireccion;
            actual = mejorDireccion;
            if (visitados[actual].tieneGrifo == true) gasolina = gasolinaInicial;
            visitados[actual].visitado = true;
        }
    }
    cout <<endl;
    cout<<"NO PUDO LLEGAR"<<endl;
}

int main() {
    vector<vector<int>> rutas{
        {0,4,7,5,0},
        {4,0,3,2,6},
        {7,3,0,4,7},
        {5,2,4,0,3},
        {0,6,7,3,0}
    };
    vector<Ciudad> visitados(5,{false,false});
    visitados[0].tieneGrifo = true;
    visitados[2].tieneGrifo = true;

    int gasolina = 10, inicio = 0, fin = 4;

    ordenar(rutas,visitados,gasolina,inicio,fin);

    return 0;
}