#if 0
${CC-gcc} ${CFLAGS--g -Wall} -o `basename $0 .c` $0
exit $?
#endif

/*
 * this example use an ridicilous way to pass connection fd.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/param.h>


#define SOCK_PATH "/tmp/echo.socket"

void sigchld_handler (int sig)
{
	while (waitpid (-1, 0, WNOHANG) > 0)
		;
	return;
}

union {
	struct cmsghdr cm;
	char control[CMSG_SPACE(sizeof(int))];
} control_un;

int main (int argc, char *argv[])
{
	int s, c, len;
	struct sockaddr_un local, remote;
	char str[128];
	int sockfd[2];

	if (signal (SIGCHLD, sigchld_handler) == SIG_ERR)
	{
		perror ("signal");
		exit (1);
	}

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror ("socket");
		exit (1);
	}

	local.sun_family = AF_UNIX;
	strcpy (local.sun_path, SOCK_PATH);
	unlink (local.sun_path);
	len = strlen (local.sun_path) + sizeof (local.sun_family);
	if (bind(s, (struct sockaddr *)&local, len) == -1)
	{
		perror ("bind");
		exit (1);
	}

	if (listen (s, 5) == -1)
	{
		perror ("listen");
		exit (1);
	}


	if (socketpair (AF_LOCAL, SOCK_STREAM, 0, sockfd) == -1)
	{
		perror ("socketpair");
		exit (1);
	}

	while (1) {

		int done, n;
		socklen_t t;
		pid_t p;

		printf ("Waiting for a connection...\n");
		t = sizeof (remote);
		if ((c = accept (s, (struct sockaddr *)&remote, &t)) == -1)
		{
			perror ("accept");
			exit (1);
		}

		/* parent */
		if ((p = fork ()) > 0 )
		{

			struct msghdr msg;
			struct iovec iov[1];
			struct cmsghdr *cmptr;

			close (sockfd[1]);


			msg.msg_control = control_un.control;
			msg.msg_controllen = sizeof (control_un.control);
			cmptr = CMSG_FIRSTHDR(&msg);
			cmptr->cmsg_len = CMSG_LEN (sizeof (int));
			cmptr->cmsg_level = SOL_SOCKET;
			cmptr->cmsg_type = SCM_RIGHTS;
			*((int *)CMSG_DATA(cmptr)) = c;

			msg.msg_name = NULL;
			msg.msg_namelen = 0;
			
			/*
			 * well, bad address will be reported if NULL msg_iov is NULL
			 * just pass something like null string
			*/
			iov[0].iov_base = "";
			iov[0].iov_len = 1;
			msg.msg_iov = iov;
			msg.msg_iovlen = 1;

			if (sendmsg(sockfd[0], &msg, 0) == -1)
			{
				perror ("sendmsg");
				exit (1);
			}

			close (c);	
		}
		/* child */
		else if (p == 0)
		{
			struct msghdr msg;
			struct iovec iov[1];
			struct cmsghdr *cmptr;
			char iovbuffer[1];

			close (sockfd[0]);
			close (s);
			close (c);

			msg.msg_control = control_un.control;
			msg.msg_controllen = sizeof (control_un.control);
			msg.msg_name = NULL;
			msg.msg_namelen = 0;
			iov[0].iov_base = iovbuffer;
			iov[0].iov_len = sizeof (iovbuffer);
			msg.msg_iov = iov;
			msg.msg_iovlen = 1;

			if ((n = recvmsg (sockfd[1], &msg, 0)) == -1)
			{
				perror ("recvmsg");
				exit (1);
			}

			if ((cmptr = CMSG_FIRSTHDR (&msg)) != NULL &&
				cmptr->cmsg_len == CMSG_LEN (sizeof(int)))
			{
				if (cmptr->cmsg_level != SOL_SOCKET)
				{
					printf ("Control level != SOL_SOCKET\n");
					exit (1);
				}

				if (cmptr->cmsg_type != SCM_RIGHTS)
				{
					printf ("Control type != SCM_RIGHTS\n");
					exit (1);
				}
				c = *((int *) CMSG_DATA (cmptr));
			}
			else
			{
				printf ("fd was not passed\n");
				exit (1);
			}


			printf ("Connected to %s.\n", remote.sun_path);
			done = 0;

			do {
				n = recv (c, str, sizeof (str), 0);
				if (n <= 0) 
				{
					if (n < 0) perror ("recv");
					done = 1;
				}

				if (!done)
					if (send (c, str, n, 0) < 0) 
					{
						perror ("send");
						done = 1;
					}
			} while (!done);

			close (c);
			exit (0);
		}
		else
		{
			perror ("fork");
			exit (1);
		}

	}

	return 0;
}
