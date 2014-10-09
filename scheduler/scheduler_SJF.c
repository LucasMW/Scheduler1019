#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
 
 
void ordena(int* pids, int* execTime,int tam);

int *pids; // vetor com os pids dos processos a serem executados segundo a politica SJF

int t_ini,t_fim,turnaround;// variaveis para guardar o tempo

/*int main(int argc, char** argv)
{
	char *Myargs[2];
	Myargs[0]="process1";
	Myargs[1]="process2";
	
	int time[2];
	time[0] = 3;
	time[1] = 2;
	
	int tam = 2;
	scheduler_SJF (time,Myargs,tam);

	return 0;
}*/
int scheduler_SJF (int *execTime,char **path, int tam)
{
	int i,j;// contadores
	pids = (int*) malloc(tam*sizeof(int));
 
	for (i=0;i<tam;i++)
	{
		
		if(pids == NULL)
		{
			printf ("erro ao alocar - SJF");
			exit(1);
			
		}

		pids[i] = fork();

		if(pids[i] == 0)// filho
		{
			//raise(SIGSTOP);
			execl(path[i],path[i],NULL);
			kill(pids[i],SIGSTOP);
			sleep(1);			
		}

	}
	ordena(pids,execTime,tam);	// função auxiliar para ordenar os tempos dos processos do menor pra o maior tempo
	
	// começa o SJF de fato 
	for (j=0;j<tam;j++)
	{
		t_ini = (int)time(NULL);// gurda o tempo do inicio do processo 1

		printf("\nInicio do processo %d: %d\n",j,(int)time(NULL));// inicio do processo

		kill(pids[j],SIGCONT);// inicia o processo com o menor tempo
		waitpid(pids[j],NULL,0);//espera ele terminar

		t_fim = (int)time(NULL);// gurda o tempo do fim do processo
		printf("Fim do processo %d: %d\n",j,(int)time(NULL));
		
		turnaround = t_fim-t_ini;
		printf ("turn around do processo %d é : %d\n",j,turnaround);
	}


}

// sort simples que ordena os pids e times em ordem crescente
void ordena(int* pids, int* execTime,int tam)
{
	int i,temp,temp2,fim;
		for (fim=tam-1; fim>0; fim--)
		{
			for (i=0; i<fim; i++)
			{
				if (execTime[i]>execTime[i+1]) 
				{
					temp = execTime[i];
					temp2 = pids[i];
					// troca e efutada aqui
					execTime[i] = execTime[i+1];
					execTime[i+1] = temp;
					
					pids[i] = pids[i+1];
					pids[i+1] = temp2;
				} 
			}
		}
}


