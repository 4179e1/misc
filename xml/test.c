#include <stdio.h>
#include <string.h>

#define MAX_NUM 100

int main()
{	
	char fn[MAX_NUM];
	char *s = "abc";
	char *t = "def";
	
	strcpy(fn, s);
	strcat(fn, t);

	printf("%s\n", fn);

	return 0;
}
