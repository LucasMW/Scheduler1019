
#include<stdio.h>

int main (int argc, char** argv)
{
int i;
if(argc<2)
{
printf ("Shell espera parametros: \n\n");
printf("exec <nome_programa> prioridade=<numero de 1 a 7> , no caso de lista de prioridades\n");

printf("exec <nome_programa> tempoexec=<tempo em ms>, no caso de SJF\n");

printf("exec <nome_programa>, no caso de ROUND-ROBIN\n"); 
return 1;
}
for(i=1;i<argc;i++)
{
	printf("%s\n",argv[i]);
}

return 0;
}
