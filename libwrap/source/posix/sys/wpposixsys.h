#ifndef _WPPOSIXSYS_H
#define _WPPOSIXSYS_H
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <sys/times.h>

struct passwd *wp_getpwuid (uid_t uid);
struct passwd *wp_getpwanam (const char *name);
struct passwd *wp_getpwent (void);

struct spwd *wp_getspnam (const char *name);
struct spwd *wp_getspent (void);

struct group *wp_getgrgid (gid_t gid);
struct group *wp_getgrnam (const char *name);
struct group *wp_getgrent (void);

int wp_getgroups (int gidsetsize, gid_t grouplist[]);
int wp_setgroups (int ngroups, const gid_t grouplist[]);
int wp_initgroups (const char *username, gid_t basegid);

int wp_uname (struct utsname *name);
int wp_gethostname (char *name, int namelen);

int wp_getrlimit (int resource, struct rlimit *rlptr);
int wp_setrlimit (int resource, const struct rlimit *rlptr);

pid_t wp_fork (void);
pid_t wp_wait (int *statloc);
pid_t wp_waitpid (pid_t pid, int *statloc, int options);

int wp_setuid (uid_t uid);
int wp_setgid (gid_t gid);
int wp_setreuid (uid_t ruid, uid_t euid);
int wp_setregid (gid_t rgid, gid_t egid);
int wp_seteuid (uid_t uid);
int wp_setegid (gid_t gid);

int wp_system (const char *cmd);

char *wp_getlogin (void);

clock_t wp_times (struct tms *buf);

int wp_setpgid (pid_t pid, pid_t pgid);

pid_t wp_setsid (void);
pid_t wp_getsid (pid_t pid);

void (*wp_signal (int signo, void (*func)(int)))(int);

int wp_kill (pid_t pid, int signo);
int wp_raise (int signo);

int wp_sigemptyset (sigset_t *set);
int wp_sigfillset (sigset_t *set);
int wp_sigaddset (sigset_t *set, int signo);
int wp_sigdelset (sigset_t *set, int signo);
int wp_sigismember (const sigset_t *set, int signo);
int wp_sigprocmask (int how, const sigset_t *set, sigset_t *oset);
int wp_sigpending (sigset_t *set);
int wp_sigaction (int signo, const struct sigaction *act, struct sigaction *oact);

int wp_sigsuspend (const sigset_t *sigmask);

int wp_sigwait (const sigset_t *set, int *signop);
/* utilities */
void wp_check_exit_status (int status);
#endif /* _WPPOSIXSYS_H */
