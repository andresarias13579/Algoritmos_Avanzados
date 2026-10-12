#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
#include "Paciente.h"

bool ordenarM1(const Paciente &a, const Paciente &b) {
    return a.m1 < b.m1;
}
bool ordenarM2(const Paciente &a, const Paciente &b) {
    return a.m2 < b.m2;
}
bool ordenarM3(const Paciente &a, const Paciente &b) {
    return a.m3 < b.m3;
}
bool ordenarPacientes(const Paciente &a, const Paciente &b) {
    return a.codigo < b.codigo;
}
bool ordenarFinal(vector<int> const &a, const vector<int> &b) {
    return a[0] < b[0];
}

bool estaDisponible(int inicio,int fin,vector<int> intervalo_m1) {
    return fin <= intervalo_m1[0] || inicio >= intervalo_m1[1];
}

void llenarPacientes(vector<Paciente> &pacientes,vector<Paciente> &auxiliar) {
    while (!auxiliar.empty()) {
        Paciente paciente = auxiliar.back();
        auxiliar.pop_back();
        pacientes.push_back(paciente);
    }
}

int imprimirOrdenMaquinas(Paciente paciente) {
    vector<vector<int>> orden;
    paciente.intervalo_m1.push_back(1);
    orden.push_back(paciente.intervalo_m1);
    paciente.intervalo_m2.push_back(2);
    orden.push_back(paciente.intervalo_m2);
    paciente.intervalo_m3.push_back(3);
    orden.push_back(paciente.intervalo_m3);
    sort(orden.begin(), orden.end(), ordenarFinal);
    bool esPrimero = true;
    int termina;
    for (vector<int> m:orden) {
        if (!esPrimero) {
            cout<<" -> ";
        }
        cout<<"M"<<m[2]<<"("<<setw(3)<<m[0]<<"-"<<setw(3) << m[1]<<")";
        termina = m[1];
        esPrimero = false;
    }
    return termina;
}

void mejorOrdenMaquina1(vector<Paciente> &pacientes) {
    vector<Paciente> solucion;
    int tiempo = 0;
    while (!pacientes.empty()) {
        Paciente paciente = pacientes.back();
        pacientes.pop_back();
        int inicio = tiempo;
        int fin = tiempo + paciente.m1;
        paciente.intervalo_m1.push_back(inicio);    //guarda a que hora inicia
        paciente.intervalo_m1.push_back(fin);       //guarda a que hora termina
        solucion.push_back(paciente);
        tiempo = fin;
    }
    while (!solucion.empty()) {
        pacientes.push_back(solucion.back());
        solucion.pop_back();
    }
}
void mejorOrdenMaquina2(vector<Paciente> &pacientes) {
    vector<Paciente> solucion,auxiliar;
    int tiempo = 0;
    while (!pacientes.empty() or !auxiliar.empty()) {
        if (pacientes.empty() and !auxiliar.empty()) {
            tiempo++;
            llenarPacientes(pacientes,auxiliar);
        }
        Paciente paciente = pacientes.back();
        pacientes.pop_back();
        int inicio = tiempo;
        int fin = tiempo + paciente.m2;
        if (estaDisponible(inicio,fin,paciente.intervalo_m1)) {
            paciente.intervalo_m2.push_back(inicio);
            paciente.intervalo_m2.push_back(fin);
            solucion.push_back(paciente);
            llenarPacientes(pacientes,auxiliar);
            tiempo = fin;
        }else auxiliar.push_back(paciente);

    }
    while (!solucion.empty()) {
        pacientes.push_back(solucion.back());
        solucion.pop_back();
    }
}
void mejorOrdenMaquina3(vector<Paciente> &pacientes) {
    vector<Paciente> solucion,auxiliar;
    int tiempo = 0;
    while (!pacientes.empty() or !auxiliar.empty()) {
        if (pacientes.empty() and !auxiliar.empty()) {
            tiempo++;
            llenarPacientes(pacientes,auxiliar);
        }
        Paciente paciente = pacientes.back();
        pacientes.pop_back();
        int inicio = tiempo;
        int fin = tiempo + paciente.m3;
        if (estaDisponible(inicio,fin,paciente.intervalo_m1) and estaDisponible(inicio,fin,paciente.intervalo_m2)) {
            paciente.intervalo_m3.push_back(inicio);
            paciente.intervalo_m3.push_back(fin);
            solucion.push_back(paciente);
            llenarPacientes(pacientes,auxiliar);
            tiempo = fin;
        }else auxiliar.push_back(paciente);

    }
    while (!solucion.empty()) {
        pacientes.push_back(solucion.back());
        solucion.pop_back();
    }
}

int main() {
    vector<Paciente> pacientes{
        {"P1",10,12,15},
        {"P2",8,8,7},
        {"P3",15,5,12},
        {"P4",10,12,7},
        {"P5",8,5,15},
        {"P6",15,8,12},
        {"P7",10,5,15},
        {"P8",8,12,7},
        {"P9",15,8,12},
        {"P10",10,5,7}
    };

    sort(pacientes.begin(), pacientes.end(),ordenarM1);
    mejorOrdenMaquina1(pacientes);

    sort(pacientes.begin(), pacientes.end(),ordenarM2);
    mejorOrdenMaquina2(pacientes);

    sort(pacientes.begin(), pacientes.end(),ordenarM3);
    mejorOrdenMaquina3(pacientes);

    sort(pacientes.begin(), pacientes.end(),ordenarPacientes);

    cout<<"Paciente             Orden de visita                    Termina en"<<endl;
    cout<<"--------  --------------------------------------------  ----------"<<endl;
    int final = 0;
    for (Paciente paciente: pacientes) {
        cout<<paciente.codigo<<"      ";
        int termina = imprimirOrdenMaquinas(paciente);
        cout<<"          t="<<termina<<endl;
        if (termina>=final) final = termina;
    }
    cout<<endl;
    cout<<"Y el makespan seria: "<<final<<" minutos"<<endl;

    return 0;
}