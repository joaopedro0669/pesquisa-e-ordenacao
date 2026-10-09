#include <stdio.h>
#include <stdlib.h>
 
typedef struct no {
    int valor;
    int alt;
    int fb;
    struct no *esq;
    struct no *dir;
} no;
 
no* Criar(int value){
    no* novo = malloc(sizeof(no));
    novo->valor = value;
    novo->alt = 0;
    novo->fb = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}
 
int getAlt(no* n){
    if(!n) return -1;
    return n->alt;
}
 
void UpdateInfo(no* n){
    int esq = getAlt(n->esq);
    int dir = getAlt(n->dir);
    n->alt = 1 + ((esq > dir) ? esq : dir);
    n->fb = esq - dir;
}
 
void Inserir(no** inicio, int value){
    if(*inicio){
        if(value < (*inicio)->valor) Inserir(&(*inicio)->esq, value);
        else if(value > (*inicio)->valor) Inserir(&(*inicio)->dir, value);
        else return;
        UpdateInfo(*inicio);
    }
    else *inicio = Criar(value);
}
 
int isAVL(no* n){
    if(!n) return 1;
    if(n->fb > 1 || n->fb < -1) return 0;
    if(isAVL(n->esq) && isAVL(n->dir)) return 1;
    return 0;
}
 
void Solve(){
    no* raiz = NULL;
    int n = 1;
    while(n != -1){
        scanf("%d", &n);
        if(n != -1) Inserir(&raiz, n);
    }
    if(isAVL(raiz)) printf("sim\n");
    else printf("nao\n");
}
 
int main(){
    int n = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) Solve();
    return 0;
} 