// MI SOLUCION, NO FUNCIONA DEL TODO XD

 #include <iostream>
 #include <iomanip>

 using namespace std;

 void imprimirMatriz(int matriz[][8]) {
     for (int i = 0; i < 8; i++) {
         for (int j = 0; j < 8; j++) {
             cout<<setw(3)<<matriz[i][j];
         }
         cout<<endl;
     }
 }

 bool buscarRuta(int f,int c,int recorrido,int matriz[][8]) {
     if (c<0 || c>=8 || f<0 || f>=8) {
         return false;
     }
     if (matriz[f][c]!=0) return false;

     matriz[f][c] = recorrido;
     if (recorrido==64) return true;
     recorrido++;

     if (buscarRuta(f,c-1,recorrido,matriz)) return true;    //arriba
     if (buscarRuta(f-1,c+1,recorrido,matriz)) return true;  //arriba - derecha
     if (buscarRuta(f,c+1,recorrido,matriz)) return true;    //derecha
     if (buscarRuta(f+1,c+1,recorrido,matriz)) return true;  //abajo - derecha
     if (buscarRuta(f+1,c,recorrido,matriz)) return true;    //abajo
     if (buscarRuta(f+1,c-1,recorrido,matriz)) return true;  //abajo - izquierda
     if (buscarRuta(f,c-1,recorrido,matriz)) return true;    //izquierda
     if (buscarRuta(f-1,c-1,recorrido,matriz)) return true;  //arriba - izquierda

     matriz[f][c] = 0;
     return false;
 }

 int main() {

     int matriz[][8] {
         {0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0},
         {0,0,0,0,0,0,0,0}
     };

     int f=7,c=4;

     if (!buscarRuta(f,c,1,matriz)) {
         cout<<"No hay una ruta posible"<<endl;
     }else {
         cout<<"Una ruta es: \n"<<endl;
         imprimirMatriz(matriz);
     }
     return 0;
 }

// #include <iostream>
// #include <vector>
//
// using std::vector;
// using std::cout;
// using std::endl;
//
// // === A ===
//
// void imprimir(vector<vector<int>> tablero) {
//     for (const auto &fila : tablero) {
//         for (const auto &col : fila) {
//             cout << col << "\t";
//         }
//         cout << endl;
//     }
// }
//
// bool esValido(const vector<vector<int>> tablero, int x, int y) {
//     return x >= 0 && x < tablero.size() && y >= 0 && y < tablero.size() && tablero[x][y] == -1;
// }
//
// void backtrack(vector<vector<int>> &estado, vector<vector<int>> &respuesta, int x = 4, int y = 7, int contador = 0) {
//     const vector<vector<int>> movs = {
//         {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}
//     };
//
//     estado[x][y] = contador + 1;
//
//     if (contador == estado.size() * estado.size() - 1) {
//         respuesta = estado;
//         return;
//     }
//
//
//     for (const auto &mov : movs) {
//         int nuevoX = x + mov[0];
//         int nuevoY = y + mov[1];
//
//         if (!esValido(estado, nuevoX, nuevoY)) continue;
//
//         backtrack(estado, respuesta, nuevoX, nuevoY, contador + 1);
//
//         if (!respuesta.empty()) {
//             return;
//         }
//
//         estado[x][y] = -1;
//     }
// }
//
//
// vector<vector<int>> solucionar(int N) {
//     vector<vector<int>> tablero(N);
//     for (int i = 0; i < N; i++) {
//         tablero[i] = vector<int>(N, -1);
//     }
//
//     vector<vector<int>> respuesta;
//     backtrack(tablero, respuesta);
//
//     return respuesta;
// }
// int main() {
//     vector<vector<int>> tablero = solucionar(8);
//     imprimir(tablero);
//
//     /**
//     vector<vector<int>> tableroMagico = {
//         {64, 2,  3, 61, 60, 6,  7, 57},
//         {9,  55, 54, 12, 13, 51, 50, 16},
//         {17, 47, 46, 20, 21, 43, 42, 24},
//         {40, 26, 27, 37, 36, 30, 31, 33},
//         {32, 34, 35, 29, 28, 38, 39, 25},
//         {41, 23, 22, 44, 45, 19, 18, 48},
//         {49, 15, 14, 52, 53, 11, 10, 56},
//         {8,  58, 59, 5,  4,  62, 63, 1}
//     };
//
//     bool magico = esMagico(tableroMagico);
//     **/
//
//     // bool magico = esMagico(tablero);
//     // cout << "Es mágico: " << magico;
//
//     return 0;
// }