#include <stdio.h>
#include <stdlib.h>

typedef struct avl {
    int valor;
    int fb;
    int alt;
    int qne;
    int qnd;
    struct avl *esq, *dir;
} avl;

avl* criar(int chave){
    avl* novo = malloc(sizeof(avl));
    novo->valor = chave;
    novo->alt = novo->fb = novo->qne = novo->qnd = 0;
    novo->esq = novo->dir = NULL;
    return novo;
}

int getalt(avl* no){
    if(no) return no->alt;
    return -1;
}

void UptInfo(avl* no){
    if(no){
        int esq = getalt(no->esq);
        int dir = getalt(no->dir);
        no->alt = (esq > dir) ? esq + 1 : dir + 1;
        no->fb = esq - dir;
    }
}

avl *rotacao_esq(avl *desbal)
{
    avl *filho = desbal->dir;
    avl *neto = filho->esq;
    filho->esq = desbal;
    desbal->dir = neto;

    desbal->fb = filho->fb = 0;
    UptInfo(desbal);
    UptInfo(filho);
    UptInfo(neto);
    return filho;
}

avl *rotacao_dir(avl *desbal)
{

    avl *filho = desbal->esq;
    avl *neto = filho->dir;
    filho->dir = desbal;
    desbal->esq = neto;

    desbal->fb = filho->fb = 0;
    UptInfo(desbal);
    UptInfo(filho);
    UptInfo(neto);
    return filho;
}

avl *rotacao_esq_dir(avl *desbal)
{
    avl *filho = desbal->esq;
    avl *neto = filho->dir;
    avl *nova_raiz_subarvore;

    desbal->esq = rotacao_esq(filho);
    nova_raiz_subarvore = rotacao_dir(desbal);

    // acertar pai dos nós

    if (neto->fb > 0) // inseriu na esq do neto
    {

        desbal->fb = -1;
        neto->fb = filho->fb = 0;
    }
    else
    {
        if (neto->fb < 0) // inseriu na dir do neto
        {
            filho->fb = 1;
            neto->fb = desbal->fb = 0;
        }
        if (neto->fb == 0)
        {
            desbal->fb = filho->fb = 0;
        }
    }
    return nova_raiz_subarvore;
}

avl *rotacao_dir_esq(avl *desbal)
{
    avl *filho = desbal->dir;
    avl *neto = filho->esq;
    avl *nova_raiz_subarvore = NULL;

    desbal->dir = rotacao_dir(filho);
    nova_raiz_subarvore = rotacao_esq(desbal);

    if (neto->fb > 0)
    {
        filho->fb = neto->fb = 0;
        desbal->fb = 1;
    }
    else
    {
        if (neto->fb < 0)
        {
            desbal->fb = neto->fb = 0;
            filho->fb = -1;
        }
        else
        {
            desbal->fb = filho->fb = 0;
        }
    }
    return nova_raiz_subarvore;
}

// if (candidato->fb == -2 || candidatao->fb == +2)

avl *rotacao_geral(avl *desbal)
{
    avl *nova_raiz_subarvore;
    if (desbal->fb == 2)
    {
        if (desbal->esq->fb == -1)
            nova_raiz_subarvore = rotacao_esq_dir(desbal);
        else
            nova_raiz_subarvore = rotacao_dir(desbal);
    }
    else if(desbal->fb == -2) // -2
    {
        if (desbal->dir->fb == 1)
            nova_raiz_subarvore = rotacao_dir_esq(desbal);
        else
            nova_raiz_subarvore = rotacao_esq(desbal);
    }
    else nova_raiz_subarvore = desbal;

    return nova_raiz_subarvore;
}

avl* inserir(avl* raiz, int chave){
    if(!raiz)
        return criar(chave);
    else {
        if(chave < raiz->valor)
            raiz->esq = inserir(raiz->esq, chave);
        else if(chave > raiz->valor)
            raiz->dir = inserir(raiz->dir, chave);
        UptInfo(raiz);
        
        return rotacao_geral(raiz); 
    }
}

int UptQtFilhos(avl* raiz){
    if(!raiz)
        return 0;
    raiz->qne = UptQtFilhos(raiz->esq);
    raiz->qnd = UptQtFilhos(raiz->dir);
    return raiz->qne + raiz->qnd + 1;
}

void mostrar(avl* raiz, int esp){
    if(raiz){
        mostrar(raiz->dir, esp+1);
        for(int i = 0; i < esp; i++) printf("   ");
        printf("[%d]%d(%d)\n", raiz->alt, raiz->valor, raiz->fb);
        mostrar(raiz->esq, esp+1);
    }
}

void emordem(avl* raiz){
    if(raiz){
        emordem(raiz->esq);
        printf("[%d]%d(%d) ", raiz->qne, raiz->valor, raiz->qnd);
        emordem(raiz->dir);
    }
}

void Solve(){
    int chave = 0;
    avl* raiz = NULL;
    while(chave != -1){
        scanf("%d", &chave);
        if(chave != -1) raiz = inserir(raiz, chave);
    }
    UptQtFilhos(raiz);
    emordem(raiz);
    printf("\n");
}

int main(){
    // int chave = 0;
    // avl* raiz = NULL;
    // while(chave != -1){
    //     scanf("%d", &chave);
    //     system("clear");
    //     if(chave != -1) raiz = inserir(raiz, chave);
    //     printf("Arvore com %d:\n", chave);
    //     mostrar(raiz, 0);
    // }
    // system("clear");
    // UptQtFilhos(raiz);
    // mostrar(raiz, 0);
    // emordem(raiz);

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        Solve();
    }
    return 0;
}