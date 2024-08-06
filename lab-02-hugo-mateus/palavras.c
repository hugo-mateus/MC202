#include <stdio.h>
#define MAX_LINHAS 300
#define MAX_COLUNAS 300
#define MAX_N_PALAVRAS 300
#define MAX_PALAVRA_TAMANHO 20

//Cria uma função strlen para descobrir o tamanho da palavra
int strlen_criado(char *str) {
    int len = 0;
    while (str[len]!= '\0') {
        len++;
    }
    return len;
}

//procura a palavra na matriz
int procura_palavra(char matriz[MAX_LINHAS][MAX_COLUNAS], int l, int c, char *palavra) {
    int i, j, r;
    int tamanho_p;

    tamanho_p = strlen_criado(palavra);

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            // verifica horizontal 
            if (j +tamanho_p <= c) {
                int achou = 1;
                for (r = 0; r < tamanho_p; r++) {
                    if (palavra[r] != matriz[i][j + r]) {
                        achou = 0;
                        break;}
                }if (achou) {
                    return 1;
                }
            }
            // Verifica horizontal invertida
            if (j- tamanho_p + 1 >= 0) {
                int achou = 1;
                for (r = 0; r < tamanho_p; r++) {
                    if (palavra[r] != matriz[i][j - r]) {
                        achou = 0;
                        break;}
                }if (achou) {
                    return 1;
                }
            }

            // Verifica vertical 
            if (i + tamanho_p <= l) {
                int achou = 1;
                for (r = 0; r < tamanho_p; r++) {
                    if (palavra[r] != matriz[i + r][j]) {
                        achou = 0;
                        break;}
                }if (achou) {
                    return 1;
                }
            }

            // Verifica vertical invertida
            if (i - tamanho_p + 1 >= 0) {
                int achou = 1;
                for (r = 0; r < tamanho_p; r++) {
                    if (palavra[r] != matriz[i - r][j]) {
                        achou = 0;
                        break;}
                }if (achou) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    int l, c, p, i;
    char matriz[MAX_LINHAS][MAX_COLUNAS];
    char palavras[MAX_N_PALAVRAS][MAX_PALAVRA_TAMANHO];

    scanf("%d %d %d", &l, &c, &p);
    for (i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            scanf(" %c", &matriz[i][j]);
        }
    }
    for (i = 0; i < p; i++) {
        scanf("%s", palavras[i]);
    }
    for (i = 0; i < p; i++) {
        if (procura_palavra(matriz, l, c, palavras[i])) {
            printf("A palavra %s está no texto!\n", palavras[i]);
        } else {
            printf("A palavra %s não está no texto!\n", palavras[i]);
        }
    }
    return 0;
}

