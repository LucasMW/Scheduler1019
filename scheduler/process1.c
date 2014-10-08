#include <stdio.h>

int main (void)
{
	int i,x;
	for (i=0;i<10000000;i++)
	{
		if(i%2==0||i%3==0)
		{
			x= x+i;
		}
		else
		{
			x=x-i;
		}	
	}			
	printf ("termino do processo 1\n");
	return 1;
}
