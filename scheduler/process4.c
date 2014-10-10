// Grupo : Pedro Augusto (0520253) e Lucas Menezes (1310844)
// PROCESS 4
#include <stdio.h>
#include <math.h>

void main(void)
{
	double i,j,k,t;
	puts("\n\nPROG4 COMECOU\n");
	for(t=0 ; t<7 ; t++)
	{
		printf("EU\tvez %lf\n",t*10);
		for(k=0 ; 6000 ; k++)
		{
			for(j=0 ; j<10000 ; j++)
			{
				for(i=0 ; i<1000 ; i++)
				{
					i=i*i*i*i;
				}
			}
		}
	}

	puts("\n\nPROG4 ACABOU\n");
}
