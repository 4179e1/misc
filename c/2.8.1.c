#include <stdio.h>

void squeeze(char s[], int c)
{
	int i, j;

	for(i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c )
			s[j++] = s[i];
	s[j] = '\0';
}

main()
{
	char s[] = "abcde";
	int c = 'c';
	squeeze(s,c);
	
	int i;
	for( i = 0; s[i] != '\0'; i++)
		printf("%d:%c\n",i,s[i]);
	return 0;
}
