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
