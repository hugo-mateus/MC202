#ifndef arquivo_peca
#define arquivo_peca
#include "peca.h"
#endif

typedef struct
{
    p_no ini, fim;
} Fila;

typedef Fila *p_fila;

p_fila criar_fila();
void liberar_fila(Fila *fila);
void enfileira(p_fila f, Peca peca);
Peca desenfileira(p_fila f);
int contar_nos_na_fila(p_fila f);
void ficar_na_esteira(p_fila f);
