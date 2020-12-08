#!/usr/sbin/dtrace -qs

/* usage: define proproceser directive ENNAME
   for exmaple, dtrace -C -D ENAME='"firefox"' -qs fdscount.d
 */

tick-10s
{
	exit(0);
}

syscall::read:entry
/execname==ENAME/
{
	@[fds[arg0].fi_pathname]=count();		/* get name by fd */
}

END
{
	trunc(@,5);	/* display top 5 */
}
