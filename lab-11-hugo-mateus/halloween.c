#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define M 1511
typedef struct
{
	char nome[11];
	int doces;
	int existe;
} no;

typedef struct
{
	no v[M];
	int usado;
} hash;
typedef hash *p_hash;

int hashing(char *chave)
{
	int len = strlen(chave);
	int h = 0;
	for (int i = 0; i < len; i++)
	{
		h = (h * 256 + chave[i]) % M;
	}
	return h;
}

void inserir(p_hash h, no n)
{
	h->usado += 1;

	int posicao = hashing(n.nome);
	for (int i = 0; i < M; i++)
	{
		if (!h->v[(posicao + i) % M].existe)
		{
			h->v[(posicao + i) % M] = n;
			return;
		}
	}
}

typedef struct no_pilha
{
	no n;
	struct no_pilha *prox;
} no_pilha;

void remover(p_hash h, char *chave)
{
	h->usado -= 1;
	int posicao = hashing(chave);
	int k = 0;
	for (; k < M; k++){
		if (strcmp(h->v[(posicao + k) % M].nome, chave) == 0){
			posicao += k;
			break;
		}
	}
	no_pilha *pilha = NULL;
	h->v[posicao] = (no){"", 0, 0};
	for (int i = 1; i < M && h->v[(posicao + i) % M].existe; i++)
	{
		no_pilha *aux = malloc(sizeof(no_pilha));
		*aux = (no_pilha){h->v[(posicao + i) % M], pilha};
		pilha = aux;
		h->v[(posicao + i) % M] = (no){"", 0, 0};
	}
	while (pilha != NULL){
		inserir(h, pilha->n);
		no_pilha *aux = pilha->prox;
		free(pilha);
		pilha = aux;
	}
}

int buscar_doces(p_hash h, char * chave){
	int posicao = hashing(chave);
	for (int i = 0; i < M; i++)
		if (!strcmp(h->v[(posicao + i) % M].nome, chave))
			return h->v[(posicao + i) % M].doces;
	return -1;
}
void atualizar_doces(p_hash h, char* chave, int soma){
	
	int posicao = hashing(chave);
	for (int i = 0; i < M; i++)
	{

		if (!strcmp(h->v[(posicao + i) % M].nome, chave)){
			h->v[(posicao + i) % M].doces += soma;
			return;
		}
	}
}

int main()
{
	hash h = (hash){0};
	for (int i = 0; i < M; i++)
	{
		h.v[i].doces = 0,
		h.v[i].existe = 0;
	}
	char command[20];
	for (scanf("%s ", command); strcmp(command, "FINALIZAR") != 0; scanf("%s ", command))
	{
		if (!strcmp(command, "ENTRAR"))
		{
			char familia[11];
			int doces;
			scanf("%s %d ", familia, &doces);
			no n = (no){"",doces, 1};
			strcpy(n.nome, familia);
			inserir(&h, n);
		}
		else if (!strcmp(command, "TRICKORTREAT"))
		{
			char crianca[11];
			char crianca_sobrenome[11];
			int familias;
			int total_doces = 0;
			scanf("%s %s %d", crianca, crianca_sobrenome, &familias);
			for (int i = 0; i < familias; i++)
			{
				char familia[11];
				char nota[11];
				scanf("%s %s ", familia, nota);
				int dn;
				if (nota[0] == 'R')
					dn = 1;
				if (nota[0] == 'M')
					dn = 2;
				if (nota[0] == 'B')
					dn = 3;
				int doces = buscar_doces(&h, familia);
				int recebidos;
				if (doces > 0){
					if (doces - dn <= 0)
					{
						printf("A familia %s ficou sem doces.\n", familia);
						recebidos = doces;
					}
					if (doces - dn > 0)
						recebidos = dn;
					atualizar_doces(&h, familia, -recebidos);
					total_doces = total_doces + recebidos;
				}
			}
			printf("%s %s recebeu ", crianca, crianca_sobrenome);
			if (total_doces > 0)
				printf("%d doce(s) das familias.\n", total_doces);
			else
				printf("10 doces da prefeitura.\n");
		}
		else if (!strcmp(command, "COMPRAR"))
		{
			char familia[11];
			int doces;
			scanf("%s %d", familia, &doces);
			atualizar_doces(&h, familia, doces);
			int atual = buscar_doces(&h, familia);
			printf("A familia %s agora possui %d doces.\n", familia, atual);
		}
		else if (!strcmp(command, "SAIR"))
		{
			char familia[11];
			scanf("%s ", familia);
			int atual = buscar_doces(&h, familia);
			remover(&h, familia);
			printf("A familia %s saiu com %d doce(s) sobrando.\n", familia, atual);
		}
	}
}