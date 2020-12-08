#include<stdio.h>
#define MAXLINE 100

void escape(char s[], char t[])
{
	int i, j;

	for( i = j = 0; t[i] != '\0'; i++ )
		switch( t[i] )
		{
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
				break;
		}
	s[j] = '\0';
}

void unescape(char s[], char t[])
{
	int i, j;
	for ( i = j = 0; s[i] != '\0'; i++ )
		if ( s[i] != '\\' )
			t[j++] = s[i];
		else
			switch ( s[i] )
			{
				case 'n':
					t[j++] = '\n';
					break;
				case 't':
					t[j++] = '\t';
					break;
				default:
					t[j++] = '\\';
					t[j++] = s[++i];
					break;
			}
	t[j] = '\0';
}

void printst(char s[])
{
	int i;
	for ( i = 0; s[i] != '\0'; i++ )
		printf("%c",s[i]);
	printf("\n");
}

main()
{
	char t[MAXLINE] = "abc\tdef\nghijk";
	char s[MAXLINE];
	/*
	int i;
	for( i = 0; i < MAXLINE; i++ )
		s[i] = 0;
		*/
	printst(t);

	escape(s,t);
	printst(s);

	unescape(s,t);
	printst(t);
	return 0;
}
