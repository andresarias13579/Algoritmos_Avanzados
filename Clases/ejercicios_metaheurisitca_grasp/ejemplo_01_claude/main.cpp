#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Proyecto.h"

using namespace std;

void calcularBetaYT(double &beta, double &t,vector<Proyecto> proyectos) {
    double minimo=99999,maximo=0;
    for (Proyecto proyecto : proyectos) {
        double ratio = (double)proyecto.retorno/proyecto.costo;
        if (ratio < minimo) minimo = ratio;
        if (ratio > maximo) maximo = ratio;
    }
    beta = maximo;
    t = minimo;
}
double calcularUmbral(double beta,double t,double alpha) {
    return beta + (double)alpha*(t-beta);
}

vector<Proyecto> armarRCL(vector<Proyecto>proyectos,double umbral) {
    vector<Proyecto> RCL;
    for (Proyecto proyecto : proyectos) {
        double ratio = (double)proyecto.retorno/proyecto.costo;
        if (ratio >= umbral) RCL.push_back(proyecto);
    }
    return RCL;
}

void quitarOpcion(vector<Proyecto> &proyectos,Proyecto opcionAzar) {
    vector<Proyecto> nuevo;
    for (Proyecto proyecto : proyectos) {
        if (proyecto.id!=opcionAzar.id) nuevo.push_back(proyecto);
    }
    proyectos = nuevo;
}
void quitarFueraDePresupuestos(vector<Proyecto> &proyectos,int limite) {
    vector<Proyecto> nuevo;
    for (Proyecto proyecto : proyectos) {
        if (proyecto.costo <= limite) nuevo.push_back(proyecto);
    }
    proyectos = nuevo;
}
int sumar(vector<Proyecto> proyectos) {
    int suma=0;
    for (Proyecto proyecto : proyectos) suma += proyecto.retorno;
    return suma;
}
int sumarCostos(vector<Proyecto> proyectos) {
    int suma=0;
    for (Proyecto proyecto : proyectos) suma += proyecto.costo;
    return suma;
}
bool esMejorSolucion(vector<Proyecto>solucion,vector<Proyecto>mejorSolucion) {
    return sumar(solucion)>sumar(mejorSolucion);
}
Proyecto escogerAlAzar(const vector<Proyecto>& RCL) {
    int indice = rand() % RCL.size();
    return RCL[indice];
}
vector<Proyecto> buscarNoSeleccionados(vector<Proyecto> solucion,vector<Proyecto> proyectos) {
    vector<Proyecto> nuevos;
    for (Proyecto p : proyectos) {
        bool estaEnSolucion = false;
        for (Proyecto s : solucion)
            if (s.id == p.id) estaEnSolucion = true;
        if (!estaEnSolucion) nuevos.push_back(p);
    }
    return nuevos;
}

vector<Proyecto> construir(vector<Proyecto>proyectos,double alpha, int limite) {
    vector<Proyecto> solucion;
    while (!proyectos.empty()) {
        double beta, t;
        calcularBetaYT(beta,t,proyectos);
        double umbral = calcularUmbral(beta,t,alpha);
        vector<Proyecto> RCL = armarRCL(proyectos,umbral);
        Proyecto opcionAzar = escogerAlAzar(RCL);
        solucion.push_back(opcionAzar);
        limite = limite - opcionAzar.costo;
        quitarOpcion(proyectos,opcionAzar);
        quitarFueraDePresupuestos(proyectos,limite);
    }
    return solucion;
}
vector<Proyecto> mejorar(vector<Proyecto> proyectos,int limite,vector<Proyecto> noSeleccionados) {

    int beneficioActual = sumar(proyectos);
    int mejorBeneficio=0;
    vector<Proyecto> mejorSolucion = proyectos;
    for (Proyecto proyecto : proyectos) {
        vector<Proyecto> proyectoSeleccionados = proyectos;
        quitarOpcion(proyectoSeleccionados,proyecto);//aqui quitamos esa wbd
        for (Proyecto suplente: noSeleccionados) {
            proyectoSeleccionados.push_back(suplente);
            int beneficioHipotetico = sumar(proyectoSeleccionados);
            if (sumarCostos(proyectoSeleccionados) <= limite and beneficioHipotetico > beneficioActual) {
                if (beneficioHipotetico>mejorBeneficio) {
                    mejorBeneficio = beneficioHipotetico;
                    mejorSolucion = proyectoSeleccionados;
                }
            }
            proyectoSeleccionados.pop_back();
        }
    }
    return mejorSolucion;
}

vector<Proyecto> GRASP(vector<Proyecto> proyectos, int limite) {
    vector<Proyecto> mejorSolucion;
    for (int i = 0; i < 3; i++) {
        vector<Proyecto> solucion;
        solucion = construir(proyectos,0.5,limite);

        //OPCION 1: esto es para mejorar constantemente, no solo hacer 1 mejora y ya, lo hizo chat
        // while (true) {
        //     vector<Proyecto> noSel = buscarNoSeleccionados(solucion,proyectos);
        //     vector<Proyecto> nueva = mejorar(solucion,limite,noSel);
        //     if (sumar(nueva) <= sumar(solucion)) break;
        //     solucion = nueva;
        // }

        //OPCION 2: esto es lo que yo hice, solo hace una mejora, para este ejercicio basta
        vector<Proyecto> noSeleccionados = buscarNoSeleccionados(solucion,proyectos);
        solucion = mejorar(solucion,limite,noSeleccionados);

        if (esMejorSolucion(solucion,mejorSolucion)) mejorSolucion = solucion;
    }
    return mejorSolucion;
}

int main() {
    vector<Proyecto> proyectos{
        {1, 40, 60},
        {2, 30, 36},
        {3, 25, 40},
        {4, 20, 22},
        {5, 35, 63},
        {6, 15, 18},
        {7, 10, 15}
    };
    srand(time(NULL));
    vector<Proyecto> solucionFactible = GRASP(proyectos,100);

    cout<<"Usamos los proyectos: ";
    for (Proyecto proyecto : solucionFactible) {
        cout<<"P"<<proyecto.id<<"   ";
    }
    cout<<endl;
    cout<<"Retorno total: "<<sumar(solucionFactible)<<endl;
    cout<<"Costo total: "<<sumarCostos(solucionFactible)<<endl;

    return 0;
}