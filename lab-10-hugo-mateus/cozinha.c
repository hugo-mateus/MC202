#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define PAI(i) ((i - 1) / 2)
#define F_ESQ(i) (2 * i + 1) /* Filho esquerdo de i*/
#define F_DIR(i) (2 * i + 2) /* Filho direito de i*/

typedef struct
{
    int dias;
    char prato[30];
    int chave;
} Item;

typedef struct
{
    Item *v;        // vetor de Items alocado dinamicamente
    int n, tamanho; // n: qtde de elementos , tamanho: qtde alocada
} FP;

typedef FP *p_fp;

p_fp criar_filaprio(int tam)
{
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tam * sizeof(Item));
    fprio->n = 0;
    fprio->tamanho = tam;
    return fprio;
}

void troca(Item *item1, Item *item2){
    Item aux = *item1;
    *item1 = *item2;
    *item2 = aux;
} 
int compara(Item item1, Item item2 ){
    return item1.chave > item2.chave || (item1.chave == item2.chave && item1.dias < item2.dias);
}
void sobe_no_heap(p_fp fprio, int k)
{
    if (k > 0 && compara(fprio->v[k], fprio->v[PAI(k)]) )
    {
        troca(&fprio->v[k], &fprio->v[PAI(k)]);
        sobe_no_heap(fprio, PAI(k));
    }

}

void desce_no_heap(p_fp fprio, int k)
{
    int maior_filho;
    if (F_ESQ(k) < fprio->n)
    {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n &&  compara(fprio->v[F_DIR(k)], fprio->v[F_ESQ(k)]))
            maior_filho = F_DIR(k);
        if (fprio->v[k].chave < fprio->v[maior_filho].chave)
        {
            troca(&fprio->v[k], &fprio->v[maior_filho]);
            desce_no_heap(fprio, maior_filho);
        }
    }
}

void insere(p_fp fprio, Item item)
{
    fprio->v[fprio->n] = item;
    fprio->n++;
    sobe_no_heap(fprio, fprio->n - 1);
}



Item extrai_maximo(p_fp fprio)
{
    Item item = fprio->v[0];
    troca(&fprio->v[0], &fprio->v[fprio->n - 1]);
    fprio->n--;
    desce_no_heap(fprio, 0);
    return item;
}



void muda_prioridade(p_fp fprio, int k, int valor)
{
    if ( valor < 0)
    {
        fprio->v[k].chave += valor;
        desce_no_heap(fprio, k);
    }
    else
    {
        fprio->v[k].chave += valor;
        sobe_no_heap(fprio, k);
    }
}


void troca_id(p_fp fprio, int valor, int dias)
{
    for (int i = 0; i < fprio->n; i++)
    {
        if (fprio->v[i].dias == dias)
        {
            muda_prioridade(fprio, i, valor);
            return;
        }
    }
} 
Item encontra_maior_chave(p_fp fprio)
{
    if (fprio->n == 0)
    {
        Item item_vazio = { 0, "", 0};
        return item_vazio;
    }

    Item maior_item = fprio->v[0];
    for (int i = 1; i < fprio->n; i++)
    {
        if (fprio->v[i].chave > maior_item.chave)
        {
            maior_item = fprio->v[i];
        }
    }

    return maior_item;
}



int main()
{
    int panelas, sobreviventes, dias, pedidos = 1, valor, rodadas = 0, quantidade[151];
    p_fp fprio;
    Item item;
    char nomes[151][151], sobrenomes[151][151], instrucao[10];
    scanf(" %d %d", &panelas, &sobreviventes);
    fprio = criar_filaprio(sobreviventes);

    for (int i = 0; i < sobreviventes; i++)
    {
        scanf(" %s", nomes[i]);
        scanf(" %s", sobrenomes[i]);
        scanf(" %d", &quantidade[i]);
    }

    scanf(" %d", &pedidos);
    do
    {
        rodadas++;

        for (int i = 0; i < pedidos; i++)
        {
            scanf("%s ", instrucao);
            scanf("%d ", &dias);
            if (strcmp(instrucao, "novo") == 0)
            {
                char c = getchar();;
                int i = 0;
                while (c != '\n')
                { 
                    item.prato[i] = c;
                    c = getchar();
                    i++;
                }
                item.prato[i] = '\0';
                //printf("%s-%d-%s\n", instrucao, dias, item.prato);
                item.chave = quantidade[dias];
                item.dias = dias;
                insere(fprio, item);
            }
            if (strcmp(instrucao, "altera") == 0)
            {
                scanf(" %d", &valor);
                troca_id(fprio, valor, dias);
            }
        }

        printf("---- rodada %d ----\n", rodadas);
        int pedidos_entregues = panelas;
        if (fprio->n < panelas )
            pedidos_entregues = fprio->n;

        for (int i = 0; i < pedidos_entregues; i++)
        {
            Item maximo = extrai_maximo(fprio);
            int dias = maximo.dias;
            printf("%s %s %s %d\n", nomes[dias], sobrenomes[dias], maximo.prato, maximo.chave);
        }
        if (pedidos != 0)
        {
            scanf(" %d", &pedidos);
        }
    } while (pedidos > 0 || fprio->n > 0);
    free(fprio->v);
    free(fprio);
    return 0;
}