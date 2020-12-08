#!/usr/sbin/dtrace -qs

/* Count programs invoked by a specified user */
proc::do_execve_common:exec
/uid == $1/
{
	@num[execname] = count();
}
