#include <stdio.h>
#include <stdlib.h>

typedef struct elem{
    int valor;
    int qtd;
    struct elem *prox;
    struct elem *adj;

} elem;

elem* CriarElem(int valor){
    elem* novo = malloc(sizeof(elem));
    novo->valor = valor;
    novo->qtd = 0;
    novo->prox = NULL;
    novo->adj = NULL;
    return novo;
}

elem* AddEnd(elem** raiz, int valor){
    elem* novo = CriarElem(valor);
    novo->prox = *raiz;
    *raiz = novo;

    return novo;
}

void AddAdj(elem* no, int peso){
    if(peso != -1){
        elem* novo = CriarElem(peso);
        novo->adj = no->adj;
        no->adj = novo;
        no->qtd++;
    }
}

int VerificaRegular(elem* raiz, int n){
    int ehRegular = 1;
    elem* aux = raiz;
    int grau = n-1;
    while(aux && ehRegular){
        if(aux->qtd == grau || aux->qtd == grau+1)
            aux = aux->prox;
        else ehRegular = 0;
    }
    return ehRegular;
}

void MostraNos(elem* no){
    elem* aux = no;
    while(aux){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
}

void MostraAdj(elem* no){
    elem* aux = no->adj;
    while(aux){
        printf("%d ", aux->valor);
        aux = aux->adj;
    }
}

int main(){
    elem* raiz = NULL;
    int n; scanf("%d", &n);
    elem* add = NULL;
    int peso = 0;
    for(int i = 0; i < n; i++){
        add = AddEnd(&raiz, i);
        for(int j = 0; j < n; j++){
            scanf("%d", &peso);
            AddAdj(add, peso);
        }
        /* MostraNos(raiz);
        printf("\n");
        MostraAdj(add);
        printf("\n"); */
    }
    if(VerificaRegular(raiz, n)) printf("sim\n");
    else printf("nao\n");
    return 0;
}