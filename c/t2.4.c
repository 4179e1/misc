#include <stdio.h>

void squeeze(char s1[], char s2[])
{
	int i, j, k;
	for ( k = 0; s2[k] != '\0'; k++)
	{
		for(i = j = 0; s1[i] != '\0'; i++)
			if ( s1[i] != s2[k] )
			{
				printf("%d,%d\n",i,j);
				s1[j++] = s1[i];
			}
	s1[j] = '\0';
	}
}

main()
{
	char s1[] = "abcde";
	char s2[] = "cd";
	squeeze(s1,s2);
	
	int i;
	for( i = 0; s1[i] != '\0'; i++)
		printf("%d:%c\n",i,s1[i]);

	return 0;
}
