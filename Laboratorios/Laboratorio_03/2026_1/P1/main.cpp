#include <algorithm>
#include <iostream>
#include <vector>

#include "Tarea.h"

using namespace std;

bool compara(const Tarea &a, const Tarea &b) {
    double ratioA = (double)a.peso/a.tiempo;
    double ratioB = (double)b.peso/b.tiempo;

    return ratioA < ratioB or (ratioA == ratioB and a.tiempo > b.tiempo);
}

void ordenarSegunSmith (vector<Tarea> tareas,vector<Tarea> &tareasOrdenadas){
    sort(tareas.begin(),tareas.end(),compara);

    while(!tareas.empty()) {
        Tarea tarea = tareas.back();
        tareas.pop_back();

        tareasOrdenadas.push_back(tarea);
    }
}

int main() {
    vector<Tarea> tareas{
        {'A',4,20},
        {'B',2,10},
        {'C',5,15},
        {'D',3,18}
    };

    vector<Tarea> tareasOrdenadas;

    ordenarSegunSmith(tareas,tareasOrdenadas);

    int completioTime = 0;
    double costoTotalPonderado = 0;
    cout<<"=========================================="<<endl;
    cout<<"ORDENAMIENTO FINAL SEGUN LA REGLA DE SMITH"<<endl;
    cout<<"=========================================="<<endl;
    for (Tarea tarea :tareasOrdenadas) {
        completioTime += tarea.tiempo;
        cout<<"Tarea: "<<tarea.id<<endl;
        cout<<"Tiempo de procesamiento: "<<tarea.tiempo<<endl;
        cout<<"Ratio: "<<(double)tarea.peso/tarea.tiempo<<endl;
        cout<<"Completion Time: "<<completioTime<<endl;
        cout<<"Costo Ponderado: "<<tarea.peso*completioTime<<endl;
        cout<<"--------------------------"<<endl;
        costoTotalPonderado +=  tarea.peso*completioTime;
    }
    cout<<"COSTO TOTAL PONDERADO: "<<costoTotalPonderado<<endl;
    return 0;
}