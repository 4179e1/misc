#include <stdio.h>
#define MAXWORD 100

int getword(char *, int);

main(int argc, char *argv[])
{
	char word[MAXWORD];

	while ( getword(word, MAXWORD) != EOF) 
		printf("%s\n", word);

	return 0;
}
