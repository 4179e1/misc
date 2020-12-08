#include <stdio.h>
#include <stdlib.h>

#define SIZE 32
#define SQLITE_HDR 0x53, 0x51, 0x4c, 0x69, 0x74, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x20, 0x33, 0x00

int main()
{
	FILE *fp;
	int ch;
	char *buffer = (char *)malloc(sizeof(char)*SIZE);

	if((fp=fopen("newfile","rb"))==NULL)
	{
		printf("Error!\n");
		exit(0);
	}
	FILE *fp_org = fp;

//	ch=fgetc(fp);
	int n;
	n = fread(buffer, 1, 2, fp);
	printf("n = %d\n", n);

	int c;

	c = feof(fp);

	printf("c = %d\n", c);

/*	
	if(ch==EOF)
		printf("文件为空\n");
	else
	{
		rewind(fp);
		fread(buffer, 1, SIZE, fp);
		printf("%s\n", buffer);
		char str[] = {SQLITE_HDR};
	
		if(strcmp(buffer, str) == 0)
			printf("same\n");
		printf("文件不为空\n");
	}
*/

	return 0;
} 
