#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/*
This script take as input DNA sequnces with capital letters [ATCG]. Finds the Open Reading Frame and prints on standard input:
>> Length of input sequences.
>> Position of START codon.
>> Position of END codon
>> Length of ORF.
>> ORF sequence.
*/

int main()
{
	// Declaration of variables
	char seq[100000];
	int length,i,x,START1,STOP1,STOP2,STOP3,START,END;
	int stopPositions[31]; // Array to store positions of STOP codons

	printf("Open Reading Frame(ORF) Finder 2.0. \n\nPlease insert your nucleotide sequence:\n");

	while (scanf("%s", seq)==1) // Code inside this loop processes DNA sequences(input)
	{
		length = strlen(seq);

		// Convert the input sequence to uppercase
		for(i=0; i<length; i++) {seq[i] = toupper(seq[i]);}

		printf("\nSequence: %s\n",seq);

		START1=0;
		STOP1=0;
		STOP2=0;
		STOP3=0;

		// Initialize the array to store positions of STOP codons (making the array "empty")
		for (i = 0; i < 30; i++) {stopPositions[i] = 0;}

		printf("Input Sequence Length: %d\n",length);

		for (i=0; i<length; i++)
		{
			// Check if the input is valid with the proper form and characters.
			if(seq[i] == 'A' || seq[i] == 'T' || seq[i] == 'C'|| seq[i] == 'G')
			{
				// Find the position of the START codon
				if(seq[i] == 'A' && seq[i+1] == 'T' && seq[i+2] == 'G')
				{
					printf("Start codon ATG starts on %d nucleotide.\n", i+1); // i+1 so numbering starts from 1 not 0
					START1++;
					START=i;// Saving the starting position in the variable START.
				}
			}

			else
			{
				printf("ORF-Finder failed. Try again, using capital letters (ATCG) only.\n");
				return 0;// Stops the script.
			}

			if(START1 >= 1) {break;} // Break for loop to continue with step 3.
		}

		// Searching for stop codons with step 3.
		for (i=i; i<length; i+=3)
		{
				// Find and save the position of the STOP codon in the variable END and in the array stopPositions.
				if(seq[i] == 'T' && seq[i+1] == 'A' && seq[i+2] == 'A')	
				{
					STOP1++; 
					stopPositions[STOP1-1]=i;
					END=i;
				}

				else if(seq[i] == 'T' && seq[i+1] == 'A' && seq[i+2] == 'G')	
				{
					STOP2++; 
					stopPositions[10+STOP2-1]=i;
					END=i;
				}

				else if(seq[i] == 'T' && seq[i+1] == 'G' && seq[i+2] == 'A')	
				{
					STOP3++; 
					stopPositions[20+STOP3-1]=i;
					END=i;
				}
		}

		if(START1 == 0) { printf("No Start codon on this sequence has been found\n\n"); }
		else if(STOP1+STOP2+STOP3 == 0)	{ printf("No STOP codon has been found.\n\n"); }

		else if (STOP1+STOP2+STOP3 > 1)	
		{ 
			stopPositions[30]=10000;
			int smallP = 30;// start from an arbitary value

			for(x=0; x<30; x++)
			{
				if(stopPositions[x] !=0 && stopPositions[x]<=stopPositions[smallP])
				{smallP=x;}
			}

			printf("STOP codon %c%c%c ends on %d nucleotide.\n", seq[stopPositions[smallP]],seq[stopPositions[smallP]+1],seq[stopPositions[smallP]+2], stopPositions[smallP]+3); 
			printf("ORF seqeuence length = %d\nThe ORF sequence is: ",stopPositions[smallP]-START+3);
			for(x=START; x<=stopPositions[smallP]+2; x++) 	{printf("%c",seq[x]);}// prints the ORF sequence
			printf("\nThere are more than 1 stop codons.");

			if(STOP1>=1)		
			{	
				printf("\nPositions of TAA:");
				for(x=0; x<=9; x++) {if(stopPositions[x] !=0){printf("%d, ",stopPositions[x]+1);}}
			}

			if(STOP2>=1)
			{
				printf("\nPositions of TAG:");
				for(x=10; x<=19; x++) {if(stopPositions[x] !=0){printf("%d, ",stopPositions[x]+1);}}
			}	

			if(STOP3>=1)
			{
				printf("\nPositions of TGA:");
				for(x=20; x<=29; x++) {if(stopPositions[x] !=0){printf("%d, ",stopPositions[x]+1);}}
			}

			printf("\n\n");
		}

		else if (STOP1+STOP2+STOP3 == 1)
		{
			printf("STOP codon %c%c%c ends on %d nucleotide.\n", seq[END],seq[END+1],seq[END+2], END+3);
			printf("ORF seqeuence length = %d\nThe ORF sequence is: ",END-START+3);
			for(x=START; x<=END+2; x++) 	{printf("%c",seq[x]);}// prints the ORF sequence
			printf("\n\n");
		}
	}
}
