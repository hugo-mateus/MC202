#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define FREE -1
#define TRUE 1
#define FALSE 0

typedef struct batMemoria
{
     int *memoria;
     int tamanho;
} batMemoria;


void dobraBatMemoria(batMemoria *batMemoria){
    //cria nova batMemoria com o dobro de espaco
    int *novaBatMemoria = malloc((2 * batMemoria->tamanho) * sizeof(int));

    //copia conteudo da antiga batMemoria para a nova
    for (int i = 0; i < batMemoria->tamanho; i++)
    {
        novaBatMemoria[i] = batMemoria->memoria[i];
    }
    //preenche o resto da memoria com FREE
    for (int i = batMemoria->tamanho; i < 2*batMemoria->tamanho; i++)
    {
        novaBatMemoria[i] = FREE;
    }

    //libera memoria antiga
    free(batMemoria->memoria);

    //atualiza a batMemoria
    batMemoria->tamanho *= 2;
    batMemoria->memoria = novaBatMemoria;
    return;
}

void metadeBatMemoria(batMemoria *batMemoria){
    //cria nova batMemoria com o metade do espaco
    int *novaBatMemoria = malloc((batMemoria->tamanho/2) * sizeof(int));

    //copia conteudo da antiga batMemoria para a nova
    for (int i = 0; i < batMemoria->tamanho/2; i++)
    {
        novaBatMemoria[i] = batMemoria->memoria[i];
    }

    //libera memoria antiga
    free(batMemoria->memoria);

    //atualiza a batMemoria
    batMemoria->tamanho /= 2;
    batMemoria->memoria = novaBatMemoria;
    return;
}

/*Armazena na primeira posicao continua possivel o tamanho do vetor, seguido de seu conteudo, na batMemoria*/
int batAlloc(int tamanhoVetor, int *vetor, batMemoria *batMemoria){
    int achouEspaco = FALSE;
    int posicaoLivre;
    int achouEspacoInvalido = FALSE;

    //busca um espaco livre continuo com tamanho do vetor
    for (int i = 0; i < (batMemoria->tamanho - tamanhoVetor) && !achouEspaco; i++, achouEspacoInvalido = FALSE)
    {
        if(batMemoria->memoria[i] == FREE) //esta em uma posicao livre, deve verificar se as seguintes tambem sao
        {
            for (int j = 0; j < (tamanhoVetor+1) && !achouEspacoInvalido; j++)
            {
                if (batMemoria->memoria[i + j] != FREE)
                {
                    achouEspacoInvalido = TRUE;
                }   
            }
            if (!achouEspacoInvalido)
            {
                achouEspaco = TRUE;
                posicaoLivre = i;
            }
        }
        else //esta no inicio de um vetor, pode pular o vetor inteiro
        {
            i+= batMemoria->memoria[i];
        }
    }

    //copia o vetor para a batMemoria e o libera se achou espaco
    if (achouEspaco)
    {
        batMemoria->memoria[posicaoLivre] = tamanhoVetor;
        for (int i = 0; i < tamanhoVetor; i++)
        {
            batMemoria->memoria[posicaoLivre+i+1] = vetor[i];
        }
        free(vetor);
        return posicaoLivre;
    }
    else //dobra o tamanho e tenta de novo
    {
        dobraBatMemoria(batMemoria);
        return batAlloc(tamanhoVetor, vetor, batMemoria);
    }
}

/*libera o vetor armazenado em batMemoria[endereco], setando todas as posicoes ocupadas por ele para FREE*/
void batFree(batMemoria *batMemoria, int endereco){
    //libera vetor
    int tamanho = batMemoria->memoria[endereco];
    for (int i = 0; i < (tamanho+1); i++)
    {
        batMemoria->memoria[i + endereco] = FREE;
    }

    //checa se apenas um quarto da batMemoria esta sendo usada
    int deveLiberar = TRUE;
    if (batMemoria->tamanho <= 8)
        deveLiberar = FALSE;
    for (int i = (batMemoria->tamanho/4); i < batMemoria->tamanho && deveLiberar; i++)
    {
        if (batMemoria->memoria[i] != FREE)
        {
            deveLiberar = FALSE;
        }
    }
    //reduz memoria pela metade
    if (deveLiberar)
        metadeBatMemoria(batMemoria);

    return;
}

/*imprime o vetor armazenado em batMemoria[endereco]*/
void batPrint(batMemoria *batMemoria, int endereco){
    int tamanho = batMemoria->memoria[endereco];
    for (int i = 1; i < (tamanho); i++)
    {
        printf("%d ", batMemoria->memoria[i+endereco]);
    }
    printf("%d\n", batMemoria->memoria[tamanho+endereco]);
    return;
}

/*imprime informacoes do uso da batMemoria*/
void batUso(batMemoria *batMemoria)
{
    int contadorPosicoesLivres = 0;
    for (int i = 0; i < batMemoria->tamanho; i++)
    {
        if (batMemoria->memoria[i] != FREE)
        {
            contadorPosicoesLivres++;
        }
    }
    printf("%d de %d\n", contadorPosicoesLivres, batMemoria->tamanho);
}
    

int main(){
    batMemoria batMemoria;

    //inicia a batMemoria com 8 posicoes livres
    batMemoria.memoria = malloc(8 * sizeof(int)); 
    batMemoria.tamanho = 8;
    for (int i = 0; i <batMemoria.tamanho; i++)
    {
        batMemoria.memoria[i] = FREE;
    }
    

    int nOperacoes;
    scanf("%d", &nOperacoes); //le numero de operacoes

    char entrada[50];
    int tamanho, endereco;
    //loop para processar as instrucoes
    for (int i = 0; i < nOperacoes; i++)
    {
        scanf("%s", entrada);
        if (strcmp(entrada, "bat-alloc") == 0)
        {
            scanf("%d", &tamanho);
            int *vetorEntrada = malloc(tamanho * sizeof(int));
            for (int j = 0; j < tamanho; j++)
            {
                scanf("%d", &vetorEntrada[j]);
            }
            printf("%d\n", batAlloc(tamanho, vetorEntrada, &batMemoria));
        }
        else if (strcmp(entrada, "bat-free") == 0)
        {
            scanf("%d", &endereco);
            batFree(&batMemoria, endereco);
        }
        else if (strcmp(entrada, "bat-print") == 0)
        {
            scanf("%d", &endereco);
            batPrint(&batMemoria, endereco);
        }
        else if (strcmp(entrada, "bat-uso") == 0)
        {
            batUso(&batMemoria);
        }
    }
    free(batMemoria.memoria);
}