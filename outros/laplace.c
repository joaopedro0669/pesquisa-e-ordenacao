#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int Laplace(vector<vector<int>> matriz, int ordem, pair<int, int> ignore, bool recursao){
    
    vector<vector<int>> matriz_usada;
    if(recursao){
        matriz_usada.resize(ordem, vector<int>(ordem));
        int a = 0, b = 0;
        for(int i = 0; i < ordem+1; i++){
            if(i != ignore.f){
                for(int j = 0; j < ordem+1; j++){
                    if(j != ignore.s){
                        matriz_usada[a][b] = matriz[i][j];
                        b++;
                    }
                }
                a++;
            }
        }
    }
    else matriz_usada = matriz;
    
    if(ordem == 1) return matriz_usada[0][0];
    
    int soma = 0, multi = -1;
    
    for(int i = 0; i < ordem; i++){
        multi = -multi;
        soma += matriz_usada[0][i] * Laplace(matriz_usada, ordem-1, {0, i}, true) * multi;
    }
    
    return soma;
}

void mostrar(vector<vector<int>> matriz, int ordem){
    for(int i = 0; i < ordem; i++){
	    for(int j = 0; j < ordem; j++){
	        cout << matriz[i][j] << ' ';
	    }
	    cout << '\n';
	}
}

int main() {
	int ordem;
	cin >> ordem;
	vector<vector<int>> matriz(ordem, vector<int>(ordem));
	for(int i = 0; i < ordem; i++){
	    for(int j = 0; j < ordem; j++){
	        cin >> matriz[i][j];
	    }
	}
	//mostrar(matriz, ordem);
	cout << Laplace(matriz, ordem, {0, 0}, false);
    return 0;
}
