#include <stdio.h>

char *strdupd(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1); //+1是为了在结尾加上字符'\0'
	if (p != NULL )
		strcpy(p, s);
	return p;
};
