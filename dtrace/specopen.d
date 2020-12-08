#!/usr/sbin/dtrace -Fs

syscall::open:entry
{
	/*
	 * The call to speculation() creates a new speculation. If this fails,
	 * dtrace will generate an error message indicating the reason for 
	 * the failed speculation(), but subsequent spculative tracing will be
	 * silently discarded.
	 */
	self->spec=speculation();
	speculate (self->spec);
	
	/* 
	 * Because this printf() follows the speculate(), it is being
	 * speculateively traced; it will only appear in the data buffer if the
	 * speculation is subsequently commited.
	 */
	printf ("%s", copyinstr(arg0));
}

syscall::open:return
/self->spec/
{
	/*
	 * To balance the outpyut with the -F option, we want to be sure that
	 * every entry has a matching return. Because we speculated the 
	 * open entry above, we wnat to also specualte the open return.
	 * This is also a convenient time to trace the errno value.
	 */
	speculate(self->spec);
	trace(errno);
}

syscall::open:return
/self->spec && errno != 0/
{
	/*
	 * If errno is non-zero, we want to commit the speculation.
	 */

	commit (self->spec);
	self->spec = 0;
}

syscall::open:return
/self->spec && errno == 0/
{
	/* 
	 * If errno is not set, we discard the speculation.
	 */
	discard (self->spec);
	self->spec = 0;
}



