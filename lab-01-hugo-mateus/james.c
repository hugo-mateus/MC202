#include <stdio.h>


int quantidade(int lista[], int n, int v){
    int salada_v = 0, i;
    for (i = 0; i< n; i++){
        if (lista[i] == v)
            salada_v++;
    }
    return salada_v;
}


int main(){
    int n, i;
    scanf("%d", &n);
    int lista[10000];
    for (i = 0; i < n; i++)
        scanf("%d", &lista[i]);
    int maior_momento = 0, maior = 0, repetido = 0, repetido_momento = 0;
    for (i = 0; i<n; i++){
        if (lista[i] == repetido_momento){
            maior_momento ++;
        } else {
            repetido_momento = lista[i];
            maior_momento = 1;
        }
        if (maior < maior_momento){
            repetido = repetido_momento;
            maior = maior_momento;
        }  
    } 
    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", quantidade(lista, n, 5), quantidade(lista, n, 7), quantidade(lista, n, 10));
    printf("James vendeu %d saladas de %d reais consecutivamente\n", maior, repetido);
    return 0;
}
