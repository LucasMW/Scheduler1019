#include <stdio.h>
#include <math.h>

void main(void)
{
	double i,j,k,t;
	puts("\n\nPROG3 COMECOU\n");
	for(t=0 ; t<10 ; t++)
	{
		for(k=0 ; k<2000 ; k++)
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

	puts("\n\nPROG3 ACABOU\n");
}
