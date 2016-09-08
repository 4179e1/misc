/* Linux do not support bi-directional pipe */
#include "util.h"

int main (int argc, char *argv[])
{
	int pipe1[2], pipe2[2];
	pid_t childpid;

	wp_pipe (pipe1);
	wp_pipe (pipe2);

	if ((childpid = wp_fork()) == 0)
	{
		wp_close (pipe1[1]);
		wp_close (pipe2[0]);
		file_server_mymsg (pipe1[0], pipe2[1]);
		exit (0);
	}
	
	wp_close (pipe1[0]);
	wp_close (pipe2[1]);

	file_client_mymsg (pipe2[0], pipe1[1]);
	wp_waitpid (childpid, NULL, 0);
	exit (0);
}
