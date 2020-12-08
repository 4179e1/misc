#include <stdio.h>

int getline ( char s[], int lim )
{
	int c, i;
	
	for ( i = 0; i < lim - 1 && ( c = getchar() ) != EOF && c != '\n'; ++i )
		s[i] = c;
	if ( c == '\n' )
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

main()
{
	int day, month, year, time;

	char monthname[20];
	char line[100];

	while(getline(line, sizeof(line)) > 0)
	{
		printf("input: %s\n", line);

		if( sscanf(line, "%d %s %d", &day, monthname, &year) == 3 )
			printf("valid1: %d %s %d", day, monthname, year);
		else if(sscanf(line, "%d/%d/%d", &day, &month, &year) == 3)
			printf("valid3: %s", line);
		else
			printf("invalid: %s\n", line);
	}
}

