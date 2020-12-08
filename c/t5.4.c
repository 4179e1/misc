#include <stdio.h>

int strend(char *s, char *t);

main()
{
	char s[] = "abcdef";
	char t[] = "def";
	char r[] = "zzv";
	char u[] = "";

	printf("%d\n", strend2(&s, &t));
	printf("%d\n", strend2(&s, &r));
	printf("%d\n", strend2(&s, &u));
	return 0;
}

int strend2(char *s, char *t)
{
	char *bs = s;
	char *bt = t;

	for(; *s; s++)
		;
	for(; *t; t++)
		;

	for(; *s == *t; s--, t--)
		if( t == bt || s == bs )
			break;

	if(*s == *t && t == bt && *s != '\0')
		return 1;
	else
		return 0;
}
