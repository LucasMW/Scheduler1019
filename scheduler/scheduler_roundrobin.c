#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define EVER ;;
#define CPUTIME 10  //Mileseconds
int main (int argc, char** argv)
{
    int pid1;
    int pid2;
    
    //int i;
    if(argc!=1)
    {
        printf("Esse programa executa apenas os programas pre-configurados\n");
        return 1;
    }
    printf( "Parent %d\n",getpid());
    pid1 = fork();
    pid2=  fork();
    printf( "1 %d 2 %d\n",pid1,pid2);
       if (pid1 == 0 && pid2!=0)                // child
       {
                      
                 printf("pid1 %d\n",getpid());
                execl("lab4.2.a",NULL);
            
         
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
                execl("lab4.2.b",NULL);
         
        }
        else if (pid2 < 0)            // failed to fork
        {
            printf("Fork não deu certo!\n");
            exit(1);
            // Throw exception
        }
        else if(pid1!=0 && pid2!=0)
        {    printf("Parent pid %d\n",getpid());
        //kill(pid1, SIGINT);
        //kill(pid2, SIGINT);
        for(EVER)
        {
        kill(pid1, SIGINT);
        kill(pid2, SIGCONT);
            fflush(stdout);
            printf("Go %d pid2\n",pid2);
        sleep(3);
        kill(pid1, SIGCONT);
        kill(pid2, SIGINT);
            fflush(stdout);
            printf("Go %d pid1\n",pid1);
        sleep(3);
        }
        }
}
