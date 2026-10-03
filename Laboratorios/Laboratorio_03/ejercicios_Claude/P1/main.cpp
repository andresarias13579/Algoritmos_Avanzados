#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int calcularLongitud(vector<int> barra) {
    int longitud = 0;
    for (int trozo : barra) {
        longitud += trozo;
    }
    return longitud;
}

void obtenerBarras(vector<int> encargos,int longitudMAX, vector<vector<int>> &barrasObtenidas) {

    while (!encargos.empty()) {
        sort(encargos.begin(), encargos.end());
        vector<int> nuevaBarra;
        vector<int> noUsados;
        while (calcularLongitud(nuevaBarra) <= longitudMAX and !encargos.empty()) {
            int trozo = encargos.back();
            encargos.pop_back();
            int longitud = calcularLongitud(nuevaBarra);
            if (trozo + longitud > longitudMAX) {
                noUsados.push_back(trozo);
            }
            else {
                nuevaBarra.push_back(trozo);
            }
        }
        barrasObtenidas.push_back(nuevaBarra);
        for (int trozo : noUsados) encargos.push_back(trozo); //con esto vuelve a llenar los encargos
    }
}

int main() {
    vector<int> encargos{6,6,5,5,4},encargos2{13,8,12,11,10,9,7,6,5,4,3,2},encargos3{14,14,7,7,7,7,6,6,6,6,5,5,5,5};
    int L1 = 10, L2 = 20,L3=15;
    vector<vector<int>> barras;

    obtenerBarras(encargos2, L2, barras);

    int numero = 1;
    for (vector<int> barra : barras) {
        cout<<"Barra "<<numero<<": [";
        bool esPrimero = true;
        int total = 0;
        for (int trozo : barra) {
            if (!esPrimero) cout<<",";
            else esPrimero = false;
            cout<<trozo;
            total+=trozo;
        }
        cout<<"] ";
        if (total == L2) cout<<"->  usa "<<total<<", sin desperdicio"<<endl;
        else cout<<"->  usa "<<total<<", desperdicio = "<<L2-total<<endl;
        numero++;
    }
    cout<<"Total: "<<numero-1<<" barras"<<endl;

    return 0;
}