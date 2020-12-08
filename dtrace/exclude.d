#!/usr/sbin/dtrace -s

/* exclude this dtrace process */
syscall::write:entry
/pid != $pid/
{
	printf ("%s called %s()\n", execname, probefunc);
}
