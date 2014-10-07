
#include<stdio.h>
#include<string.h>
int main (int argc, char** argv)
{
	int i;
	int schPid;
	if(argc<3) // 1 shell 2 exec 3 <nome_programa>
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
		if(strcmp(argv[1],"exec")==0)
		{	
			if(argc==3)
			{ /* Call Round Robin */
				printf("Calling RR\n");
				
			
			
			execl("scheduler/scheduler_roundrobin","scheduler/scheduler_roundrobin",NULL);
			return 0;
			}
			if(strncmp("tempoexec=",argv[3],10)==0);
			{
				/*Call SJF */
			printf("Calling SJF\n");
				return 0;
			}
			if(strncmp("prioridade=",argv[3],11)==0)
			{
			printf("Calling priority Lists\n");
				/* Call Priority Lists */
				return 0;
			}
			else
			{
			printf("Tente: ./shell exec <nome do programa> | prioridade=<numero de 1 a 7> | tempoexec=<tempo em ms> \n");
			return 2;
			}
		}
		
		
	
	

	return 0;
}
