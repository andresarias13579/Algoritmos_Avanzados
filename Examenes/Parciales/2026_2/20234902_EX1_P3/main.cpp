//ARIAS VILLANUEVA EDWIN CARLOS ANDRES - 20234902
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#include "Antena.h"

bool ordenar(const Antena& a, const Antena& b) {
    return a.id > b.id;
}

void buscarCanales(vector<vector<int>> mapa_de_interferencias,vector<Antena> &antenas) {

    int indiceAntena=0;    //canal inicial A
    for (int k=0; k<mapa_de_interferencias.size(); k++) {
        vector<int> interferencias = mapa_de_interferencias[k];
        int canal=1;
        for (int i = 0; i < interferencias.size(); i++) {
            if (interferencias[i] == 1) {   //Verifica si es su vecino
                if (antenas[i].canal == canal) {
                    canal++;
                    i=0;    //se reinicia
                }
            }
        }
        antenas[indiceAntena].canal = canal;
        indiceAntena++;
    }

}

int main() {
    vector<vector<int>> mapa_de_interferencias{
        //     A   B   C   D   E   F   G
        {   0,  1,  1,  1,  0,  0,  0}, //A
        {   1,  0,  1,  0,  1,  0,  0}, //B
        {   1,  1,  0,  0,  0,  1,  0}, //C
        {   1,  0,  0,  0,  0,  0,  1}, //D
        {   0,  1,  0,  0,  0,  0,  0}, //E
        {   0,  0,  1,  0,  0,  0,  0}, //F
        {   0,  0,  0,  1,  0,  0,  0}  //G
    };
    vector<Antena> antenas{
        {'A',0},
        {'B',0},
        {'C',0},
        {'D',0},
        {'E',0},
        {'F',0},
        {'G',0}
    };

    buscarCanales(mapa_de_interferencias, antenas);

    for (Antena a: antenas) {
        cout<<"Antena "<<a.id<<" -> Canal "<<a.canal<<endl;
    }

    return 0;
}