#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
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

int wp_sigemptyset (sigset_t *set)
{
	int n;
	if ((n = sigemptyset (set)) == -1)
		wp_error_sys_warning ("sigemptyset error");
	return n;
}

int wp_sigfillset (sigset_t *set)
{
	int n;
	if ((n = sigfillset (set)) == -1)
		wp_error_sys_warning ("sigfillset error");
	return n;
}

int wp_sigaddset (sigset_t *set, int signo)
{
	int n;
	if ((n = sigaddset (set, signo)) == -1)
		wp_error_sys_warning ("sigaddset error");
	return n;
}

int wp_sigdelset (sigset_t *set, int signo)
{
	int n;
	if ((n = sigdelset (set, signo)) == -1)
		wp_error_sys_warning ("sigdelset error");
	return n;
}

int wp_sigismember (const sigset_t *set, int signo)
{
	int n;
	if ((n = sigismember (set, signo)) == -1)
		wp_error_sys_warning ("sigismember fail");
	return n;
}

int wp_sigprocmask (int how, const sigset_t *set, sigset_t *oset)
{
	int n;
	if ((n = sigprocmask (how, set, oset)) == -1)
		wp_error_sys_warning ("sigprocmask error");
	return n;
}

int wp_sigpending (sigset_t *set)
{
	int n;
	if ((n = sigpending (set)) == -1)
		wp_error_sys_warning ("sigpending error");
	return n;
}

int wp_sigaction (int signo, const struct sigaction *act, struct sigaction *oact)
{
	int n;
	if ((n = sigaction (signo, act, oact)) == -1)
		wp_error_sys_warning ("sigaction error");
	return n;
}

int wp_sigsuspend (const sigset_t *sigmask)
{
	int n;
	if ((n = sigsuspend (sigmask)) == -1)
		wp_error_sys_warning ("sigsuspend error");
	return n;
}

int wp_sigwait (const sigset_t *set, int *signop)
{
	int n;
	if ((n = sigwait (set, signop)) != 0)
		wp_error_warning ("sigwait() error: %s", strerror (n));
	return n;
}

ssize_t wp_readv (int filedes, const struct iovec *iov, int iovcnt)
{
	ssize_t n;
	if ((n = readv (filedes, iov, iovcnt)) == -1)
		wp_error_sys_warning ("readv() error");
	return n;
}

ssize_t wp_writev (int filedes, const struct iovec *iov, int iovcnt)
{
	ssize_t n;
	if ((n = writev (filedes, iov, iovcnt)) == -1)
		wp_error_sys_warning ("writev() error");
	return n;
}

void *wp_mmap (void *addr, size_t len, int prot, int flag, int filedes, off_t off)
{
	void *p;
	if ((p = mmap (addr, len, prot, flag, filedes, off)) == MAP_FAILED)
		wp_error_sys_warning ("mmap() error");
	return p;
}

int wp_mprotect (void *addr, size_t len, int prot)
{
	int n;
	if ((n = mprotect (addr, len, prot)) == -1)
		wp_error_sys_warning ("mprotect() error");
	return n;
}

int wp_msync (void *addr, size_t len, int flags)
{
	int n;
	if ((n = msync (addr, len, flags)) == -1)
		wp_error_sys_warning ("msync() error");
	return n;
}

int wp_munmap (caddr_t addr, size_t len)
{
	int n;
	if ((n = munmap (addr, len)) == -1)
		wp_error_sys_warning ("munmap() error");
	return n;
}

int wp_pipe (int filedes[2])
{
	int n;
	if ((n = pipe (filedes)) == -1)
		wp_error_sys_warning ("pipe() error");
	return n;
}

int wp_mkfifo (const char *pathname, mode_t mode)
{
	int n;
	if ((n = mkfifo (pathname, mode)) == -1)
		wp_error_sys_warning ("mkfifo() error");
	return n;
}

key_t wp_ftok (const char *path, int id)
{
	key_t k;
	if ((k = ftok (path, id)) == (key_t)-1)
		wp_error_sys_warning ("ftok() error");
	return k;
}

int wp_msgget (key_t key, int flag)
{
	int n;
	if ((n = msgget (key, flag)) == -1)
		wp_error_sys_warning ("msgget() error");
	return n;
}
int wp_msgctl (int msqid, int cmd, struct msqid_ds *buf)
{
	int n;
	if ((n = msgctl (msqid, cmd, buf)) == -1)
		wp_error_sys_warning ("msgctl() error");
	return n;
}

int wp_msgsnd (int msqid, const void *ptr, size_t nbytes, int flag)
{
	int n;
	if ((n = msgsnd (msqid, ptr, nbytes, flag)) == -1)
		wp_error_sys_warning ("msgsnd() error");
	return n;
}

ssize_t wp_msgrcv (int msqid, void *ptr, size_t nbytes, long type, int flag)
{
	int n;
	if ((n = msgrcv (msqid, ptr, nbytes, type, flag)) == -1)
		wp_error_sys_warning ("msgrcv() error");
	return n;
}

int wp_semget (key_t key, int nsems, int flag)
{
	int n;
	if ((n = semget (key, nsems, flag)) == -1)
		wp_error_warning ("semget() error");
	return n;
}

#if 0
int wp_semctl (int semid, int semnum, int cmd, union semun arg)
{
	int n;
	if ((n = semctl (semid, semnum, cmd, arg)) == -1)
		wp_error_warning ("semctl() error");
	return n;
}
#endif

int wp_semop (int semid, struct sembuf semoparray[], size_t nops)
{
	int n;
	if ((n = semop (semid, semoparray, nops)) == -1)
		wp_error_warning ("semop() error");
	return n;
}

int wp_shmctl (int shmid, int cmd, struct shmid_ds *buf)
{
	int n;
	if ((n = shmctl (shmid, cmd, buf)) == -1)
		wp_error_warning ("shmctl() error");
	return n;
}

void *wp_shmat (int shmid, const void *addr, int flag)
{
	void *p;
	if ((p = shmat (shmid, addr, flag)) == (void *)-1)
		wp_error_warning ("shmat() error");
	return p;
}

int wp_shmdt (void *addr)
{
	int n;
	if ((n = shmdt (addr)) == -1)
		wp_error_warning ("shmdt() error");
	return n;
}
