
#ifndef arquivo_peca
#define arquivo_peca
#include "peca.h"
#endif

#ifndef arquivo_string
#define arquivo_string
#include <string.h>
#endif

int qual_tamanho(char tamanho[]){
    if (strcmp(tamanho, "pequena") == 0)
        return 1;
    if (strcmp(tamanho, "media") == 0)
        return 2;
    if (strcmp(tamanho, "grande") == 0)
        return 3;
    else
        return -1;
}


int tempo_empacotamento_peca(Peca peca){
    if (peca.tamanho == 1 && peca.classe == 1)
    {
        return 1;
    }
    if ((peca.tamanho == 1 && peca.classe == 2) || (peca.tamanho == 2 && peca.classe == 1) || (peca.tamanho == 3 && peca.classe == 1))
    {
        return 2;
    }
    if ((peca.tamanho == 2 && peca.classe == 2) || (peca.tamanho == 3 && peca.classe == 2))
    {
        return  3;
    }
    return 0;
}

int tempo_classificacao_peca(Peca peca){
    if (peca.tamanho == 1)
    {
        return 1;
    }
    if (peca.tamanho == 2)
    {
        return 2;
    }
    if (peca.tamanho == 3)
    {
        return 3;
    }
    return 0;
}
