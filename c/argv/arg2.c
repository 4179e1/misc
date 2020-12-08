#include <stdio.h>

int main(int argc, char *argv[])
{
	int i;

	printf("%c\n",argv[1][1]);
	printf("%c\n",**++argv);

	for(i = 0; i < argc; i++)
		printf("%s\t", argv[i]);

	printf("\n");

	return 0;
}
