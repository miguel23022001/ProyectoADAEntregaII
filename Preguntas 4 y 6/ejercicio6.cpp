#include <bits/stdc++.h>
using namespace std;
using tipo = long long int;
#define INF LLONG_MAX

vector<tipo> cost;
vector<tipo> opt;
vector<tipo> temp;
vector<tipo> p;
vector<tipo> p2;
vector<tipo> numeros;

void prefixSumN();
void prefixSumNMod();
tipo S(int l,int r);
tipo S2(int l, int r);

tipo costoSegmento(int i, int j);
void calcular(int l, int r, int optl, int optr);
tipo particionDinamicaOptimizacion(int n, int k);

int main() {
    int n,k;
    cin>>n;
    //cin>>k;
    k=n-1;

    numeros.resize(n);
    cost.resize(k);
    opt.resize(n,INF);
    temp.resize(n,INF);

    tipo numero;
    for (int i = 0; i < n; ++i) {
        cin>>numero;
        numeros[i] = numero;
    }

    p.resize(n);
    p2.resize(n);

    prefixSumN();
    prefixSumNMod();

    tipo costo = particionDinamicaOptimizacion(n, k);
    //cout<<costo << endl;

    for (int i = 0; i < k; ++i) {
        cout << cost[i] << ' ';
    }

    return 0;
}

void calcular(int l, int r, int optl, int optr){
    if (l > r)
        return;

    int mid = (l + r) >> 1;

    tipo minCost = INF;
    int q = -1;

    for (int k = optl; k <= min(mid, optr); k++) {
        if(minCost > (opt[k] + costoSegmento(k,mid))){
            minCost = opt[k] + costoSegmento(k,mid);
            q = k;
        }
    }

    temp[mid] = minCost;
    int opt = q; 
    calcular(l, mid - 1, optl, opt);
    calcular(mid + 1, r, opt, optr);
}

tipo particionDinamicaOptimizacion(int n, int k) {
    for (int j = 0; j < n; ++j)
        opt[j] = costoSegmento(0,j);

    cost[0] = opt[n - 1];
    //cout << opt[n - 1] << ' ';

    for (int i = 1; i < k; i++) {
        calcular(i, n - 1, i, n - 1);
        opt = temp;

        cost[i] = opt[n - 1];
        //cout << opt[n - 1] << ' ';

    }
    return opt[n - 1];
}

tipo costoSegmento(int i, int j) {
    int m = (i+j) >> 1;
    tipo resultado = S2(i,m) - (i*S(i,m)) + (j*S(m+1,j)) - S2(m+1,j);
    return  resultado;
}

void prefixSumNMod() {
    tipo suma = 0;
    for (int i = 0; i < numeros.size(); ++i) {
        suma += numeros[i]*(i);
        p2[i] = suma;
    }
}

void prefixSumN() {
    tipo suma = 0;
    for (int i = 0; i < numeros.size(); ++i) {
        suma += numeros[i];
        p[i] = suma;
    }
}

tipo S(int l, int r) {
    if(l == 0)
        return p[r];
    return p[r] - p[l-1];
}

tipo S2(int l, int r) {
    if(l == 0)
        return p2[r];
    return p2[r] - p2[l-1];
}
