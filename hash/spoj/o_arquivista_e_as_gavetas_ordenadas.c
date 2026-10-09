#include <stdio.h>
#include <stdlib.h>

typedef struct elem{
    int valor;
    struct elem* prox;
} elem;

typedef struct gaveta {
    elem* lista;
    int maior_num, *docs_ordenados;
} gaveta;

elem* CriarElem(int num){
    elem* novo = malloc(sizeof(elem));
    novo->valor = num;
    novo->prox = NULL;
    return novo;
}

void inserir(elem** lista, int doc){
    elem* novo = CriarElem(doc);
    novo->prox = *lista;
    *lista = novo;
}

void ordenar(gaveta* gav){
    //obter maior elemento
    int maior = -1;
    elem* aux = gav->lista;
    while(aux){
        if(aux->valor > maior) maior = aux->valor;
        aux = aux->prox;
    }
    gav->maior_num = maior;

    //criar o array e inicializar
    gav->docs_ordenados = calloc(maior+1, sizeof(int));

    //colocar no array ordenado
    aux = gav->lista;
    while(aux){
        gav->docs_ordenados[aux->valor] += 1;
        aux = aux->prox;
    }
}

void mostrar(gaveta gav){
    int tam = gav.maior_num;
    for(int i = 0; i <= tam; i++){
        for(int j = 0; j < gav.docs_ordenados[i]; j++){
            printf("%d ", i);
        }
    }
}

int main(){
    int m, n, doc;
    scanf("%d %d", &m, &n);
    gaveta estante[m];
    //inicializar as gavetas
    for(int i = 0; i < m; i++){
        estante[i].lista = NULL;
        estante[i].maior_num = -1;
        estante[i].docs_ordenados = NULL;
    }

    //colocar documentos na gaveta
    while(n--){
        scanf("%d", &doc);
        inserir(&(estante[doc % m].lista), doc);
    }

    //ordenar e mostrar documentos na gaveta
    for(int i = 0; i < m; i++){
        ordenar(&estante[i]);
        if(estante[i].maior_num > -1){
            printf("Gaveta %d: ", i);
            mostrar(estante[i]);
            printf("\n");
        }
    }
    return 0;
}