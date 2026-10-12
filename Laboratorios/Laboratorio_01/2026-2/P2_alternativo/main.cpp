#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<int>> direcciones {
    {-1, 0},   // 12: arriba
    {-1, 1},   // 1:30: arriba-derecha
    { 0, 1},   // 3: derecha
    { 1, 1},   // 4:30: abajo-derecha
    { 1, 0},   // 6: abajo
    { 1,-1},   // 7:30: abajo-izquierda
    { 0,-1},   // 9: izquierda
    {-1,-1}    // 10:30: arriba-izquierda
};

void imprimirRuta(vector<vector<char>> ruta, int nroSobrevivientes) {
    for (vector<char> r : ruta) {
        for (char t : r) {
            cout<<setw(3)<<t;
        }
        cout<<endl;
    }
    cout<<"Encontrando "<<nroSobrevivientes<<" grupos de sobrevivientes"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
}

void buscarSobrevivientesBacktrack(int actualX,int actualY,int X,int Y,int &nroSobrevivientes,vector<vector<char>>terreno,
    vector<vector<char>> &ruta,char letra) {
    if (actualX<0 || actualX>=X || actualY<0 || actualY>=Y) return;   //por si se sale
    if (terreno[actualX][actualY] == '*') { //aqui encontramos un obstaculo
        ruta[actualX][actualY] = '*';
        return;
    }
    if (ruta[actualX][actualY] != ' ') return;    //con esto omitimos a los qeu visitamos
    if (terreno[actualX][actualY] == '+') nroSobrevivientes++; //encontramos un sobreviviente
    if (actualX==X-1 && actualY==Y-1) { //caso base
        ruta[actualX][actualY] = letra;
        imprimirRuta(ruta,nroSobrevivientes);
        ruta[actualX][actualY] = ' ';
        return;
    }
    for (int i=0;i<8;i++) {
        ruta[actualX][actualY] = letra;

        int siguienteX = actualX + direcciones[i][0];
        int siguienteY = actualY + direcciones[i][1];
        buscarSobrevivientesBacktrack(siguienteX,siguienteY,X,Y,nroSobrevivientes,terreno,ruta,letra+1);

        ruta[actualX][actualY] = ' ';
    }

    if (terreno[actualX][actualY] == '+') nroSobrevivientes--;
}

int main() {
    vector<vector<char>> terreno{
        {' ',' ',' ','*','*'},
        {' ',' ','+','*','+'},
        {' ',' ','*',' ',' '},
        {' ','+','+',' ',' '},
        {' ','*','*',' ','*'},
        {' ','*','*','+','*'},
        {'+','*',' ','*','+'},
        {'*','*','*','*',' '},
        {' ',' ','+',' ',' '}
    };
    vector<vector<char>> ruta{
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' '}
    };

    int nroSobrevivientes=0,N=9,M=5;

    buscarSobrevivientesBacktrack(0,0,N,M,nroSobrevivientes,terreno,ruta,'A');

    return 0;
}