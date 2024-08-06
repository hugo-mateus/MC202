#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

p_fila criar_fila()
{
    p_fila f;
    f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void liberar_fila(Fila *fila)
{
    No *atual = fila->ini;
    while (atual != NULL)
    {
        No *temp = atual;
        atual = atual->prox;
        free(temp); // Libera o nó atual
    }
    fila->ini = fila->fim = NULL; // Define a fila como vazia
}

void enfileira(p_fila f, struct Peca peca)
{
    p_no novo;
    novo = malloc(sizeof(No));
    novo->peca = peca;
    novo->prox = NULL;
    if (f->ini == NULL)
        f->ini = novo;
    else
        f->fim->prox = novo;
    f->fim = novo;
}

Peca desenfileira(p_fila f)
{
    p_no primeiro = f->ini;
    Peca peca = primeiro->peca;
    f->ini = f->ini->prox;
    if (f->ini == NULL)
        f->fim = NULL;
    free(primeiro);
    return peca;
}

int contar_nos_na_fila(p_fila f)
{
    int contador = 0;
    p_no atual = f->ini;
    while (atual != NULL)
    {
        contador++;
        atual = atual->prox;
    }
    return contador;
}

void ficar_na_esteira(p_fila f)
{
    p_no atual = f->ini;
    while (atual != NULL)
    {
        atual->peca.pronto_fila = 1;
        atual = atual->prox;
    }
}
