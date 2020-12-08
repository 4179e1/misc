#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
	char *word;
	int count;
} keytab[] = {
	"a_b", 0,
	"c_d", 0,
	"char", 0,
	"else", 0,
	"int", 0,
	"void", 0,
	"while", 0,
	"if", 0,
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

#define NKEYS (sizeof(keytab) / sizeof (struct key))

main(int argc, char *argv[])
{
	int n;
	char word[MAXWORD];

	while( getword(word, MAXWORD) != EOF )
	{	printf("%s, over\n", word);
		if ( isalpha( word[0] ) )
			if (( n = binsearch( word, keytab, NKEYS ) ) >= 0 )
					keytab[n].count++;
	}

	for ( n = 0; n < NKEYS; n++ )
		if( keytab[n].count > 0 )
			printf( "%4d %s\n",
					keytab[n].count, keytab[n].word );

	return 0;
}

int binsearch(char *word, struct key keytab[], int n)
{
	int cond;
	int low, high, mid;

	printf("intput search: %s, over\n", word);

	low = 0;
	high = n - 1;

	while( low <= high )
	{
		int mid = ( low + high ) / 2;
		if ((cond = strcmp (word, keytab[mid].word)) < 0 )
			high = mid - 1;
		else if ( cond > 0 )
			low = mid + 1;
		else
		{	
			printf("%s found, return.\n",keytab[mid].word);
			return mid;
		}
	}

	return -1;
}
