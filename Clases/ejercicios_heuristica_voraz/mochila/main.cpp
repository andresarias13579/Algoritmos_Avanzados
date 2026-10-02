#include <algorithm>
#include <iostream>
#include <vector>

#include "Item.h"

using namespace std;

void cambiarItem(Item &a,Item &b) {
    Item aux;
    aux = a;
    a = b;
    b = aux;
}

void ordenarPorRatio(vector<Item> &mochila) {
    for (int i = 0; i < mochila.size()-1; i++) {
        for (int j = i+1; j < mochila.size(); j++) {
            double ratioI = (double)mochila[i].valor/mochila[i].peso;
            double ratioJ = (double)mochila[j].valor/mochila[j].peso;
            if (ratioI > ratioJ or ratioI == ratioJ and mochila[i].peso > mochila[j].peso) {
                cambiarItem(mochila[i],mochila[j]);
            }
        }
    }
}

int sumarPeso(const vector<Item> &mochila ) {
    int suma =0 ;
    for (Item item : mochila) {
        suma += item.peso;
    }
    return suma;
}

bool comparaRatio(const Item &a, const Item &b) {
    double ratioI = (double)a.valor/a.peso;
    double ratioJ = (double)b.valor/b.peso;
    return ratioI < ratioJ or ratioI == ratioJ and a.peso < b.peso;
}

void buscarBuenaAlternativa(vector<Item> mochila,int numeroObjetos,int capacidadMaxima, vector<Item> &objetosSeleccionados) {
    // ordenarPorRatio(mochila);
    sort(mochila.begin(), mochila.end(),comparaRatio );
    while (!mochila.empty()) {
        Item item = mochila.back();
        mochila.pop_back();
        if (item.peso + sumarPeso(objetosSeleccionados) <= capacidadMaxima) {
            objetosSeleccionados.push_back(item);
        }
    }
}

int main() {
    vector<Item> mochila {
        {1,12,4},
        {2,2,2},
        {3,1,1},
        {4,1,2},
        {5,4,10}
    };

    int numeroObjetos = sizeof(mochila)/sizeof(mochila[0]);
    int capacidadMaxima = 15;

    vector<Item> objetosSeleccionados;

    buscarBuenaAlternativa(mochila,numeroObjetos,capacidadMaxima,objetosSeleccionados);

    int beneficioTotal = 0, pesoTotal = 0;
    cout << "Los objetos seleccionados fueron: "<< endl;
    for (Item item : objetosSeleccionados) {
        cout << item.id<< "   ";
        beneficioTotal += item.valor;
        pesoTotal += item.peso;
    } cout << endl;

    cout<<"Peso total: "<<pesoTotal<<endl;
    cout<<"Beneficio total: "<<beneficioTotal<<endl;

    return 0;
}