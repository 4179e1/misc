#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libwrap.h>
#include <unistd.h>


#define MAXLINE 1024
#define MAXARGS	128

void eval (char *cmdline);
bool parseline (char *buf, char **argv);
bool buildin_command (char **argv);

int main (int argc, char *argv[])
{
	char cmdline[MAXLINE];

	while (1)
	{
		printf (">");
		wp_fgets (cmdline, MAXLINE, stdin);
		if (feof (stdin))
		{
			exit (0);
		}

		eval (cmdline);
	}
}

void eval (char *cmdline)
{
	char *argv[MAXARGS];
	char buf[MAXLINE];
	bool bg;
	pid_t pid;

	strcpy (buf, cmdline);
	bg = parseline (buf, argv);
	
	if (argv[0] == NULL)
	{
		return;
	}

	if (!buildin_command (argv))
	{
		if ((pid = wp_fork()) == 0)
		{
			if (execvp (argv[0], argv) < 0)
			{
				wp_error_exit (0, "%s: Command not found.\n", argv[0]);
			}
		}
	}

	if (!bg)
	{
		int status;
		wp_waitpid (pid, &status, 0);
	}
	else
	{
		printf ("%d %s", pid, cmdline);
	}
	return;
}

bool buildin_command (char **argv)
{
	if (!strcmp (argv[0], "quit"))
	{
		exit (0);
	}
	if (!strcmp (argv[0], "&"))
	{
		return true;
	}
	return false;
}

bool parseline (char *buf, char **argv) /* buf : input ; argv : output */
{
	char *delim;
	int argc;
	bool bg;

	buf[strlen(buf) - 1] = ' ';
	while (*buf && (*buf == ' '))
	{
		buf++;
	}

	argc = 0;
	while ((delim = strchr (buf, ' ')))
	{
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' '))
		{
			buf++;
		}
	}
	argv[argc] = NULL;

	if (argc == 0)
	{
		return true;	/* ignore empty line, return anything is ok */
	}

	if ((bg = (*argv[argc - 1] == '&')))
	{
		argv [--argc] = NULL;
	}

	return bg;
}
