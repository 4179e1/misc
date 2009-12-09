#ifndef _WPPOSIXSYS_H
#define _WPPOSIXSYS_H
#include <pwd.h>
#include <shadow.h>
#include <grp.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/resource.h>

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

/* utilities */
void wp_check_exit_status (int status);
#endif /* _WPPOSIXSYS_H */
