#include <stdio.h>
#include <sys/wait.h>

void wp_check_exit_status (int status)
{
	if (WIFEXITED (status))
		printf ("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED (status))
		printf ("abnormal termination, signal number = %d%s\n", WTERMSIG(status), 
#ifdef WCOREDUMP
				WCOREDUMP (status) ? "core file generated" : ""
#else
				""
#endif
			   );
	else if (WIFSTOPPED (status))
		printf ("child stopped, signal number = %d\n", WSTOPSIG (status));
}
