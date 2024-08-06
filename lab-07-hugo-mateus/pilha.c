
#ifndef arquivo_pilha
#define arquivo_pilha
#include "pilha.h"
#endif

#ifndef arquivo_stdio
#define arquivo_stdio
#include <stdio.h>
#endif

#ifndef arquivo_stdlib
#define stdlib
#include <stdlib.h>
#endif 

void empilhar(p_pilha pilha, Peca peca)
{
    p_no novo = malloc(sizeof(No));
    novo->peca = peca;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

Peca desempilhar(p_pilha pilha)
{
    p_no topo = pilha->topo;
    Peca peca = topo->peca;
    pilha->topo = pilha->topo->prox;
    free(topo);
    return peca;
}

int contar_nos_na_pilha(p_pilha p)
{
    int contador = 0;
    p_no atual = p->topo;
    while (atual != NULL)
    {
        contador++;
        atual = atual->prox;
    }
    return contador;
}

void print_ppilha(p_no p)
{
    if (p == NULL)
        return;
    printf("%d ", p->peca.num);
    if (p->prox != NULL)
        print_ppilha(p->prox);
}

void ficar_na_pilha(p_pilha f)
{
    p_no atual = f->topo;
    if (atual != NULL)
    {
        atual->peca.pronto_pilha = 1;
    }
}