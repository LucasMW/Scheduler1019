#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define EVER ;;
#define CPUTIME 10  //Mileseconds

struct node 
{
     int ini;
     struct node * next;
};



int main (int argc, char** argv)
{
    int status;
    char *Myargs[4];
    Myargs[0]="./process1";
    Myargs[1]="arg0";
    Myargs[2]="arg1";
    Myargs[3]=NULL;
    char * envp[]={NULL};
    int pid1;
    int pid2;
    int cpuTime= CPUTIME*1000; 

    //int i;
    //execl("/home/pedro/SC/scheduler","scheduler","./process1",NULL);
    printf( "Parent %d\n",getpid());
    
    pid1 = fork();
    pid2=  fork();
    printf( "1 %d 2 %d\n",pid1,pid2);
       if (pid1 == 0 && pid2!=0)                // child
       {
                      
                 printf("pid1 %d\n",getpid());	
                //execl("lab4.2.a",NULL);
		//execv("process1",Myargs);
		status = execve("./process1",Myargs,envp);
		printf ("depois da execve no filho");
            
         
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
                      
                status = execve("./process1",Myargs,envp);
		printf ("depois da execve no loop");
                printf("pid2 %d\n",getpid());
		printf("retorno do execve %d\n",status);
                //execl("/home/pedro/SC/scheduler","scheduler","./process1 > p1out.txt",NULL);
		//execv("process1",Myargs);
         
        }
    
}
