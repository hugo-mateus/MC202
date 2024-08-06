#include <stdio.h>
#include <stdlib.h>

//Troca os valores da matriz por 0
void esvaziar_matriz(int tamanho, int **matriz) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            matriz[i][j] = 0; 
        }
    }
}

// preenche matriz com numeros colocados em input
void formando_matriz(int tamanho, int** matriz) {
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++) 
            scanf("%d", &matriz[i][j]);
}

// acha a linha com menor soma
int achar_a_linha(int tamanho, int** matriz) {
    int soma_1 = 0, soma_2 = 0, soma_3 = 0,soma_4 = 0;
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_1 += matriz[i][j];
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_2 += matriz[i+1][j];
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_3 += matriz[i][j+1];
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_4 += matriz[i+1][j+1];
    if((soma_1 > soma_2 && soma_1 > soma_4) || (soma_3 > soma_2 && soma_3 > soma_4)){
        return tamanho;
    }
    return 0;
}

//acha a a coluna com menor soma
int achar_a_coluna(int tamanho, int** matriz) {
    int soma_1 = 0, soma_2 = 0, soma_3 = 0,soma_4 = 0;
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_1 += matriz[i][j];
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_2 += matriz[i+1][j];
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_3 += matriz[i][j+1];
    for (int i = 0; i < tamanho; i++) 
        for (int j = 0; j < tamanho; j++)
                soma_4 += matriz[i+1][j+1];
    if((soma_1 > soma_3 && soma_1 > soma_4) || (soma_2 > soma_3 && soma_2 > soma_4)){
        return tamanho;
    }
    return 0;
}

//Imprime a matriz com espaço tabular
void imprimindo_matriz(int tamanho, int** matriz) {
    for (int i = 0; i < tamanho; i++) {
        printf("\n");
        for (int j = 0; j < tamanho; j++) 
            printf("%d\t", matriz[i][j]);
    }
}

int main() {
    int **matriz, tamanho, numero = 1, i, j, tamanho_original, vezes = 0;

    // construindo a matriz
    scanf("%d", &tamanho);
    tamanho_original = tamanho;
    matriz = (int **)malloc(tamanho * sizeof(int *));
    for (i = 0; i < tamanho; i++) 
        matriz[i] = (int *)malloc(tamanho * sizeof(int)); 
    formando_matriz(tamanho, matriz);

    printf("Quadras:");
    imprimindo_matriz(tamanho, matriz);
    
    do {
        int** matriz_recente;
        int p1,p2,substituicao;

        //aloca espaço para a matriz de dentro do loop
        matriz_recente = (int **)malloc(tamanho * sizeof(int *));
        for (i = 0; i < tamanho; i++) 
            matriz_recente[i] = (int *)malloc(tamanho * sizeof(int));

        //substitui um valor
        if(vezes>= 1){
            scanf(" %d", &numero);
            if (numero == 1){
                scanf(" %d %d %d", &p1, &p2, &substituicao);
                if(p1<= tamanho && p2<= tamanho){
                    matriz[p1][p2] = substituicao;
            }}if(numero == 0){
                for (i = 0; i < tamanho; i++) {
                    free(matriz_recente[i]);
                    }free(matriz_recente);
                break;
            }        
        }
        tamanho -= 1;

        int linha_retirada = achar_a_linha(tamanho, matriz);
        int coluna_retirada = achar_a_coluna(tamanho, matriz);

        //retira a linha e coluna encontradas
        int linhas_im = 0, colunas_im = 0;
        for (i = 0; i < tamanho + 1; i++) {
            for (j = 0; j < tamanho + 1; j++) {
                if (i != linha_retirada && j != coluna_retirada) {
                    matriz_recente[linhas_im][colunas_im] = matriz[i][j];
                    if (colunas_im == tamanho - 1) {
                        linhas_im += 1;
                        colunas_im = 0;
                    } else {
                        colunas_im += 1;
                    }
                }
            }
        }

        printf("\n\nConjuntos que precisam de atenção:");
        imprimindo_matriz(tamanho, matriz_recente);

        esvaziar_matriz(tamanho, matriz);
    
        //Coloca os valores da matriz_recente em matriz
        for (i = 0; i < tamanho; i++) {
            for (j = 0; j < tamanho; j++) {
                matriz[i][j] = matriz_recente[i][j];
            }
        }
        //libera espaço de memória
        for (i = 0; i < tamanho + 1; i++) {
            free(matriz_recente[i]);
        }free(matriz_recente);
        vezes++;
    } while (tamanho >= 2 && numero != 0);

    for (i = 0; i < tamanho_original; i++) {
        free(matriz[i]);
    }
    free(matriz);
    printf("\n");
    return 0;
}

