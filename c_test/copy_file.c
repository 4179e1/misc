#include <stdio.h>
#include <stdlib.h>

#define SIZE 8192
int main(void)
{
	char *buffer = (char *)malloc(sizeof(char)*SIZE);
	int numr;
	FILE *sfp = fopen("notepad", "rb");
	FILE *dfp = fopen("df", "wb");

	while(feof(sfp) == 0)
	{
		numr = fread(buffer, 1, SIZE, sfp);
		fwrite(buffer, 1, numr, dfp);
	}
	
	fclose(sfp);
	fclose(dfp);

	return 0;
}
