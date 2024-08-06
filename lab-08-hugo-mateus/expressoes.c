#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct no *p_no;

struct no {
    char dado;
    p_no esq , dir; /* pai */
};

p_no criar_arvore(char x, p_no esq, p_no dir)
{
    p_no r = malloc(sizeof(struct no));
    r->dado = x;
    r->esq = esq;
    r->dir = dir;
    return r;
}


void libera_arvore(p_no raiz)
{
    if (raiz != NULL){
        libera_arvore(raiz->esq);
        libera_arvore(raiz->dir);
        free(raiz);
    }
}

int eh_operador(char x){
    return (x == '>' || x == '<' || x == '}' || x == '{' || x == '&' || x == '|' || x == '=' || x == '!');
}

void inordem(p_no raiz) {
    //imprime a arvore lendo inordem
    if (raiz != NULL) {
        if (eh_operador(raiz->dado)){
            printf("(");
            inordem(raiz->esq);
            printf(" ");
        }
        printf("%c", raiz->dado); 
        if (eh_operador(raiz->dado)){
            printf(" ");
            inordem(raiz->dir);
            printf(")");
        }
    }
}
void trocar(p_no raiz, char c){
    raiz->dado = c;
    libera_arvore(raiz->esq);
    libera_arvore(raiz->dir);
    raiz->esq = NULL;
    raiz->dir = NULL;
}
void otimizar(p_no raiz){

    if (raiz != NULL && eh_operador(raiz->dado) && raiz->esq != NULL && raiz->dir != NULL)
    {
        otimizar(raiz->esq);
        otimizar(raiz->dir);
        char operador = raiz->dado;
        char esq = raiz->esq->dado;
        char dir = raiz->dir->dado;
        if ( esq == dir && !eh_operador(esq) && !eh_operador(dir))
        {
            if (operador == '>' || operador == '<' || operador == '!')
                trocar(raiz, 'F');
            if (operador == '=' || operador == '{' || operador == '}')
                trocar(raiz, 'T');
        }

        if( '0' <= esq && esq <= '9' && '0' <= dir && dir <= '9'){
            if (operador == '{')
                trocar(raiz, esq <= dir ? 'T' : 'F');
            
            if (operador == '}')
                trocar(raiz, esq >= dir ? 'T' : 'F');
            
            if (operador == '<')
                trocar(raiz, esq < dir ? 'T' : 'F');
            
            if (operador == '>'){
                trocar(raiz, esq > dir ? 'T' : 'F');
            }
            
            if (operador == '=')
                trocar(raiz, esq == dir ? 'T' : 'F');
            
            if (operador == '!')
                trocar(raiz, esq != dir ? 'T' : 'F');
            
        }

        if((esq == 'T' || dir == 'T') && operador == '|')
            trocar(raiz, 'T');
        
        if((esq == 'F' || dir == 'F') && operador == '&')
            trocar(raiz, 'F');
        
        if(dir == '9' && operador == '{')
            trocar(raiz, 'T');
        
        if(esq == '9' && operador == '}')
            trocar(raiz, 'T');
        
        if(dir == '0' && operador == '}')
            trocar(raiz, 'T');

        if(esq == '0' && operador == '{')
            trocar(raiz, 'T');
        
        if(dir == '9' && operador == '>')
            trocar(raiz, 'F');
        
        if(esq == '9' && operador == '<')
            trocar(raiz, 'F');

        if(dir == '0' && operador == '<')
            trocar(raiz, 'F');

        if(esq == '0' && operador == '>')
            trocar(raiz, 'F');
    }
}

typedef struct pilha{
    struct pilha* proximo;
    p_no expressao;
} pilha;

int mp = 0;

void colocar(pilha **p, char dado, p_no esq, p_no dir)
{
    pilha *novo = malloc(sizeof(pilha));
    novo->proximo = *p;
    novo->expressao = criar_arvore(dado, dir, esq);
    *p = novo;
}
int fp = 0;
void pegar_dois(pilha **p, p_no* primeiro, p_no* segundo)
{
    pilha *aux = (*p);

    *primeiro = aux->expressao;
    *segundo = aux->proximo->expressao;
    *p = (*p)->proximo->proximo;
    free(aux->proximo);
    free(aux);


}

void fundir_topo(pilha** p, char operador){
    p_no esq = NULL;
    p_no dir = NULL;
    pegar_dois(p, &esq, &dir);

    colocar(p, operador, esq, dir);
}

int main()
{
    int n;
    scanf("%d ", &n);

    for (int i = 0; i < n; i++){
        int f = 0;
        p_no raiz = NULL;
        char entrada[500];
        struct pilha *p = NULL;
        scanf("%s ", entrada);

        // descobrir quantos caracteres tem na entrada
        while(entrada[f] != '\0'){
            f++;
        }


        int i = 0;
        while (i < f)
        {
            if (eh_operador(entrada[i]))
                fundir_topo(&p, entrada[i]);
            else
                colocar(&p, entrada[i], NULL, NULL);
            i++;
        }

        raiz = p->expressao;

        struct pilha *aux = p;
        while (p != NULL)
        {
            aux = p->proximo;
            free(p);
            p = aux;
        }
        printf("\n");
        inordem(raiz);
        printf("\n");
        otimizar(raiz);
        inordem(raiz);
        printf("\n\n");
        libera_arvore(raiz);
    }
    return 0;
}
