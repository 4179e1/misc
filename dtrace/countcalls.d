#!/usr/sbin/dtrace -qs

/* Count system calls invoked by a process */

profile:::tick-10s
{
	exit(0);
}

syscall::write:entry, syscall::read:entry, syscall::open:entry
{
	@[strjoin(probefunc, "() calls")] = count();
}
