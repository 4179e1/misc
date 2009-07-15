#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 16
#define SQLITE_HDR 0x53, 0x51, 0x4c, 0x69, 0x74, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x20, 0x33, 0x00

int main(void)
{
	char *buffer = (char *)malloc(sizeof(char)*SIZE);

	char str[] = {SQLITE_HDR};

	FILE *fp = fopen("test_fill.db", "rb");

	fread(buffer, 1, SIZE, fp);

	printf("%s\n", buffer);

	if(strcmp(buffer, str) == 0)
		printf("same\n");

	fclose(fp);
	return 0;
}
