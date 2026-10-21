//ARIAS VILLANUEVA EDWIN CARLOS ANDRES - 20234902
#include <iostream>
#include <vector>

using namespace std;
#include "Equipos.h"

int sumar(Equipo equipo,vector<int> horas) {
    int suma = 0;
    for (int proyecto: equipo.proyectos) suma+=horas[proyecto-1];
    return suma;
}

bool proyectoImcompatible(int proyecto, vector<vector<int>>icompatibilidades,Equipo equipo) {
    int duplaIncompatible = 0;
    for (vector<int> i : icompatibilidades) {
        if (i[0] == proyecto+1) duplaIncompatible = i[1];
        if (i[1] == proyecto+1) duplaIncompatible = i[0];
        if (duplaIncompatible != 0) {
            for (int k : equipo.proyectos) {
                if (k == duplaIncompatible) return true;
            }
            duplaIncompatible = 0;
        }
    }
    return false;
}

bool encontrarSolucion(int N,int M,vector<int> horas, vector<vector<int>>incompatibilidades,vector<Equipo> &equipos,
    int cargaPorEquipo, int equipoActual ,vector<bool> usados) {

    if(sumar(equipos[0],horas) == cargaPorEquipo and sumar(equipos[1],horas) == cargaPorEquipo
        and sumar(equipos[2],horas) == cargaPorEquipo) return true; //caso base

    if (sumar(equipos[equipoActual],horas)==cargaPorEquipo) equipoActual++; //pasamos al siguiente equipo

    for (int i=0;i<N;i++) {
        int horasProyecto = sumar(equipos[equipoActual],horas);
        if (horasProyecto + horas[i] > cargaPorEquipo) continue;    //verificamos si es que sobrepasa
        if (proyectoImcompatible(i,incompatibilidades,equipos[equipoActual]))   //verificamos compatibilidad
            continue;
        if (usados[i] == true) continue;    //verificamos si ya se uso

        //agregamos
        usados[i] = true;
        equipos[equipoActual].proyectos.push_back(i+1);
        //exploramos
        if (encontrarSolucion(N,M,horas,incompatibilidades,equipos,cargaPorEquipo,equipoActual,usados))
            return true;
        //quitamos
        equipos[equipoActual].proyectos.pop_back();
        usados[equipoActual] = false;

    }

    return false;
}

int main() {
    int N=6;
    int M=2;
    vector<int> horas {3,5,4,4,3,2};
    vector<vector<int>> incompatibilidades{
        {1,2},
        {3,4},
    };
    // vector<vector<int>> incompatibilidades{
    //     {1,3},
    //     {2,6},
    // };
    vector<Equipo> equipos {
        {'A'},
        {'B'},
        {'C'}
    };
    int cargaTotal =0;
    vector<bool> usados(N,false);
    for(int i=0;i<N;i++) cargaTotal+=horas[i];
    if (cargaTotal%3==0 and
        encontrarSolucion(N,M,horas,incompatibilidades,equipos,cargaTotal/3,0,usados)) {
        for (Equipo equipo : equipos) {
            cout<<"Equipo "<<equipo.id<<": ";
            for (int proyecto: equipo.proyectos) {
                cout<<proyecto<<" ";
            }
            cout<<endl;
        }
        cout<<"Carga por equipo: "<<cargaTotal/3<<endl;
    }else {
        cout<<"IMPOSIBLE"<<endl;
    }

    return 0;
}