#include <iostream>
#include <vector>

using namespace std;
#include "Proyectos.h"

int calcularGanancia(vector<Proyecto> proyectos) {
    int suma = 0;
    for (Proyecto proyecto : proyectos) suma += proyecto.ganancia;
    return suma;
}
int calcularCosto(vector<Proyecto> proyectos) {
    int suma = 0;
    for (Proyecto proyecto : proyectos) suma += proyecto.costo;
    return suma;
}
void quitamosFueraDePresupuesto(vector<Proyecto> &proyectos,int presupuesto) {
    vector<Proyecto> nuevo;
    for (Proyecto proyecto : proyectos) {
        if (proyecto.costo<=presupuesto) nuevo.push_back(proyecto);
    }
    proyectos = nuevo;
}
void hallarBeyaYTau(vector<Proyecto> proyectos,double &beta,double &tau) {
    double min=9999,max=0;
    for (Proyecto proyecto : proyectos) {
        double ratio = (double)proyecto.ganancia/proyecto.costo;
        if (ratio>max) max=ratio;
        if (ratio<min) min=ratio;
    }
    beta=max;
    tau=min;
}
bool cumpleConPredecesores(vector<Proyecto> escogidos,Proyecto proyecto) {
    vector<bool> cumple(proyecto.predecesores.size(),false);
    int i=0;
    for (int predecesor : proyecto.predecesores) {
        for (Proyecto proyecto : escogidos) if (proyecto.id==predecesor) cumple[i]=true;
        i++;
    }
    bool todoCumplen=true;
    for (bool c:cumple) if (c==false) todoCumplen=false;

    return todoCumplen;
}
void quitarProyecto(vector<Proyecto> &proyectos, int id) {
    vector<Proyecto> nuevo;
    for (Proyecto p : proyectos) if (p.id != id) nuevo.push_back(p);
    proyectos = nuevo;
}
vector<Proyecto> filtrarFactibles(vector<Proyecto> proyectos, vector<Proyecto> escogidos, int presupuesto) {
    vector<Proyecto> factibles;
    for (Proyecto p : proyectos)
        if (p.costo <= presupuesto and cumpleConPredecesores(escogidos, p)) factibles.push_back(p);
    return factibles;
}
vector<Proyecto> armamosRCL(vector<Proyecto> candidatos,double umbral) {
    vector<Proyecto> RCL;
    for (Proyecto p : candidatos) {
        double ratio = (double)p.ganancia / p.costo;
        if (ratio >= umbral) RCL.push_back(p);
    }
    return RCL;
}
Proyecto escogerAlAzar(vector<Proyecto> &RCL) {
    int indice = rand()%RCL.size();
    Proyecto proyecto = RCL[indice];
    vector<Proyecto> nuevo;
    for (Proyecto escogido : RCL) if (proyecto.id!=escogido.id) nuevo.push_back(escogido);
    RCL = nuevo;
    return proyecto;
}
bool solucionValida(vector<Proyecto> solucion, int presupuesto) {
    if (calcularCosto(solucion) > presupuesto) return false;
    for (Proyecto p : solucion)
        if (!cumpleConPredecesores(solucion, p)) return false;
    return true;
}


vector<Proyecto> construirSolucion(vector<Proyecto>proyectos,int presupuesto,double alpha) {
    vector<Proyecto> solucion;
    while (true) {
        vector<Proyecto> candidatos = filtrarFactibles(proyectos, solucion, presupuesto);
        if (candidatos.empty()) break;              // ya no hay nada factible
        double beta, tau;
        hallarBeyaYTau(candidatos, beta, tau);      // solo sobre factibles
        double umbral = beta - alpha * (beta - tau);
        vector<Proyecto> RCL = armamosRCL(candidatos, umbral);
        Proyecto elegido = escogerAlAzar(RCL);
        presupuesto -= elegido.costo;
        solucion.push_back(elegido);
        quitarProyecto(proyectos, elegido.id);      // no se puede elegir dos veces
    }
    return solucion;
}
vector<Proyecto> buscarNoSeleccionado(vector<Proyecto> solucion,vector<Proyecto> proyectos) {
    vector<Proyecto> noSeleccionados;
    for (Proyecto proyecto : proyectos) {
        bool noEscogigo = true;
        for (Proyecto solu:solucion) if (proyecto.id==solu.id) noEscogigo = false;
        if (noEscogigo) noSeleccionados.push_back(proyecto);
    }
    return noSeleccionados;
}
vector<Proyecto> mejorarSolucion(vector<Proyecto> solucion, vector<Proyecto> noSeleccionados, int presupuesto) {
    int mejorGanancia = calcularGanancia(solucion);
    vector<Proyecto> mejorSolucion = solucion;      // si no hay mejora, se devuelve la original
    for (int i = 0; i < solucion.size(); i++) {
        Proyecto sale = solucion[i];
        for (Proyecto suplente : noSeleccionados) {
            solucion[i] = suplente;
            int gananciaHipotetica = calcularGanancia(solucion);
            if (gananciaHipotetica > mejorGanancia and solucionValida(solucion, presupuesto)) {
                mejorGanancia = gananciaHipotetica;
                mejorSolucion = solucion;
            }
        }
        solucion[i] = sale;                         // restauramos para probar la siguiente posición
    }
    return mejorSolucion;
}

vector<Proyecto> GRASP(vector<Proyecto> proyectos,int presupuesto,int iteraciones,double alpha) {
    vector<Proyecto> mejorSolucion;
    for (int i = 0; i < iteraciones; i++) {
        vector<Proyecto> solucion;
        solucion = construirSolucion(proyectos,presupuesto,alpha);
        vector<Proyecto> noSeleccionados = buscarNoSeleccionado(solucion,proyectos);
        solucion = mejorarSolucion(solucion,noSeleccionados,presupuesto);
        if (calcularGanancia(solucion) > calcularGanancia(mejorSolucion)) mejorSolucion = solucion;
    }
    return mejorSolucion;
}

int main() {
    int iteraciones=1000,presupuesto=400;
    double alpha=0.3;
    vector<Proyecto> proyectos{
        {1,100,200},
        {2,50,300,{1}},
        {3,150,300,{1}},
        {4,50,400},
        {5,50,200,{4}},
        {6,150,800,{2,4}},
        {7,100,250}
    };
    srand(time(NULL));

    vector<Proyecto> solucion = GRASP(proyectos,presupuesto,iteraciones,alpha);

    cout<<"Proyectos seleccionados: ";
    for (Proyecto proyecto : solucion) {
        cout<<"P"<<proyecto.id<<"    ";
    }
    cout<<endl;
    cout<<"Beneficio Total: "<<calcularGanancia(solucion)<<endl;
    cout<<"Costo Total: "<<calcularCosto(solucion)<<endl;

    return 0;
}