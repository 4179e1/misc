#!/usr/sbin/dtrace -qs

syscall::read:entry,
syscall::write:entry
/pid == $1/
{
	printf ("%s(%d, 0x%x, %4d)", probefunc, arg0, arg1, arg2);
}

syscall::read:return,
syscall::write:return
/pid == $1/
{
	/* arg1, the return value, but why not arg0? */
	printf ("\t = %d\n", arg1);
}
