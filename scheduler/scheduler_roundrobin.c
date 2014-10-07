#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define EVER ;;
#define CPUTIME 2000  //Mileseconds
int main (int argc, char** argv)
{
    int pid1;
    int pid2;
	int cpuTime= CPUTIME*1000; 
	
    
    //int i;
    if(argc!=1)
    {
        printf("Parametro recebido %s\n",argv[1]);
        return 1;
    }
    printf( "Parent %d\n",getpid());
    pid1 = fork();
    pid2=  fork();
    printf( "1 %d 2 %d\n",pid1,pid2);
       if (pid1 == 0 && pid2!=0)                // child
       {
                      
                 printf("pid1 %d\n",getpid());
                execl("ioBound","ioBound",NULL);
            
         
        }
        else if (pid1 < 0)            // failed to fork
        {
            printf("Fork não deu certo!\n");
            exit(1);
            // Throw exception
        }
                                       // parent
        if (pid2 == 0 && pid1!=0)                // child
       {
                      
                 
                printf("pid2 %d\n",getpid());
                execl("cpuBound1","cpuBound1",NULL);
         
        }
        else if (pid2 < 0)            // failed to fork
        {
            printf("Fork não deu certo!\n");
            exit(2);
            // Throw exception
        }
        else if(pid1!=0 && pid2!=0)
        {    
					printf("Parent pid %d\n",getpid());
		      kill(pid1, SIGSTOP);
		      kill(pid2, SIGSTOP);
		      for(EVER)
		      {
				   	kill(pid1, SIGSTOP);
				    kill(pid2, SIGCONT);
				        //fflush(stdout);
				    printf("Go %d pid2\n",pid2);
				    usleep(cpuTime);
				    kill(pid1, SIGCONT);
				    kill(pid2, SIGSTOP);
				        //fflush(stdout);
				    printf("Go %d pid1\n",pid1);
				    usleep(cpuTime);
        }
        }
}
