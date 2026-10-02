#include <iostream>
#include <vector>

using namespace std;

int cantidadMax(vector<int> monedas,vector<int> dp) {
    dp[0] = 0; dp[1] = monedas[0];  //condiciones base
    for(int i=2;i<dp.size();i++) {
        dp[i] = max(monedas[i-1] + dp[i-2], dp[i-1]);
    }
    return dp.back();
}

int main() {

    vector<int> monedas {5,1,2,10,6,2};
    vector<int> dp(monedas.size() +1 , 0);

    cout<<"La cantidad maxima de monedas que podemos obtener sin que sean adyacentes es: "
        <<cantidadMax(monedas,dp)<<endl;

    return 0;
}