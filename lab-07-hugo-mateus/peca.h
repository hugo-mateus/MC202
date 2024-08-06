typedef struct Peca
{
    int num;
    int classe;
    int tamanho;
    int pronto_fila;
    int pronto_pilha;
    int pronto;
} Peca;

typedef struct Peca *p_peca;

typedef struct No
{
    Peca peca;
    struct No *prox;
} No;

typedef struct No *p_no;

int qual_tamanho(char tamanho[]);
int tempo_empacotamento_peca(Peca peca);
int tempo_classificacao_peca(Peca peca);