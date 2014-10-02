#include <stdio.h>
#include <stdlib.h>

struct lista{
	char cmd[100];
	struct lista* prox;
}; typedef struct lista Lista;

struct pilha{
	int num_elem;
	Lista* prim;	
}; typedef struct pilha Pilha;

Pilha *pilha_cria(void);
/*cria pilha vazia*/

void pilha_push(Pilha *p, char *cmd);
/*adiciona elemento na pilha*/

char* pilha_pop(Pilha *p);
/*retira elemento da pilha*/

int pilha_vazia(Pilha *p);
/*retorna 1 se é vazia 0 caso contrario*/

void pilha_libera(Pilha *);
/*esvazia pilha*/

void dump(Pilha* p);
/*imprime na ordem de insersao */
