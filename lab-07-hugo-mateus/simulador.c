#include <stdio.h>

#ifndef arquivo_stdlib
#define stdlib
#include <stdlib.h>
#endif 
#include <string.h>

#ifndef arquivo_peca
#define arquivo_peca
#include "peca.h"
#endif

#ifndef arquivo_fila
#define arquivo_fila
#include "fila.h"
#endif

#ifndef arquivo_pilha
#define arquivo_pilha
#include "pilha.h"
#endif



int main()
{
    int tam_est, tam_pilha= 0, total_coletado, i = 0, qt_coletados = 0, classe, tempo_atraso = 0;

    int empilhador_tempo = 0, classificador_tempo = 0, empilhador_ocupado = 0, classificador_ocupado = 0;
    int  embalagens_saidas = 0;
    Peca peca_classificador;
    
    char tamanho[10];
    p_fila fila;
    p_pilha pilha;
    pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;

    fila = criar_fila();

    scanf(" %d %d %d", &tam_est, &tam_pilha, &total_coletado);

    printf("##### Simulação\n");

    do
    {
        int entra_class = 0, sai_class = 0, entra_emb = 0, sai_emb = 0;

        //anda um minuto para o tempo de empilhar e classificar até 0
        if (empilhador_tempo <= 0)
            empilhador_tempo = 0;
        else
            empilhador_tempo -= 1;

        if (classificador_tempo <= 0)
            classificador_tempo = 0;
        else
            classificador_tempo -= 1;

        //empilhador acabou e pegou outra peça
        if (empilhador_tempo == 0 && empilhador_ocupado)
        {
            sai_emb = 1;
            empilhador_ocupado = 0;
            embalagens_saidas++;
        }

        if (pilha->topo != NULL && !empilhador_ocupado)
        {
            Peca peca_retirada = desempilhar(pilha);
            empilhador_tempo = tempo_empacotamento_peca(peca_retirada);
            empilhador_ocupado = 1;
        }

        if (empilhador_ocupado && empilhador_tempo <= 0){
            empilhador_ocupado = 0;
        }

        // se acabou esteira e classificador ta livre, da peça pra ele

        int ocupacao_pilha = contar_nos_na_pilha(pilha);

        if (ocupacao_pilha < tam_pilha  && ocupacao_pilha < tam_pilha && classificador_ocupado && classificador_tempo <= 0){
            empilhar(pilha, peca_classificador);
            classificador_ocupado = 0;
            sai_class = 1;
            entra_emb = 1;
        }
        if (fila->ini != NULL && !classificador_ocupado)
        {
            peca_classificador = desenfileira(fila);
            classificador_tempo = tempo_classificacao_peca(peca_classificador);
            classificador_ocupado = 1;
        }

        int  ocupacao_fila = contar_nos_na_fila(fila);
        if (ocupacao_fila < tam_est && qt_coletados < total_coletado)
        {
            scanf(" %s", tamanho);
            scanf(" %d", &classe);
            Peca peca;
            peca.num = qt_coletados;
            peca.classe = classe;
            peca.tamanho = qual_tamanho(tamanho);
            peca.pronto_fila = 0;
            peca.pronto_pilha = 0;
            enfileira(fila, peca);
            qt_coletados++;
            entra_class += 1;
        }
        else  {
            if (qt_coletados < total_coletado){
                tempo_atraso++;
            }
        }

        printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", i + 1, entra_class, sai_class, entra_emb, sai_emb);
        i++;
    } while (embalagens_saidas < total_coletado);

    printf("Tempo atraso: %d.\n", tempo_atraso);

    liberar_fila(fila);
    free(fila);
    free(pilha);
    return 0;
}