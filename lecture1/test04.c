#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	char seq[1000];
	int length,i;

	for(i=1; i<=10; i++)
	{
		scanf("%s", seq);
		length = strlen(seq);
		printf("The length of string is %d\n", length);
	}

}


