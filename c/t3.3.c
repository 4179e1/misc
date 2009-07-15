#include <stdio.h>

void expand(char s1[], char s2[])
{
	char c;
	int i, j;

	i = j = 0;
	while ( ( c = s1[i++] ) != '\0' )
		if ( s1[i] == '-' && s1[i+1] >= c )
		{
			i++;
			while ( c < s1[i] )
				s2[j++] = c++;
		}
		else
			s2[j++] = c;
	s2[j] = '\0';
}

void prints(char s[])
{
	int i;
	for( i = 0; s[i] != '\0'; i++ )
		printf("%4c",s[i]);
	printf("\n");
}

main()
{
	char s1[] = "0-z";
	char s2[100];
	expand(s1,s2);
	prints(s1);
	prints(s2);
}
