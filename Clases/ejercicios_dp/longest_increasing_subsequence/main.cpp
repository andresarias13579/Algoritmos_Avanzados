#include <iostream>
#include <ranges>
#include <vector>

using namespace std;

int hallarSubsecuencia(vector<int> secuencia,vector<int> &resultado) {
    int n = secuencia.size();
    vector<int> dp(n, 1);           // cada elemento por sí solo ya es subsecuencia de longitud 1
    vector<int> copia(n,-1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (secuencia[j] < secuencia[i]) {
                if (dp[j]+1 > dp[i]) copia[i] = j;
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int longMax = 0;
    for (int i = 0; i < n; i++) longMax = max(longMax, dp[i]);
    // encuentro dónde termina la subsecuencia más larga
    int idxMax = 0;
    for (int i = 1; i < n; i++)
        if (dp[i] > dp[idxMax]) idxMax = i;

    // reconstruyo la secuencia siguiendo los padres hacia atrás
    int actual = idxMax;
    while (actual != -1) {
        resultado.push_back(secuencia[actual]);
        actual = copia[actual];
    }

    return longMax;
}

int main() {
    vector<int> secuencia{-7, 10, 9, 2, 3, 8, 8, 1};
    vector<int> resultado;

    cout<<"La subsecuencia mas larga es de longitud "<< hallarSubsecuencia(secuencia,resultado)<<endl;
    for (int c: resultado) cout<<"  "<<c<<endl;

    return 0;
}