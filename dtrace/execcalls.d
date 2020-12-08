#!/usr/sbin/dtrace -s
/* modprobe sdt */
proc::do_execve_common:exec
{
	printf ("Pid %d(parent) executed %s(child pid %d)\n", ppid, stringof (args[0]), pid);
}
