#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define EVER ;;
#define CPUTIME 2000  //Mileseconds

void filhoHandler (int sinal);
void alarmHandler (int sinal);
int scheduler_RR (char **path, int tam);

int pos,procFim=0;// posiçao do processo corrente e o numero dos processo finalizados
int *pids;
int *t_ini,*t_fim,*turnaround;// variaveis para controle do tempo

int main (void)
{
	char *Myargs[3];
	Myargs[0]="process1";
	Myargs[1]="process2";
	Myargs[2]="process3";
		
	int tam = 3;
	
	scheduler_RR (Myargs,tam);
}
void filhoHandler (int sinal)
{
	pids[pos] = -1;
	procFim++;
}

void alarmHandler (int sinal)
{
	if(pids[pos] != -1)
	{
		kill(pids[pos],SIGSTOP);
	}
}

int scheduler_RR (char **path, int tam)
{
    int cpuTime= CPUTIME*1000; 
    // ini da copia	
    int i,j;// contadores
	
 
	for (i=0;i<tam;i++)
	{
		
		pids = (int*) malloc(tam*sizeof(int));
		t_ini = (int*) malloc(tam*sizeof(int));
		t_fim = (int*) malloc(tam*sizeof(int));
		turnaround = (int*) malloc(tam*sizeof(int));

		if(pids == NULL)
		{
			printf ("erro ao alocar - RR");
			exit(1);
			
		}

		pids[i] = fork();

		if(pids[i] == 0)// filho
		{	
			printf ("entre o execv e o kill do processo %d\n",i);
			execl(path[i],path[i],NULL);
			
			kill(pids[i],SIGSTOP);
			sleep(1);			
		}
	}
	
	signal(SIGUSR1, filhoHandler);
	signal(SIGALRM, alarmHandler);
	
	while(procFim < tam)// enquanto o numero de processos que ja acabaram < que o numero de processos nao terminados
	{
		for(pos = 0 ; pos < tam ; pos++ )
		{
			if (pids[pos] == -1) //Se o programa ja acabou, pulamos ele
				continue;	
			t_ini[pos] = (int)time(NULL);
			kill(pids[pos],SIGCONT);
			alarm(1);
			sleep(1);
			
			printf ("dentro do loop RR - %d\n",pos);
			t_fim[pos] = (int)time(NULL);
		}
	}

	for(pos = 0 ; pos < tam ; pos++ )
	{   
   		turnaround[pos] = t_fim[pos]-t_ini[pos];
		printf ("turn around do processo %d é : %d\n",pos,turnaround[pos]);
	}
}
