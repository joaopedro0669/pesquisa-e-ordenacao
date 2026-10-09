#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct nod
{
    void* info;
    struct nod *ant, *prox;
};
typedef struct nod Nod;

struct listad
{
    Nod* ini;
    Nod* fim;
};
typedef struct listad Listad;

struct pagina
{
    int folha;
    int qtdeChaves;
    struct pagina *pai;
    Listad *listaChaves;
    struct pagina *direita;
};
typedef struct pagina Pagina;

struct arvoreb{
    Pagina *raiz;
    int ordem;
    int altura;
};
typedef struct arvoreb Arvoreb;

struct chave{
    int valorChave;
    Pagina *filho;
};
typedef struct chave Chave;

Listad *cria_listad();
Nod *cria_nod(void* info);
Listad* insere_inicio_listad(Listad *L, void* info);
Listad* insere_fim_listad(Listad *L, void* info);
Nod* remove_inicio_listad(Listad *L);
Nod* remove_fim_listad(Listad *L);
Listad* libera_listad(Listad *L);
Listad* divide_lista(Listad *L, int qtde);
void imprime_listad(Listad *L);
Arvoreb *cria_arvoreb(int ordem);
Pagina *cria_pagina();
Chave *cria_chave(int ch);
Chave *get_chave(Nod *aux);
Pagina *encontra_folha(Arvoreb *T, int num_chave);
Pagina *insere_chave_na_pagina(Pagina *pagina1, Chave *nova_chave);
Pagina *cria_nova_raiz(Chave *chave_subir, Pagina *filho_esq, Pagina *filho_dir);
Pagina *divide_pagina(Pagina *pagina_a_dividir);
void insere_arvoreb(Arvoreb *T, int chave_int);
void em_ordem(Pagina *raiz);
void mostrar_em_ordem(Arvoreb *T);
Pagina *libera_pagina(Pagina *pag_aux);
Pagina* libera_todas_paginas(Pagina *raiz);
Arvoreb *libera_arvoreb(Arvoreb *T);

Listad *cria_listad()
{

    Listad *L = (Listad *)malloc(sizeof(Listad));
    L->fim = L->ini = NULL;
    return L;
}

Nod *cria_nod(void* info)
{
    Nod *novo = (Nod *)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    novo->info = info;
    return novo;
}

Listad* insere_inicio_listad(Listad *L, void* info)
{
    Nod *novo = cria_nod(info);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else
    {
        if (L->ini == NULL)
            L->ini = L->fim = novo;
        else
        {
            novo->prox = L->ini;
            L->ini->ant = novo;
            L->ini = novo;
        }
    }
    return L;
}


Listad* insere_fim_listad(Listad *L, void* info)
{
    Nod *novo = cria_nod(info);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else
    {
        if (L->ini == NULL)
            L->ini = L->fim = novo;
        else
        {
            novo->ant = L->fim;
            L->fim->prox = novo;
            L->fim = novo;
        }
    }
    return L;
}


Nod* remove_inicio_listad(Listad *L)
{
    Nod* aux = NULL;
    if (L != NULL && L->fim != NULL) //caso haja elemento
    {
        aux = L->ini;
        if (L->ini == L->fim)
        {   
            L->ini = L->fim = NULL;
        }
        else
        {
            L->ini = L->ini->prox;
            L->ini->ant = NULL;
        }
    }
    return aux;
}

Nod* remove_fim_listad(Listad *L)
{
    Nod* aux = NULL;
    if (L != NULL && L->fim != NULL) //caso haja elemento
    {
        aux = L->fim;
        if (L->ini == L->fim)
        {   
            L->ini = L->fim = NULL;
        }
        else
        {
            L->fim = L->fim->ant;
            L->fim->prox = NULL;
        }
    }
    return aux;
}

Listad* libera_listad(Listad *L)
{
    Nod *aux;
    while (L->ini != NULL)
    {   
        aux = L->ini;
        free(aux->info);
        L->ini = L->ini->prox;
        free(aux);
    }
    L->fim = NULL;
    free(L);
    return NULL;
}

Listad* divide_lista(Listad *L, int qtde)
{
    Listad *L2 = cria_listad();
    Nod* aux = L->ini;
    int i = 1;

    while (i < qtde)
    {
        i++;
        aux = aux->prox;
    }

    L2->ini = aux->prox;
    L2->fim = L->fim;

    L->fim = aux;
    
    L2->ini->ant = NULL;
    L->fim->prox = NULL;

    return L2;
}

void imprime_listad(Listad *L){
    Nod* aux = L->ini;
    while(aux){
        printf("%d ", *((int*)aux->info));
        aux = aux->prox;
    }
    printf("\n");
}

Arvoreb *cria_arvoreb(int ordem)
{
    Arvoreb *T = malloc(sizeof(Arvoreb));
    T->altura = 0;
    T->ordem = ordem;
    T->raiz = NULL;
    return T;
}

Pagina *cria_pagina()
{
    Pagina *p = malloc(sizeof(Pagina));
    p->direita = p->pai = NULL;
    p->qtdeChaves = 0;
    p->folha = 1;
    p->listaChaves = cria_listad();
    return p;
}

Chave *cria_chave(int ch)
{
    Chave *c = malloc(sizeof(Chave));
    c->filho = NULL;
    c->valorChave = ch;
    return c;
}

Chave *get_chave(Nod *aux)
{
    return (Chave *)(aux->info);
}

Pagina *encontra_folha(Arvoreb *T, int num_chave)
{
    Pagina *aux_pag = T->raiz;

    Nod *aux_nod;

    while (!aux_pag->folha) // aux_pagina == 0 ou != 1
    {
        aux_nod = aux_pag->listaChaves->ini;
        while (aux_nod != NULL && get_chave(aux_nod)->valorChave < num_chave)
            aux_nod = aux_nod->prox;

        if (aux_nod == NULL)
            aux_pag = aux_pag->direita;
        else
            aux_pag = get_chave(aux_nod)->filho;
    }

    return aux_pag;
}

Pagina *insere_chave_na_pagina(Pagina *pagina1, Chave *nova_chave)
{

    if (pagina1 == NULL)
    {
        pagina1 = cria_pagina();
    }
    Nod *aux = pagina1->listaChaves->ini;

    if (aux == NULL)
    {
        pagina1->listaChaves = insere_inicio_listad(pagina1->listaChaves, nova_chave);
    }
    else
    {
        if (nova_chave->valorChave < get_chave(aux)->valorChave)
        {
            pagina1->listaChaves = insere_inicio_listad(pagina1->listaChaves, nova_chave);
        }
        else if (nova_chave->valorChave > get_chave(pagina1->listaChaves->fim)->valorChave)
        {
            pagina1->listaChaves = insere_fim_listad(pagina1->listaChaves, nova_chave);
        }
        else // inserir ordenado
        {
            while (nova_chave->valorChave > get_chave(aux)->valorChave)
            {
                aux = aux->prox;
            }
            Nod *novo_no = cria_nod(nova_chave);
            novo_no->prox = aux;
            novo_no->ant = aux->ant;
            aux->ant->prox = novo_no;
            aux->ant = novo_no;
        }
    }
    pagina1->qtdeChaves++;
    return pagina1;
}

Pagina *cria_nova_raiz(Chave *chave_subir, Pagina *filho_esq, Pagina *filho_dir)
{
    Pagina *nova_raiz = cria_pagina();
    nova_raiz = insere_chave_na_pagina(nova_raiz, chave_subir);
    chave_subir->filho = filho_esq;
    nova_raiz->direita = filho_dir;
    filho_dir->pai = filho_esq->pai = nova_raiz;
    nova_raiz->folha = 0;
    return nova_raiz;
}

Pagina *divide_pagina(Pagina *pagina_a_dividir)
{

    // atualizar a nova pagina - todos os campos
    Pagina *nova_pagina = cria_pagina();
    Nod *aux;
    int qtde = ceil(pagina_a_dividir->qtdeChaves / 2.0); // qtde de chaves é igual a ordem da arvore
    nova_pagina->listaChaves = divide_lista(pagina_a_dividir->listaChaves, qtde);
    nova_pagina->qtdeChaves = pagina_a_dividir->qtdeChaves - qtde;
    nova_pagina->pai = pagina_a_dividir->pai;
    nova_pagina->folha = pagina_a_dividir->folha;

    // atualizar pagina dividida - todos os campos
    pagina_a_dividir->qtdeChaves = qtde;

    // quem vai apontar para a nova págin se nao for a raiz que esta sendo dividida
    if (pagina_a_dividir->pai != NULL)
    {
        aux = pagina_a_dividir->pai->listaChaves->ini;
        while (aux != NULL && pagina_a_dividir != get_chave(aux)->filho)
            aux = aux->prox;

        if (aux == NULL)
            pagina_a_dividir->pai->direita = nova_pagina;
        else
            get_chave(aux)->filho = nova_pagina;
    }

    if (!pagina_a_dividir->folha) // pagina_a_dividir != 1
    {
        aux = nova_pagina->listaChaves->ini;
        while (aux != NULL)
        {
            get_chave(aux)->filho->pai = nova_pagina;
            aux = aux->prox;
        }
        nova_pagina->direita = pagina_a_dividir->direita;
        nova_pagina->direita->pai = nova_pagina;

        // a direita da página queq foi dividida
        // precisa apontar para o mesmo lugar que
        // a chave anterior a ela aponta
        pagina_a_dividir->direita = get_chave(pagina_a_dividir->listaChaves->fim)->filho;
    }
    // chave que vai subir passa a apontar para pagina_a_dividir
    Chave *chave_subir = pagina_a_dividir->listaChaves->fim->info;
    chave_subir->filho = pagina_a_dividir;
    return nova_pagina;
}

void insere_arvoreb(Arvoreb *T, int chave_int)
{
    Pagina *folha = encontra_folha(T, chave_int);
    int tem_valor_inserir = 1;
    Chave *nova_chave = cria_chave(chave_int);
    Pagina *nova_pagina;

    if (folha == NULL)
        T->raiz = insere_chave_na_pagina(folha, nova_chave);
    else
    {
        while (tem_valor_inserir)
        {

            folha = insere_chave_na_pagina(folha, nova_chave);
            if (folha->qtdeChaves < T->ordem)
                tem_valor_inserir = 0;
            else
            {
                nova_pagina = divide_pagina(folha);
                nova_chave = remove_fim_listad(folha->listaChaves)->info;
                folha->qtdeChaves--;
                if (folha == T->raiz) // dividiu a raiz
                {
                    T->raiz = cria_nova_raiz(nova_chave, folha, nova_pagina);
                    tem_valor_inserir = 0;
                }
                else
                    folha = folha->pai;
            }
        }
    }
}

void em_ordem(Pagina *raiz)
{
    if (raiz != NULL)
    {
        Nod *aux = raiz->listaChaves->ini;
        while (aux != NULL)
        {
            em_ordem(get_chave(aux)->filho);
            printf("%d ", get_chave(aux)->valorChave);
            aux = aux->prox;
        }
        em_ordem(raiz->direita);
    }
}

void mostrar_em_ordem(Arvoreb *T)
{
    em_ordem(T->raiz);
}

Pagina *libera_pagina(Pagina *pag_aux)
{
    pag_aux->listaChaves = libera_listad(pag_aux->listaChaves);
    free(pag_aux);
    return NULL;
}

Pagina* libera_todas_paginas(Pagina *raiz)
{
    if (raiz != NULL)
    {
        Nod *aux = raiz->listaChaves->ini;
        while (aux != NULL)
        {
            get_chave(aux)->filho =  libera_todas_paginas(get_chave(aux)->filho);
            aux = aux->prox;
        }
        raiz->direita = libera_todas_paginas(raiz->direita);
        raiz = libera_pagina(raiz);
    }
    return raiz;
}

Arvoreb *libera_arvoreb(Arvoreb *T)
{
    T->raiz = libera_todas_paginas(T->raiz);
    free(T);
    return NULL;
}

int main() {
    int c1 = 1;
    int c2 = 2;
    int c3 = 3;
    int c4 = 4;
    int c5 = 5;
    int c6 = 6;
    Listad* list = cria_listad();
    list = insere_fim_listad(list, &c1);
    list = insere_fim_listad(list, &c2);
    list = insere_fim_listad(list, &c3);
    list = insere_fim_listad(list, &c4);
    list = insere_fim_listad(list, &c5);
    list = insere_fim_listad(list, &c6);
    
    imprime_listad(list);
    Listad* nlist = divide_lista(list, 6);
    imprime_listad(list);
    imprime_listad(nlist);
    
    return 0;
}