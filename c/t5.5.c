#include <stdio.h>
#include <string.h>

void strncpy2(char *s, char *t, int n)
{
	while(*t && n-- > 0)
		*s++ = *t++;
	*s = '\0';
	while(n-- > 0)
		*s++ = '\0';
}

void strncat2(char *s, char *t, int n)
{
	strncpy2(s+strlen(t),t,n);
}

int strncmp2(char *s, char *t, int n)
{
	for(; *s == *t; s++, t++)
		if( *s == '\0' || *t == '\0' || --n <= 0 )
			return 0;
	return *s - *t;
}

main()
{
	char s[20];
	char t[] = "orz";
	char u[] = "OTL";
	int n = 5;
	int nx = 2;

	strncpy2(s, t, nx);
	printf("%s\n", s);
	strncpy2(s, t, n);
	printf("%s\n", s);


	strncat2(s, t, nx);
	printf("%s\n", s);
	strncat2(s, t, n);
	printf("%s\n", s);
	
	printf("%d\n", strncmp2(s, t, n));
	printf("%d\n", strncmp2(s, t, nx));
	printf("%d\n", strncmp2(t, s, n));
	printf("%d\n", strncmp2(t, s, nx));
	printf("%d\n", strncmp2(t, u, n));
	printf("%d\n", strncmp2(t, u, nx));

	printf("%d\n", strncmp(s, t, n));
	printf("%d\n", strncmp(s, t, nx));
	printf("%d\n", strncmp(t, s, n));
	printf("%d\n", strncmp(t, s, nx));
	printf("%d\n", strncmp(t, u, n));
	printf("%d\n", strncmp(t, u, nx));
}
