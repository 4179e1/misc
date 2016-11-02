#!/usr/sbin/dtrace -qs

/* Display errno and the file name for failed open() calls */

syscall::open:entry
{
	self->filename = copyinstr(arg0);
}

syscall::open:return
/arg0 < 0/
{
	printf ("errno = %-2d file=%s\n", errno, self->filename);
}
