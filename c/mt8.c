#include <stdio.h>

main()
{
	char s[10];
	printf("%d\n", s[9] == '\0' ? 1 : 0 );
	printf("%d\n", s[10] == '\0' ? 1 : 0 );

	char v[10] = "";
	printf("%d\n", v[9] == '\0' ? 1 : 0 );
	printf("%d\n", v[1] == '\0' ? 1 : 0 );

	char t[3] = "12";
	printf("%d\n", t[2] == '\0' ? 1 : 0 );

	char u[3] = "123";
	printf("%d\n", u[2] == '\0' ? 1 : 0 );
	return 0;
}
