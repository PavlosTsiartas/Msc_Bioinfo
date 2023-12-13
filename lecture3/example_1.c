#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	char seq[1000];
	int length,i,count=0;

	scanf("%s", seq);
	length = strlen(seq);
	
	for (i=0; i<length; i++)
	{
		if(seq[i] == 'G' || seq[i] == 'C')
		{count++;}
	}
	
	printf("The GC content is %f\n", (100.0*count) / length );

}


