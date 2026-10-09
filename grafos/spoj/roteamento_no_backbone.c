#include <stdio.h>
#include <stdlib.h>

typedef struct vertice {
    int valor;
    struct vertice *adj, *prox;
} vertice;

typedef struct elem {
    int valor;
    int origem;
    //int vez;
    struct elem *prox;
} elem;

typedef struct dados{
    int valor, origem;
} dados;

int visitado[1010];
int funfando[1010];
//int caminho[5010];

vertice* CriarVertice(int valor){
    vertice* novo = malloc(sizeof(vertice));
    novo->valor = valor;
    novo->adj = novo->prox = NULL;
    return novo;
}

elem* CriarElem(int origem, int valor){
    elem* novo = malloc(sizeof(elem));
    novo->valor = valor;
    novo->origem = origem;
    //novo->vez = vez;
    novo->prox = NULL;
    return novo;
}

void AddElem(vertice** head, int valor){
    if(*head){
        vertice* aux = *head;
        while(aux->prox) aux = aux->prox;
        aux->prox = CriarVertice(valor);
    }
    else *head = CriarVertice(valor);
}

void AddAdj(vertice* head, int vert, int valor){
    vertice* aux = head;
    while(aux->valor != vert) aux = aux->prox;
    if(aux->adj){
        vertice* aux2 = aux->adj;
        vertice* novo = CriarVertice(valor);
        if(aux2->valor > valor){
            novo->adj = aux2;
            aux->adj = novo;
        }
        else{
            while(aux2->adj && aux2->adj->valor < valor) aux2 = aux2->adj;
            novo->adj = aux2->adj;
            aux2->adj = novo;
        }
    }
    else{
        aux->adj = CriarVertice(valor);
    }
}

vertice* BuscaVertice(vertice* head, int valor){
    vertice* aux = head;
    while(aux->valor != valor) aux = aux->prox;
    return aux;
}

elem* BuscaElem(elem* head, int valor){
    elem* aux = head;
    while(aux && aux->valor != valor) aux = aux->prox;
    return aux;
}

void push(elem** head, int origem, int valor){
    if(*head){
        elem* aux = *head;
        while(aux->prox) aux = aux->prox;
        aux->prox = CriarElem(origem, valor);
    }
    else *head = CriarElem(origem, valor);
}

dados pop(elem** head){
    if(*head){
        elem *aux = *head;
        *head = aux->prox;
        dados valores;
        valores.valor = aux->valor;
        valores.origem = aux->origem;
        //valores.vez = aux->vez;
        free(aux);
        return valores;
    }
    dados t = {-1, -1};
    return t;
}

void empilha(elem** head, int valor){
    elem *novo = CriarElem(0, valor);
    novo->prox = *head;
    *head = novo;
}

int desempilha(elem** head){
    elem* aux = *head;
    *head = aux->prox;
    int valor = aux->valor;
    free(aux);
    return valor;
}

void MostrarAdj(vertice* vert){
    vertice* aux = vert->adj;
    while(aux) {
        printf("%d ", aux->valor);
        aux = aux->adj;
    }
}

void MostrarGrafo(vertice *head){;
    vertice* aux = head;
    while(aux){
        printf("%d -> ", aux->valor);
        MostrarAdj(aux);
        printf("\n");
        aux = aux->prox;
    }
}

void LimparCaminho(int n){
    for(int i = 0; i <= n; i++){
        visitado[i] = 0;
    }
}

void MostrarCaminho(elem* head, int inicio, int final){
    elem* aux = BuscaElem(head, final);
    elem* pilha = NULL;
    int valor = final;
    if(aux){
        while(valor){
            empilha(&pilha, valor);
            aux = BuscaElem(head, aux->origem);
            if(aux) valor = aux->valor;
            else valor = 0;
        }
        while(pilha){
            printf("%d ", desempilha(&pilha));
        }
        printf("\n");
    }
    else printf("DESTINO INALCANCAVEL\n");
}

elem* dfs(vertice* grafo, int inicio, int final){
    vertice *atual, *aux;
    elem* fila = NULL;
    elem* caminho = NULL;
    push(&caminho, 0, inicio);
    push(&fila, 0, inicio);
    dados d = pop(&fila);
    visitado[inicio] = 1;
    while(d.valor != -1 && d.valor != final){
        atual = BuscaVertice(grafo, d.valor);
        aux = atual->adj;
        while(aux){
            if(!visitado[aux->valor] && funfando[aux->valor]){
                push(&fila, atual->valor, aux->valor);
                push(&caminho, atual->valor, aux->valor);
                visitado[aux->valor] = 1;
            }
            aux = aux->adj;
        }
        d = pop(&fila);
    }
    return caminho;
}


void Solve(vertice* head, int n){
    char op[5]; int a, b;
    while(getchar() != '\n');
    scanf("%s", op);
    if(op[0] == 'F'){
        scanf("%d", &a);
        funfando[a] = 0;
    }
    else if(op[0] == 'V'){
        scanf("%d", &a);
        funfando[a] = 1;
    }
    else if(op[0] == 'P'){
        scanf("%d %d", &a, &b);
        LimparCaminho(n);
        elem* caminho = dfs(head, a, b);
        MostrarCaminho(caminho, a, b);
    }
    else{
        printf("Nao foi.");
    }
}

int main(){
    int n, m, q;
    vertice* head = NULL;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &q);
    for(int i = 1; i <= n; i++){
        funfando[i] = 1;
        visitado[i] = 0;
        AddElem(&head, i);
    }
    
    int a, b;
    for(int i = 1; i <= m; i++){
        scanf("%d %d", &a, &b);
        AddAdj(head, a, b);
        AddAdj(head, b, a);
        
    }

    //MostrarGrafo(head);

    for(int i = 0; i < q; i++)
        Solve(head, n);

    return 0;
}