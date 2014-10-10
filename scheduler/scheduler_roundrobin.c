#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define EVER ;;
#define CPUTIME 50  //Mileseconds
#define ON 1
#define OFF 0
#define DEBUGMSGS OFF
static void filhoHandler (int sinal);
static void alarmHandler (int sinal);
int scheduler_RR (char **path, int tam);
static int isFather (int *pids, int tam);
static int pos,procFim=0;// posiçao do processo corrente e o numero dos processo finalizados
static int *pids;
static int *t_ini,*t_fim,*turnaround=0;// variaveis para controle do tempo
turnaround[pos] += (t_fim[pos]-t_ini[pos]);
static int z;

/*int main (void)
{
	char *Myargs[3];
	Myargs[0]="process1";
	Myargs[1]="process2";
	Myargs[2]="process3";
		
	int tam = 3;
	
	scheduler_RR (Myargs,tam);
}*/
static void filhoHandler (int sinal)
{
	printf ("dentro do sigusr1");
	pids[pos] = -1;
	procFim++;
}

static void alarmHandler (int sinal)
{
	if(DEBUGMSGS)printf ("dentro do alarm");
	if(pids[pos] != -1)
	{
		kill(pids[pos],SIGSTOP);
	}
}

int scheduler_RR (char **path, int tam)
{
	int status;
    int cpuTime= CPUTIME*1000; 
    // ini da copia	
    int i,j;// contadores
	int bol1;
	int result;
	
 		pids = (int*) malloc(tam*sizeof(int));
		t_ini = (int*) malloc(tam*sizeof(int));
		t_fim = (int*) malloc(tam*sizeof(int));
		turnaround = (int*) malloc(tam*sizeof(int));

	for (i=0;i<tam;i++)
	{
		
		if(pids == NULL)
		{
			printf ("erro ao alocar - RR");
			exit(1);
			
		}

		pids[i] = fork();

		if(pids[i] == 0)// filho
		{	
			if(DEBUGMSGS)printf ("entre o execv e o kill do processo %d\n",i);
			execl(path[i],path[i],NULL);
			
			//kill(pids[i],SIGSTOP);
			//kill(pids[i],SIGSTOP);
			//bol1 = WIFSTOPPED(status);
			//printf ("ifstopped %d\n",bol1);
			//sleep(1);			
			exit(1);
		}
		kill(pids[i],SIGSTOP);
				
		
	} //fim do for
			
	signal(SIGUSR1, filhoHandler);
	signal(SIGALRM, alarmHandler);

	if (isFather(pids,tam))
	{
		while(procFim < tam)// enquanto o numero de processos que ja acabaram < que o numero de processos nao terminados
		{
			for(pos = 0 ; pos < tam ; pos++ )
			{
				if (pids[pos] == -1) //Se o programa ja acabou, pulamos ele
					continue;	
				t_ini[pos] = (int)time(NULL);
				kill(pids[pos],SIGCONT);
				usleep(cpuTime);			
				result = waitpid(pids[pos],&status,WNOHANG);
				if(DEBUGMSGS)printf ("result e status %d %d\n",result,status);
				if(result!=0)
				{
					printf ("processo %d terminado\n",pos);
					procFim++;
					pids[pos]=-1;
				}			
				ualarm(cpuTime,0);
					/* equals to alarm in microseconds */			
				//kill(pids[pos],SIGSTOP);		
			
				if(DEBUGMSGS)printf ("dentro do loop RR - %d\n",pos);
				//t_fim[pos] = (int)time(NULL);
				turnaround[pos] += cpuTime;
			
			}// fim do for
		}//fim do while
	}//fim do if pai

	for(pos = 0 ; pos < tam ; pos++ )
	{   
   		
		printf ("turn around do processo %d é : %.3f segundos\n",pos,turnaround[pos]/1000000.0);
	}
}
static int isFather (int *pids,int tam)
{
	int i;
	for (i=0;i<tam;i++)
	{	
		if (pids[i]==0)
		{
			return 0;
		}
	}
	return 1;
}
