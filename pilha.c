#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

Pilha* pilha_cria(void)
{
	Pilha* p = (Pilha*)malloc(sizeof(Pilha));
	p->prim = NULL;
	return p;
}

void pilha_push(Pilha* p, char *cmd)
{
	
	Lista* n = (Lista*)malloc(sizeof(Lista));
	
	strcpy(n->cmd,cmd);
	//n->cmd = cmd;
	n->prox = p->prim;
	p->prim = n;
}

char* pilha_pop(Pilha* p)
{
	Lista* t;
	char *v;
	if(pilha_vazia(p))
	{
		printf("Pilha vazia.\n");
		exit(1);
	}

	v = (char*)malloc(sizeof(char)*(1+strlen(p->prim->cmd)));	

	if(v == NULL)
	{
		printf("erro no malloc v\n");
		exit(1);
	}
	
	t = p->prim;
	strcpy(v,t->cmd);
	p->prim = t->prox;
	free(t);
	return v;
}

int pilha_vazia(Pilha* p)
{
	return(p->prim==NULL);
}

void pilha_libera(Pilha *p)
{
	Lista* q = p->prim;
	
	while(q!=NULL)
	{
		Lista* t = q->prox;
		free(q);
		q = t;
	}
	free(p);
}

void dump(Pilha* p)
{
	Lista* q;
	Pilha* aux;
	aux = pilha_cria();

	for(q=p->prim; q!=NULL; q=q->prox)
	{
		pilha_push(aux,q->cmd);
	}
	if(pilha_vazia(p))
		printf("pilha vazia\n");
	for(q=aux->prim; q!=NULL; q=q->prox)
		printf("%s\n",q->cmd);

}
