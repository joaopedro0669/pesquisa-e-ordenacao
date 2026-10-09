//10/04/26

#include "arvoreb.h"

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

// encontre a página que seja uma folha para inserir a chave  ch
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

/*insira ch na página encontrada (insere ordenado na lista)*/

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
    // chave que vai subir passa a apontar para pagina_a_dividir
    Chave *chave_subir = pagina_a_dividir->listaChaves->fim->info;
    chave_subir->filho = pagina_a_dividir;

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
    return nova_pagina;
}


/*
inicio
  encontre a página que seja uma folha para inserir a chave  ch
  enquanto tem valor para inserir
  insira ch na página encontrada (insere ordenado na lista)
  se (página não está estourou sua capacidade) então
         marque que não tem mais valor para inserir
  senão
        divida a página em que inseriu em pg1 e pg2;
//pg1 = página em que inserimos a ch e que portanto será dividida
//pg2 eh nova a nova página que deve ser criada
      ch= ultima chave de pg1; //a qual é retirada de nó1
        se (pg era a raiz) então
           crie uma nova raiz como página ascendente de pg1 e pg2;
           coloque a chave ch e ponteiros para pg1 e pg2 nessa raiz
           marque que não tem mais valor para inserir
        senao
           folha = seu pai;
        fimse
  fimse
  fimenquanto
fim
*/

void insere_arvoreb(Arvoreb *T, int chave_int)
{
    Chave *c = cria_chave(chave_int);
    Pagina* ins = encontra_folha(T, chave_int);

    ins = insere_chave_na_pagina(ins, c);
    Pagina* aux = ins;
    while(aux && aux->qtdeChaves == T->ordem){
        Pagina *np = divide_pagina(aux);

        Chave* subir = aux->listaChaves->fim->info;
        aux->listaChaves = remove_fim_listad(aux->listaChaves);

        if(!aux->pai){
            T->raiz = cria_nova_raiz(subir, ins, np);
            aux = NULL;
        }
        else{
            aux->pai = insere_chave_na_pagina(aux->pai, subir);
            aux = aux->pai;
        }
    }
}

void mostrar_em_ordem(Arvoreb *T)
{
    em_ordem(T->raiz);
}

void em_ordem(Pagina *raiz)
{
    if(raiz){
        Nod* aux = raiz->listaChaves->ini;
        while(aux){
            em_ordem(get_chave(aux)->filho);
            printf("%d ", get_chave(aux)->valorChave);
            aux = aux->prox;
        }
        em_ordem(raiz->direita);
    }
}