#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct grafo {
    int **adj;
    int n;
} grafo;

typedef grafo *p_grafo;

typedef struct no {
    int v;
    struct no* prox; 
} no; 
typedef no *p_no;



typedef struct
{
    int *n;
    p_no topo;
} Pilha;

typedef Pilha *p_pilha;

Pilha* criar_pilha (){
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->n = 0;
    p->topo = NULL;
    return p;
}

void empilhar(p_pilha pilha , int x) {
    p_no novo = malloc(sizeof(no));
    novo->v = x;
    novo->prox = pilha ->topo;
    pilha->topo = novo;
}

int desempilhar(p_pilha pilha) {
    p_no topo = pilha ->topo;
    int x = topo ->v;
    pilha ->topo = pilha ->topo ->prox;
    free(topo);
    return x;
}

void destroi_pilha (Pilha* p){
free(p);
}

int pilha_vazia (Pilha* p){
    return (p->topo == NULL);
}

p_grafo criar_grafo(int n) {
    int i, j;
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = n;
    g->adj = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        g->adj[i] = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->adj[i][j] = 0;

    return g;
}

void destroi_grafo(p_grafo g) {
    int i;
    for (i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

void insere_aresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void remove_aresta(p_grafo g, int u, int v) {
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

int tem_aresta(p_grafo g, int u, int v) {
    return g->adj[u][v];
}

int busca_rec(p_grafo g, int *visitado , int v, int t) {
    int w;
    if (v == t)
        return 1; 
    visitado[v] = 1;
    for (w = 0; w < g->n; w++)
        if (g->adj[v][w] && !visitado[w])
            if (busca_rec(g, visitado , w, t))
                return 1;
    return 0;
}
int existe_caminho(p_grafo g, int s, int t) {
    int encontrou , i, *visitado = malloc(g->n * sizeof(int));
    for (i = 0; i < g->n; i++)
        visitado[i] = 0;
    encontrou = busca_rec(g, visitado , s, t);
    free(visitado);
    return encontrou;
}



int operacao_valida(int operacao){
    if (operacao == 1 ||operacao == 2 ||operacao == 3 ||operacao == 4 ||operacao == 5 ||operacao == 6)
        return 1;
    return 0;
}

p_grafo adiciona_vertice(p_grafo g, int u) {
    g->adj[u][u]= 1;
    return g;
}


int busca_vertice(p_grafo g, int n) {
    if (g == NULL || n < 0 || n >= g->n) {
        // Grafo não existe ou índice inválido
        return 0;
    }

    if (g->adj[n][n]) {
        return 1; // Elemento encontrado na coordenada (i, j)
    }
    // Elemento não encontrado
    return 0;
}
void busca_em_profundidade(p_grafo g, int *pai , int p, int v) {
    int* adjs = g->adj[v]; 
    pai[v] = p;
    for(int i = 0; i  < 20; i++)
        if (adjs[i] && pai[i] == -1 )
            busca_em_profundidade(g, pai , v, i);
}

void enfileira(p_pilha p, int i){
    p_no n = malloc(sizeof(no));
    n->v = i;
    p_no aux = p->topo;
    if (aux != NULL){
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = n;
        p->topo = aux;
    } else {

        p->topo = n;
    }    
}
void busca_em_largura(p_grafo g, int *pai, int k){
    p_pilha p = criar_pilha();
    enfileira(p, k);
    while (!pilha_vazia(p))
    {
        int u = desempilhar(p);
        for (int i = 0; i < 20; i++){
            if (g->adj[u][i] && pai[i] == -1)
            {
                pai[i] = u;
                enfileira(p, i);
            }
        }
    }
    destroi_pilha(p);
}
int * encontra_caminhos(p_grafo g, int s) {
    int i, *pai = malloc(g->n * sizeof(int));
    for (i = 0; i < g->n; i++)
        pai[i] = -1;
    busca_em_largura(g, pai, s);
    return pai;
}




void imprimi_caminho(int v, int *pai, int final) {
    if(pai[v] != v)
        imprimi_caminho(pai[v], pai, final);
    if (final == v)
        printf("%d\n", v);
    else
        printf("%d -> ", v);
}

int * busca_em_profundidade_2(p_grafo g, int s) {
    int w, v;
    int *pai = malloc(g->n * sizeof(int));
    int *visitado = malloc(g->n * sizeof(int));
    p_pilha p = criar_pilha ();
    for (v = 0; v < g->n; v++) {
        pai[v] = -1;
        visitado[v] = 0;
    }
    empilhar(p,s);
    pai[s] = s;
    while (!pilha_vazia(p))
    {
        v = desempilhar(p);
        if (visitado[v])
            continue;
        visitado[v] = 1;

 
        for (w = 0; w < g->n; w++)
            if (g->adj[v][w] && !visitado[w]) {
                pai[w] = v;
                empilhar(p, w);
        }
    }
    destroi_pilha(p);
    free(visitado);
    return pai; 
}

void imprime_conexoes_diretas_indiretas(p_grafo g, int *pai, int u) {
    int *visitado = calloc(g->n, sizeof(int));
    // Armazena os vértices conectados diretamente ou indiretamente
 
    printf("Ponto %d (Pontos diretamente ou indiretamente conectados): ", u);

    for (int i = 0; i < g->n; i++) {
        if (pai[i] != -1 ) {
                printf("%d ", i);
        }
    }
    printf("\n");

    free(visitado);
}


int main(){
    int operacao = 1, u,v;
    p_grafo grafo = criar_grafo(20);
    while (operacao_valida(operacao)){
        scanf(" %d ", &operacao);

        if (operacao == 1){
            scanf(" %d ", &u);

            if (busca_vertice(grafo, u) == 0) {
                grafo = adiciona_vertice(grafo, u);
            }
        }

        if (operacao ==2){
            scanf(" %d %d ", &u, &v);
            if (!tem_aresta(grafo, u, v))
                insere_aresta(grafo,u, v);
        }

        if (operacao == 3){
            scanf(" %d %d ", &u, &v);
            if (tem_aresta(grafo, u,v))
                remove_aresta(grafo, u,v);
        }

        if (operacao == 4){
            scanf(" %d %d ", &u, &v);
            if (existe_caminho(grafo, u,v))
                printf("Existe conexão entre os nós.\n");
            else
                printf("Não existe conexão entre os nós.\n");
        }
        
        if (operacao ==5){
            scanf(" %d %d", &u, &v);
            if (existe_caminho(grafo,u,v)){
                int *pais = encontra_caminhos(grafo, u);
                int final = v;
                imprimi_caminho(v, pais, final);
                free(pais);
            }else {
                printf("Não existe conexão entre os nós.\n");
            }
        }

        if(operacao ==6){
            for(int j = 0; j <= 20; j++){
                if(busca_vertice(grafo, j)){
                    int *pai = busca_em_profundidade_2(grafo, j);
                    imprime_conexoes_diretas_indiretas(grafo, pai, j);
                    free(pai);
                }
            }
        }
    }
    destroi_grafo(grafo);
    return 0;
}