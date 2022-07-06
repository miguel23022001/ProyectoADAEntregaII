#include <bits/stdc++.h>
using namespace std;
using tipo = long long int;
#define INF LLONG_MAX

vector<tipo> p;
vector<tipo> p2;
vector<tipo> numeros;
vector<vector<tipo>> m;

void prefixSumN();
void prefixSumNMod();
tipo S(int l,int r);
tipo S2(int l, int r);

tipo costoSegmento(int i, int j);
tipo particionDinamica(int n, int k);
void imprimir_matriz(vector<vector<tipo>> &m);

int main() {
    int n,k;
    cin>>n;
    //cin>>k;
    k=n-1;

    numeros.resize(n);
    p.resize(n);
    p2.resize(n);

    m.resize(k);
    for (int i = 0; i < k; ++i) {
        m[i].resize(n,INF);
    }

    tipo numero;
    for (int i = 0; i < n; ++i) {
        cin>>numero;
        numeros[i] = numero;
    }

    prefixSumN();
    prefixSumNMod();

    tipo costo = particionDinamica(n,k);
    // cout<<costo << endl;
    // imprimir_matriz(m);
    for (auto & i : m) {
        cout<<i[n-1]<<' ';
    }
    return 0;
}

tipo particionDinamica(int n, int k) {
    for (int j = 0; j < n; ++j)
        m[0][j] = costoSegmento(0,j);

    for (int j = 1; j < n; ++j) {
        for (int i = 1; i < k ; ++i) {
            for (int l = i; l <= j; ++l) {
                m[i][j]=min(m[i][j], m[i-1][l] + costoSegmento(l,j));
            }
        }
    }
    return m[k-1][n-1];
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


void imprimir_matriz(vector<vector<tipo>> &m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); ++j) {
            cout << "(" << i << "," << j << ")" << m[i][j] << ' ';
        }
        cout<<endl;
    }
}
