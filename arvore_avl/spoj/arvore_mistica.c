#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    int alt;
    struct no *esq;
    struct no *dir;
    struct no* pai;
} no;

no* Criar(int value){
    no* novo = malloc(sizeof(no));
    novo->valor = value;
    novo->alt = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    return novo;
}

int GetAlt(no* raiz){
    return (raiz) ? raiz->alt : -1;
}

void UpdateAlt(no* raiz){
    int esq = GetAlt(raiz->esq);
    int dir = GetAlt(raiz->dir);
    raiz->alt = 1 + ((esq > dir) ? esq : dir);
}

no* Inserir(no *raiz, int value){
    if(raiz){
        if(value < raiz->valor) {
            raiz->esq = Inserir(raiz->esq, value);
            raiz->esq->pai = raiz;
        }
        else if(value > raiz->valor) {
            raiz->dir = Inserir(raiz->dir, value);
            raiz->dir->pai = raiz;
        }
        UpdateAlt(raiz);
        return raiz;
    }
    else return Criar(value);
}

int GetAltNo(no* raiz, int value){
    no* aux = raiz;
    while(aux){
        if(aux->valor == value) return aux->alt;
        else if(value < aux->valor) aux = aux->esq;
        else aux = aux->dir;
    }
    return -1;
}

int GetDif(no* raiz, int a, int b){
    int n1 = GetAltNo(raiz, a);
    int n2= GetAltNo(raiz, b);
    if(n1 < 0 || n2 < 0) return -1;

    return (n1 - n2 > 0) ? n1 - n2 : n2 - n1;
}

void mostrar(no* raiz, int esp){
    if(raiz){
        mostrar(raiz->dir, esp+1);
        for(int i = 0; i < esp; i++) printf("\t");
        printf("%d(%d)\n", raiz->valor, raiz->alt);
        mostrar(raiz->esq, esp+1);
    }
}

no* Procura(no* raiz, int value){
    no* aux = raiz;
    while(aux && aux->valor != value){
        if(value < aux->valor) aux = aux->esq;
        else aux = aux->dir;
    }
    return aux;
}

int ProcuraDist(no* raiz, int a, int b){
    int dist1 = 0, dist2 = 0;
    no* raiz1 = Procura(raiz, a);
    no* raiz2 = Procura(raiz, b);
    if(!raiz1 || !raiz2) return -1;
    while(raiz1 != raiz2){
        if(raiz1->alt < raiz2->alt){
            raiz1 = raiz1->pai;
            dist1++;
        }
        else if(raiz1->alt > raiz2->alt){
            raiz2 = raiz2->pai;
            dist2++;
        }
        else {
            raiz1 = raiz1->pai;
            raiz2 = raiz2->pai;
            dist1++;
            dist2++;
        }
    }
    return dist1 + dist2;
}

int main(){
    int n, q, a, b;
    no* raiz = NULL;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &a);
        raiz = Inserir(raiz, a);
        //mostrar(raiz, 0);
    }
    //mostrar(raiz, 0);
    scanf("%d", &q);
    for(int i = 0; i < q; i++){
        scanf("%d %d", &a, &b);
        int dist = ProcuraDist(raiz, a, b);
        if(dist == -1) printf("Nao encontrado\n");
        else printf("%d\n", dist);
    }
    return 0;
}