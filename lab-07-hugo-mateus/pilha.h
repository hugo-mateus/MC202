#ifndef arquivo_peca
#define arquivo_peca
#include "peca.h"
#endif


typedef struct
{
    p_no topo;
} Pilha;

typedef Pilha *p_pilha;

void empilhar(Pilha *pilha, Peca peca);
Peca desempilhar(Pilha *pilha);
int contar_nos_na_pilha(Pilha *p);
void ficar_na_pilha(p_pilha f);
