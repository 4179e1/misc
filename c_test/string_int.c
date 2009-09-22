#include <stdio.h>

enum _num 
{
	ZERO = 0,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
};

struct _ns
{
	int num;
	char *str;
};

struct _ns array[] = 
{
	{ZERO,	"ZERO"},
	{ONE,	"ONE"},
	{TWO,	"TWO"},
	{THREE,	"THREE"},
	{FOUR,	"FOUR"},
	{FIVE,  "FIVE"},
	{SIX,	"SIX"},
	{SEVEN,	"SEVEN"},
	{EIGHT,	"EIGHT"},
	{NINE,	"NINE"},
};

void print_num (int n)
{
	printf ("%s\n", array[n].str);
}

int main(void)
{
	int i;

	do {
		printf ("Input a value: ");
		scanf ("%d", &i);
		print_num (i % 10);
	} while (1);

	return 0;
}
