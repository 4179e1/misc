#!/usr/sbin/dtrace -s

syscall::read:entry
/execname == "firefox"/
{
	self->t = timestamp; /* Initialize a thread-local variable */
}

syscall::read:return
/self->t != 0/
{
	printf ("%s (pid=%d) spent %d microseconds in read()\n", execname, pid, 
((timestamp - self->t)/1000)); /* divided by 1000 for microseconds */
	
	self->t = 0; /* reset the variable */
}
