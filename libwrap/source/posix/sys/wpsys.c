#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include "wpposixsys.h"
#include "wpbase.h"

struct passwd *wp_getpwuid (uid_t uid)
{
	struct passwd *pw;
	if ((pw = getpwuid (uid)) == NULL)
		wp_error_sys_warning ("getpwuid error");
	return pw;
}

struct passwd *wp_getpwanam (const char *name)
{
	struct passwd *pw;
	if ((pw = getpwnam (name)) == NULL)
		wp_error_sys_warning ("getpwname error");
	return pw;
}

struct passwd *wp_getpwent (void)
{
	struct passwd *pw;
	if ((pw = getpwent ()) == NULL)
		wp_error_sys_warning ("getpwent error");
	return pw;
}

struct spwd *wp_getspnam (const char *name)
{
	struct spwd *sp;
	if ((sp = getspnam (name)) == NULL)
		wp_error_sys_warning ("getspnam error");
	return sp;
}

struct spwd *wp_getspent (void)
{
	struct spwd *sp;
	if ((sp = getspent ()) == NULL)
		wp_error_sys_warning ("getspent error");
	return sp;
}

struct group *wp_getgrgid (gid_t gid)
{
	struct group *gr;
	if ((gr = getgrgid (gid)) == NULL)
		wp_error_sys_warning ("getgrgid error");
	return gr;
}
struct group *wp_getgrnam (const char *name)
{
	struct group *gr;
	if ((gr = getgrnam (name)) == NULL)
		wp_error_sys_warning ("getgrnam error");
	return gr;
}

struct group *wp_getgrent (void)
{
	struct group *gr;
	if ((gr = getgrent ()) == NULL)
		wp_error_warning ("getgrent error");
	return gr;
}

int wp_getgroups (int gidsetsize, gid_t grouplist[])
{
	int n;
	if ((n = getgroups (gidsetsize, grouplist)) == -1)
		wp_error_sys_warning ("getgroups error");
	return n;
}

int wp_setgroups (int ngroups, const gid_t grouplist[])
{
	int n;
	if ((n = setgroups (ngroups, grouplist)) == -1)
		wp_error_sys_warning ("setgroups error");
	return n;
}

int wp_initgroups (const char *username, gid_t basegid)
{
	int n;
	if ((n = initgroups (username, basegid)) == -1)
		wp_error_sys_warning ("initgroups error");
	return n;
}

int wp_uname (struct utsname *name)
{
	int n;
	if ((n = uname (name)) == -1)
		wp_error_sys_warning ("uname error");
	return n;
}

int wp_gethostname (char *name, int namelen)
{
	int n;
	if ((n = gethostname (name, namelen)) == -1)
		wp_error_sys_warning ("gethostname error");
	return n;
}

int wp_getrlimit (int resource, struct rlimit *rlptr)
{
	int n;
	if ((n = getrlimit (resource, rlptr)) != 0)
		wp_error_sys_warning ("getrlimit error");
	return n;
}

int wp_setrlimit (int resource, const struct rlimit *rlptr)
{
	int n;
	if ((n = setrlimit (resource, rlptr)) != 0)
		wp_error_sys_warning ("setrlimit error");
	return n;
}

pid_t wp_fork (void)
{
	pid_t p;
	if ((p = fork ()) < 0)
		wp_error_sys_warning ("fork error");
	return p;
}

pid_t wp_wait (int *statloc)
{
	pid_t p;
	if ((p = wait (statloc)) == -1)
		wp_error_sys_warning ("wait error");
	return p;
}

pid_t wp_waitpid (pid_t pid, int *statloc, int options)
{
	pid_t p;
	if ((p = waitpid (pid, statloc, options)) == -1)
		wp_error_sys_warning ("waitpid error");
	return p;
}

int wp_setuid (uid_t uid)
{
	int n;
	if ((n = setuid (uid)) ==-1)
		wp_error_sys_warning ("setuid error");
	return n;
}

int wp_setgid (gid_t gid)
{
	int n;
	if ((n = setgid (gid)) == -1)
		wp_error_sys_warning ("setgid error");
	return n;
}

int wp_setreuid (uid_t ruid, uid_t euid)
{
	int n;
	if ((n = setreuid (ruid, euid)) == -1)
		wp_error_sys_warning ("setreuid error");
	return n;
}

int wp_setregid (gid_t rgid, gid_t egid)
{
	int n;
	if ((n = setregid (rgid, egid)) == -1)
		wp_error_sys_warning ("setregid error");
	return n;
}
int wp_seteuid (uid_t uid)
{
	int n;
	if ((n = seteuid (uid)) == -1)
		wp_error_sys_warning ("seteuid error");
	return n;
}

int wp_setegid (gid_t gid)
{
	int n;
	if ((n = setgid (gid)) == -1)
		wp_error_sys_warning ("setegid error");
	return n;
}

int wp_system (const char *cmd)
{
	int n;
	n = system (cmd);
	if (n == -1)
		wp_error_sys_warning ("system error: fork fail");
	else if (n == 127)
		wp_error_sys_warning ("system error: execl error");

	return n;
}

char *wp_getlogin (void)
{
	char *p;
	if ((p = getlogin ()) == NULL)
		wp_error_sys_warning ("getlogin error");
	return p;
}

clock_t wp_times (struct tms *buf)
{
	clock_t t;
	if ((t = times (buf)) == -1)
		wp_error_sys_warning ("times error");
	return t;
}

int wp_setpgid (pid_t pid, pid_t pgid)
{
	int n;
	if ((n = setpgid (pid, pgid)) == -1)
		wp_error_sys_warning ("setpgid error");
	return n;
}

pid_t wp_setsid (void)
{
	pid_t n;
	if ((n = setsid ()) == -1)
		wp_error_sys_warning ("setsid error");
	return n;
}

void (*wp_signal (int signo, void (*func)(int)))(int)
{
	void (*f)(int) ;
	if ((f = signal (signo, func)) == SIG_ERR)
		wp_error_sys_warning ("signal error");
	return f;
}

int wp_kill (pid_t pid, int signo)
{
	int n;
	if ((n = kill (pid, signo)) == -1)
		wp_error_sys_warning ("kill error");
	return n;
}

int wp_raise (int signo)
{
	int n;
	if ((n = raise (signo)) == -1)
		wp_error_sys_warning ("raise error");
	return n;
}

