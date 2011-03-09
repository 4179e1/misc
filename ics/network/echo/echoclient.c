#include <libwp.h>
#include <stdlib.h>
#define MAXLINE 1024

int main(int argc, char **argv) 
{
	int clientfd, port;
	char *host, buf[MAXLINE];
	wp_rio_t *rio;

	if (argc != 3)
	{
		wp_critical("usage: %s <host> <port>\n", argv[0]);
	}
	host = argv[1];
	port = atoi(argv[2]);

	clientfd = wp_open_clientfd(host, port);
	if (clientfd < 0)
	{
		wp_critical ("connect error");
	}
	rio = wp_rio_new (clientfd);

	while (wp_fgets(buf, MAXLINE, stdin) != NULL)
	{
		wp_rio_writen(rio, buf, strlen(buf));
		wp_rio_readlineb(rio, buf, MAXLINE);
		wp_fputs(buf, stdout);
	}
	wp_rio_free (rio);
	wp_close(clientfd);
	exit(0);
}
