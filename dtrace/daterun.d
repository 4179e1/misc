#!/usr/sbin/dtrace -s

/* daterun.d -- Display arguments to write() whenever w command were executed */
/*
ssize_t write(int fd, const void *buf, size_t count);

arg0 and arg2 were value-passed parameter, no need to copy
however, arg1 were address-passed parameter, which pointed to user space
so it need to be copied.
*/

syscall::write:entry
/execname == "w"/
{
	printf ("%s(%d, %s, %d)\n", probefunc, arg0, copyinstr(arg1, arg2), arg2);
}
