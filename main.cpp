#include <bits/stdc++.h>
using namespace std;
using tipo = long long int;
#define INF LLONG_MAX

//void imprimir_matriz(vector<vector<tipo>> &m);
tipo particionDinamica(vector<tipo> &numeros, int k, vector<vector<tipo>> &matriz, vector<tipo> &prefixSumN, vector<tipo> &prefixSumMod);
//tipo costoSegmento(int i, int j, vector<tipo> &numeros);

vector<tipo> prefixSumN(vector<tipo> &numeros);
vector<tipo> prefixSumNMod(vector<tipo> &numeros);
tipo S(int l,int r, vector<tipo> &numeros);
tipo S2(int l, int r, vector<tipo> &numeros);
tipo costoSegmento(int i, int j, vector<tipo> &prefixSumN, vector<tipo> &prefixSumMod);

int main() {
    int n,k;
    cin>>n;
    //cin>>k;
    k=n-1;
    vector<tipo> numeros;

    vector<vector<tipo>> m(k,vector<tipo>(n));
    tipo numero;
    for (int i = 0; i < n; ++i) {
        cin>>numero;
        numeros.push_back(numero);
    }

    vector<tipo> p = prefixSumN(numeros);
    vector<tipo> p2 = prefixSumNMod(numeros);

    tipo costo = particionDinamica(numeros,k,m,p,p2);
//    cout<<costo << endl;
//    imprimir_matriz(m);
    for (auto & i : m) {
        cout<<i[n-1]<<' ';
    }
    return 0;
}

tipo particionDinamica(vector<tipo> &numeros, int k, vector<vector<tipo>> &matriz, vector<tipo> &prefixSumN, vector<tipo> &prefixSumMod) {
    for (int j = 0; j < numeros.size(); ++j)
        matriz[0][j] = costoSegmento(0,j,prefixSumN,prefixSumMod);
    for (int j = 1; j < numeros.size(); ++j) {
        for (int i = 1; i < k ; ++i) {
            matriz[i][j] = INF;
            for (int l = i; l <= j; ++l) {
                tipo costoS = costoSegmento(l,j,prefixSumN,prefixSumMod);
                tipo costo = matriz[i-1][l] + costoS;
                if(costo < matriz[i][j])
                    matriz[i][j]=costo;
            }
        }
    }
    return matriz[k-1][numeros.size()-1];
}

//tipo costoSegmento(int i, int j, vector<tipo> &numeros) {
//    tipo resultado = 0;
//    for (int a = i; a <= j; ++a) {
//        tipo uno = (a - i);
//        tipo dos = (j - a);
//        if(uno<dos)
//            resultado += uno*numeros[a];
//        else
//            resultado += dos*numeros[a];
//    }
//    return  resultado;
//}

tipo costoSegmento(int i, int j, vector<tipo> &prefixSumN, vector<tipo> &prefixSumMod) {
    int m = (i+j)/2;
    tipo resultado = S2(i,m,prefixSumMod) - (i*S(i,m,prefixSumN)) + (j*S(m+1,j,prefixSumN)) - S2(m+1,j,prefixSumMod);
    return  resultado;
}

vector<tipo> prefixSumNMod(vector<tipo> &numeros) {
    vector<tipo> p2(numeros.size());
    tipo suma = 0;
    for (int i = 0; i < numeros.size(); ++i) {
        suma += numeros[i]*(i);
        p2[i] = suma;
    }
    return p2;
}

//void imprimir(vector<tipo>& numeros) {
//    for (tipo numero : numeros) {
//        cout << numero << ' ';
//    }
//}

vector<tipo> prefixSumN(vector<tipo> &numeros) {
    vector<tipo> p(numeros.size());
    tipo suma = 0;
    for (int i = 0; i < numeros.size(); ++i) {
        suma += numeros[i];
        p[i] = suma;
    }
    return p;
}

tipo S(int l, int r, vector<tipo> &numeros) {
    if(l == 0)
        return numeros[r];
    return numeros[r] - numeros[l-1];
}

tipo S2(int l, int r, vector<tipo> &numeros) {
    if(l == 0)
        return numeros[r];
    return numeros[r] - numeros[l-1];
}


//void imprimir_matriz(vector<vector<double>> &m) {
//    for (int i = 0; i < m.size(); i++) {
//        for (int j = 0; j < m[0].size(); ++j) {
//            cout << "(" << i+1 << "," << j+1 << ")" << m[i][j] << ' ';
//        }
//        cout<<endl;
//    }
//}


//