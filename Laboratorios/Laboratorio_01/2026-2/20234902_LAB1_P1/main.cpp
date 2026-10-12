//ARIAS VILLANUEVA EDWIN CARLOS ANDRES - 20234902
#include <iostream>

enum VERTICES{A,B,C,D,E};
#define MAX_VERTICES 5

using namespace std;

void imprimirSolucion(int *solucion) {
    int cant = 0;
    for (int i=0; solucion[i+1]; i++) cant++;
    cant = cant+2; //esto porque el A es 0 y no lo cuenta

    bool inicio = true;
    for (int i=0; i<cant; i++) {
        char letra = 'A' + solucion[i];
        if (!inicio) cout<<" -> ";
        inicio = false;
        cout<<letra;
    }
}

bool todoVisitado(bool visitado[],int cantVertices) {
    for (int i=0; i<cantVertices; i++) {
        if (!visitado[i]) return false;
    }
    return true;
}

bool cumpleHamiltoniano( int conexiones[][MAX_VERTICES],int i,int cantVertices,bool visitado[], int anterior,
    int *solucion,int numSolucion) {
    if (visitado[i] == true) {
        if (conexiones[anterior][0] == 1 and todoVisitado(visitado,cantVertices)) {
            solucion[numSolucion] = i;
            return true;
        }
        return false;
    }

    visitado[i] = true;
    solucion[numSolucion] = i;

    //con esto nos desplazamos
    for (int j=0; j<cantVertices; j++) {
        if (conexiones[i][j] == 1) {
            if (cumpleHamiltoniano(conexiones, j, cantVertices,visitado,i,solucion,numSolucion+1)) return true;
        }
    }

    visitado[i] = false;
    solucion[numSolucion] = 0;
    return false;
}

int main() {
    //aqui son las conexiones de los vertices (aristas). Es una matriz con A hasta los E datos
    int conexiones[][MAX_VERTICES] {
        //  A B C D E
        {0,1,1,1,1}, //A
        {1,0,1,0,1}, //B
        {1,1,0,1,0}, //C
        {0,0,1,0,1}, //D
        {1,1,0,1,0}  //E
    };
    // int conexiones[][MAX_VERTICES] {
    //     //  A B C D E
    //     {0,1,1,0,0}, //A
    //     {1,0,1,0,0}, //B
    //     {1,1,0,1,1}, //C
    //     {0,0,1,0,1}, //D
    //     {0,0,1,1,0}  //E
    // };
    char vertice[]{'A','B','C','D','E'}; //esto es nada mas para saber el numero de vertices
    int numVertices = sizeof(conexiones)/sizeof(conexiones[0]);
    bool visitado[MAX_VERTICES]{};
    int solucion[20]{};
    if (!cumpleHamiltoniano( conexiones,A,numVertices,visitado,0,solucion,0)) {
        cout<<"NO SE PUEDE FORMAR EL CICLO HAMILTONIANO"<<endl;
    }else imprimirSolucion(solucion);

    return 0;
}