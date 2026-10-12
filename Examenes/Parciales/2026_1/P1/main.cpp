#include <iostream>

using namespace std;
#include "Ruta.h"
#include <vector>

void mejorRutaBacktrack(int fila,int columna,vector<int> pesos,vector<int> valores,vector<vector<int>>distancias,int distanciaMax,
                        int pesoMax,vector<bool> &visitados,Ruta ruta,Ruta &mejorRuta) {
    int distCierre = ruta.sumaDistancia + distancias[fila][0];
    if (distCierre <= distanciaMax && ruta.sumaValor > mejorRuta.sumaValor) {
        mejorRuta = ruta;
        mejorRuta.sumaDistancia = distCierre;
        mejorRuta.direccion.push_back(0);
    }

    for (int i = 1; i < (int)distancias.size(); i++) {
        if (visitados[i]) continue;
        if (ruta.sumaPeso + pesos[i] > pesoMax) continue;                    // poda por peso
        if (ruta.sumaDistancia + distancias[fila][i] > distanciaMax) continue;       // poda por autonomía

        // elegir
        visitados[i] = true;
        ruta.sumaPeso += pesos[i];
        ruta.sumaValor += valores[i];
        ruta.sumaDistancia += distancias[fila][i];
        ruta.direccion.push_back(i);

        // explorar
        mejorRutaBacktrack(i,columna, pesos, valores, distancias, distanciaMax, pesoMax, visitados,
            ruta, mejorRuta);

        // deshacer
        ruta.direccion.pop_back();
        ruta.sumaDistancia -= distancias[fila][i];
        ruta.sumaValor -= valores[i];
        ruta.sumaPeso -= pesos[i];
        visitados[i] = false;
    }
}

int main() {
    vector<vector<int>> dist{
        {0,10,15,20},
        {10,0,35,25},
        {35,35,0,30},
        {20,25,30,0}
    };
    int D=60,W=15;
    vector<int> w{0,5,10,4}, v{0,25,40,15};
    vector<bool> visitados(dist.size(),false);
    Ruta ruta,mejorRuta;
    ruta.sumaPeso=0;
    ruta.sumaValor=0;
    ruta.sumaDistancia = 0;
    ruta.direccion.push_back(0);
    mejorRuta.sumaPeso=0;
    mejorRuta.sumaValor=0;
    mejorRuta.sumaDistancia = 0;

    mejorRutaBacktrack(0,0,w,v,dist,D,W,visitados,ruta,mejorRuta);

    bool esPrimero = true;
    cout<<"===RESULTADO==="<<endl;
    cout<<"Maxima importancia obtenida: "<<mejorRuta.sumaValor<<endl;
    cout<<"Ruta optima seguida: "<<endl;
    for (int r : mejorRuta.direccion) {
        if (!esPrimero) cout<<"->";
        else esPrimero = false;
        cout<<r;
    }

    return 0;
}