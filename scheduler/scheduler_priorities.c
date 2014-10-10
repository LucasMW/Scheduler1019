// Grupo : Pedro Augusto (0520253) e Lucas Menezes (1310844)
// SCHEDULER POR PRIORIDADE
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
static int getMaximum(int* pri, int tam);

static int pos,procFim=0;// posiçao do processo corrente e o numero dos processo finalizados
static int *pids;
static int *t_ini,*t_fim,*turnaround=0;// variaveis para controle do tempo

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

int scheduler_PL (int* priorities, char **path, int tam)
{
	int status;
    	int cpuTime= CPUTIME*1000; 
  	int i,j;// contadores
	int bol1;
	int result;
	int currentPri;
	currentPri=getMaximum(priorities,tam);
	if(currentPri<-1)
	{	printf("PL: Priority List Currupted\n");
	}
	
 		pids = (int*) malloc(tam*sizeof(int));
		t_ini = (int*) malloc(tam*sizeof(int));
		t_fim = (int*) malloc(tam*sizeof(int));
		turnaround = (int*) malloc(tam*sizeof(int));
		

	for (i=0;i<tam;i++)
	{
		
		if(pids == NULL)
		{
			if(DEBUGMSGS)printf ("erro ao alocar - PL");
			exit(1);
			
		}

		pids[i] = fork();

		if(pids[i] == 0)// filho
		{	
			if(DEBUGMSGS)printf ("entre o execv e o kill do processo %d\n",i);
			if(execl(path[i],path[i],NULL)==-1)
			printf("PL: Coudn't alloc Process\n");
			
			//kill(pids[i],SIGSTOP);
			//kill(pids[i],SIGSTOP);
			//bol1 = WIFSTOPPED(status);
			//printf ("ifstopped %d\n",bol1);
			//sleep(1);			
			exit(1);
		}
		kill(pids[i],SIGSTOP);
				
		
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
			if(priorities[pos]==currentPri) //Somente se for a prioridade da vez
			{	kill(pids[pos],SIGCONT); //Se não for não continue
				usleep(cpuTime);
			}			
			result = waitpid(pids[pos],&status,WNOHANG);
			if(DEBUGMSGS)printf ("result e status %d %d\n",result,status);
			if(result!=0)
			{
				printf ("processo %d terminado\n",pos);
				procFim++;
				pids[pos]=-1;
			}
						
			if(priorities[pos]==currentPri)
			{	ualarm(cpuTime,0);
				if(priorities[pos]>1)
					priorities[pos]--; //prioridade cai
				currentPri=getMaximum(priorities,tam); //Atualize a prioridade corrente			
				
				/* equals to alarm in microseconds */			
			//kill(pids[pos],SIGSTOP);		
			}
			if(DEBUGMSGS)printf ("dentro do loop RR - %d\n",pos);
			//t_fim[pos] = (int)time(NULL);
			turnaround[pos] += cpuTime;
			//printf("currentPri=%d\n",currentPri);
			//printf("pri %d that pri= %d\n",i,priorities[i]);
			
		}
	}

	for(pos = 0 ; pos < tam ; pos++ )
	{   
   		
		printf ("turn around do processo %d é : %.3f segundos\n",pos,turnaround[pos]/1000000.0);
	}
}
static int getMaximum(int* pri,int tam)
{
  int x=-99;
  int i;
	for(i=0;i<tam;i++)
	{
		if(x<pri[i])	
			x=pri[i];
	}
	return x;

}
