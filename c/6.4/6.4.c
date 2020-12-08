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
};

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

#define NKEYS (sizeof(keytab) / sizeof (struct key))

main(int argc, char *argv[])
{
	struct key *p;
	char word[MAXWORD];

	while( getword(word, MAXWORD) != EOF )
		if ( isalpha( word[0] ) )
			if (( p = binsearch( word, keytab, NKEYS ) ) !=NULL )
					p->count++;

	for ( p = keytab; p < keytab + NKEYS; p++ )
		if( p->count > 0 )
			printf( "%4d %s\n",
					p->count, p->word );

	return 0;
}

struct key *binsearch(char *word, struct key *keytab, int n)
{
	int cond;
	struct key *low = &keytab[0];
	struct key *high = &keytab[n-1];
	struct key *mid;

	while( low <= high )
	{
		mid = low + ( high - low ) / 2;
		if ((cond = strcmp (word, mid->word)) < 0 )
			high = mid - 1;
		else if ( cond > 0 )
			low = mid + 1;
		else
			return mid;
	}

	return NULL;
}
