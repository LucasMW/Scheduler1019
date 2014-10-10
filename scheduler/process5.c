// Grupo : Pedro Augusto (0520253) e Lucas Menezes (1310844)
// PROCESS 5
#include <stdio.h>
#include <math.h>

void main(void)
{
	double i,j,k,t;
	puts("\n\nPROG5 COMECOU\n");
	for(t=0 ; t<10 ; t++)
	{
		printf("EU\tvez %lf\n",t*10);
		for(k=0 ; k<7000 ; k++)
		{
			for(j=0 ; j<9000 ; j++)
			{
				for(i=0 ; i<1000 ; i++)
				{
					i=i*i*i*i;
				}
			}
		}
	}

	puts("\n\nPROG5 ACABOU\n");
}
