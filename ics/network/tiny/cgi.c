#if 0

PROG=`basename $0 .c`
case $# in
	0)
		clang -o $PROG -Wall $0
	;;
	1)
		case $1 in 
			test)
				QUERY_STRING="9&7" ./$PROG
			;;
			*)
				echo nothing to do
			;;
		esac
	;;
	*)
		echo nothing to do
	;;
esac

exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

int main (void)
{
	char *buf, *p;
	char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];

	int n1 = 0, n2 = 0;

	if ((buf = getenv ("QUERY_STRING")) != NULL)
	{
		p = strchr (buf, '&');
		*p = '\0';
		strcpy (arg1, buf);
		strcpy (arg2, p + 1);
		n1 = atoi (arg1);
		n2 = atoi (arg2);
	}

	sprintf (content, "Welcome to add.com: ");
	sprintf (content, "%sThe Internet addition portal.\r\n<p>", content);
	sprintf (content, "%sThe answer is: %d + %d = %d\r\n<p>",
			content, n1, n2, n1 + n2);
	sprintf (content, "%sThanks for vistring!\r\n", content);

	printf ("Content-length: %d\r\n", strlen(content));
	printf ("Content-type: text/html\r\n\r\n");

	printf ("%s", content);
	fflush (stdout);

	exit (0);
}
