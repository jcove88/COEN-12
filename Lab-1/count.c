/* Jillian Coveney
 * COEN 12
 * Lab 1
 * Wednesday 2:15pm
 */

#include <stdio.h>
#include <string.h>
#define MAX_WORD_LENGTH 30

//main function
int main(int argc, char *argv[])
{
	FILE *fp;
	char str[MAX_WORD_LENGTH];
	int count = 0;
	//check if name of file was given
	if(argc == 1)	
	{
		printf("You forgot to include the name of the file!/n");
		return 1;
	}
	//open file
	fp = fopen(argv[1], "r");	
	//check for error reading file
	if(fp == NULL)
	{
		printf("Sorry, there was an error in reading the file.\n");
		return 1;
	}
	//loop that counts the the total words in the file
	while(fscanf(fp, "%s", str) == 1)
	{
		count++;
	}
	fclose(fp);
	printf("\nTotal word count is %d\n", count);
	return 0;
}
