#include <libwp.h>
#include <stdlib.h>
#define MAXLINE 1024

void echo(int connfd) 
{
	size_t n; 
	char buf[MAXLINE]; 
	wp_rio_t *rio;

	rio = wp_rio_new(connfd);
	while((n = wp_rio_readline(rio, buf, MAXLINE)) != 0)
	{
		printf("server received %d bytes\n", n);
		wp_rio_writen(rio, buf, n);
	}
	wp_rio_free (rio);
}

