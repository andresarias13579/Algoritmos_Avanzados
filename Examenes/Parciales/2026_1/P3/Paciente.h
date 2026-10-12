//
// Created by Andres on 11/10/2026.
//

#ifndef P3_PACIENTE_H
#define P3_PACIENTE_H

struct Paciente {
    string codigo;
    int m1;
    int m2;
    int m3;
    vector<int> intervalo_m1;
    vector<int> intervalo_m2;
    vector<int> intervalo_m3;
};

#endif //P3_PACIENTE_H
