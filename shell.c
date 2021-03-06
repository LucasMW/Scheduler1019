// Grupo : Pedro Augusto (0520253) e Lucas Menezes (1310844)
// SHELL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler/scheduler_SJF.h"
#include "scheduler/scheduler_roundrobin.h"
#include "scheduler/scheduler_priorities.h"
#define ON 1
#define OFF 0
#define DEBUGMSGS OFF
#define DEFAULTFILELOCATION "entrada.txt"


char* strccat(char * first,char * second)
{ 
	char* newstr;

	newstr=(char*)malloc(strlen(first)+strlen(second)+3); //2 NULL + 1 ' '
	if(!newstr)
	{
		printf("couldn't alloc\n");
		exit(01);
	}

 	strcpy(newstr,first);
 	newstr[strlen(first)]=' ';
 	strcpy(newstr+strlen(first)+1,second);

	return newstr;
}

char* getfilemsg(char* path)
{
	FILE* input;
	int i=0;
	char c;
	char* msg;
	input=fopen(path,"rt");
	if(!input)
	{
		printf("File Interpreter: File %s Not Found \n",path);
		exit(02);
	}
	while(fscanf(input,"%c",&c)!=EOF)
	{
		i++;
	}
	msg=(char*)malloc(i+1); 	
	i=0;
	rewind(input);
	while(fscanf(input,"%c",&c)!=EOF)
	{
		msg[i]=c;
		i++;
	}
	msg[i]=0; //null
	return msg;

}
void FileInterpreter(char* path)
{
	FILE * input;
	char** lines;
	char* filestr;
	char ** prognames;
	int * exectimes;
	int * priorities;
	char *p;
	char c;
	int i,tam,spaces,j;
	char stropr[2560];
	char mode=0;
	
	input=fopen(path,"rt");
	if(!input)
	{
	printf("File Interpreter: File %s Not Found \n",path);
		exit(02);
	}
	i=0;
	while(fgets (stropr , 255 ,input) != NULL)
	{	
		if(DEBUGMSGS)printf("%s\nstrlen=%d",stropr,strlen(stropr));
		i++;
	}
	tam=i;
	lines=(char**)malloc(sizeof(char)*i+1);
	rewind(input);
	for(i=0; fgets (stropr , 255 ,input)!= NULL; i++)
	{	
		
		stropr[strlen(stropr)-1]=0; //null
		lines[i]=malloc(sizeof(char)*strlen(stropr)+1);
		strcpy(lines[i],stropr); //copy to lines[i]
		
	}
	printf("%d\n",tam);
	for(i=0;i<tam;i++)
	{	
		if(DEBUGMSGS)printf("Linha%d: %s\n",i,lines[i]);
    }   
	
     //fclose (input);

	for(i=0,j=0;i<tam;i++)
	{	
		if(strncmp(lines[i],"exec",4)==0)
		{	
			if(DEBUGMSGS)printf("OK\n");
			if(strstr(lines[i],"tempoexec="))
			{	if(DEBUGMSGS)printf("SJF\n");
				mode=1;
			}
			else if (strstr(lines[i],"prioridade="))
			{	if(DEBUGMSGS)printf("Prioridade\n");
				mode=2;
			}
			else
			{	if(DEBUGMSGS)printf("RR\n");
				mode=3;
			}
			
		}
		else
		{
			if(DEBUGMSGS)printf("Fail\n");
			j++;
		}
		
		
		
		
    }  
	if(j)
			printf("entry corrupted\n"); 
	prognames=(char**)malloc(sizeof(char*)*tam);
	exectimes=(int*)malloc(sizeof(int)*tam);
	priorities=(int*)malloc(sizeof(int)*tam);
	if(DEBUGMSGS)printf("mode %d\n",mode);
	switch(mode)
	{
		case 1:
		for(i=0;i<tam;i++)
		{
			p=strstr(lines[i],"tempoexec=");
			prognames[i]=(char*)malloc(strlen(lines[i]+strlen("exec ")));
			
			strncpy(prognames[i],lines[i]+strlen("exec "),(p-(lines[i]+strlen("exec "))-1)); //Elimina o espaço
			exectimes[i]=atoi(p+strlen("tempoexec="));
			
			
		}
		for(i=0;i<tam;i++)
		{
			if(DEBUGMSGS)printf("prog[%d]: %s\n%d\n",i,prognames[i],strlen(prognames[i]));
			for(c=0,p=prognames[i];*p;p++,c++)
			{      
				if(DEBUGMSGS)printf("%d<",c);
				if(isprint(*p))
				  
					if(DEBUGMSGS)printf("%c>",*p);
				
				else
					if(DEBUGMSGS)printf("Detected\n");
			}
			if(DEBUGMSGS)printf("\n");
		}
		for(i=0;i<tam;i++)
		{
			if(DEBUGMSGS)printf("time[%d]: %d\n",i,exectimes[i]);
		}
		if(DEBUGMSGS)printf("CALL SJF\n");
		scheduler_SJF(exectimes,prognames,tam);
		break;
		case 2:
		for(i=0;i<tam;i++)
		{
			p=strstr(lines[i],"prioridade=");
			prognames[i]=(char*)malloc(strlen(lines[i]+strlen("exec ")));
			
			strncpy(prognames[i],lines[i]+strlen("exec "),(p-(lines[i]+strlen("exec "))-1)); //Elimina o espaço
			
			priorities[i]=atoi(p+strlen("prioridade="));
			
			
		}
		for(i=0;i<tam;i++)
		{
			if(DEBUGMSGS)printf("prog[%d]: %s\n",i,prognames[i]);
			
		}
		for(i=0;i<tam;i++)
		{
			if(DEBUGMSGS)printf("time[%d]: %d\n",i,priorities[i]);
		}
		if(DEBUGMSGS)printf("CALL PL\n");
		scheduler_PL(priorities,prognames,tam);
			
		break;
		case 3:
		for(i=0;i<tam;i++)
		{
		prognames[i]=(char*)malloc(strlen(lines[i]+strlen("exec ")));
		strcpy(prognames[i],lines[i]+strlen("exec "));
		}
		for(i=0;i<tam;i++)
		{
			if(DEBUGMSGS)printf("prog[%d]: %s\n",i,prognames[i]);
		}
		scheduler_RR(prognames,tam);
			
		break;
		
	}	
	if(DEBUGMSGS)printf("shd\n");



} 


int main (int argc, char** argv)
{
	int i;
	int schPid;
	if(argc>1)
	{
		if(strcmp(argv[1],"-interpreter")==0)
		{
			if(argc<3)
			FileInterpreter(DEFAULTFILELOCATION);
			else
			FileInterpreter(argv[2]);
		return 0;	
		}
		
	}
	
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
				
			
			
			execl("scheduler/scheduler_roundrobin","scheduler/scheduler_roundrobin",argv[2],NULL);
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
