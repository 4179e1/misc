#!/usr/sbin/dtrace -s

/* dtrace -s target.d -c date */
syscall:::entry
/pid == $target/
{
	@[probefunc] = count();
}
