//
// Created by Andres on 5/11/2026.
//

#ifndef P1_PROYECTOS_H
#define P1_PROYECTOS_H
#include <vector>

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    vector<int> predecesores;
};

#endif //P1_PROYECTOS_H
