#!/usr/sbin/dtrace -qs

BEGIN
{
	printf ("%-4s %-6s %-20s %-10s %s\n", "UID", "PID", "Prog", "Error", "Func");

	/* Assign error names to the associative array error[] */
	error[EPERM]   = "EPERM";    /* Operation not permitted */
	error[ENOENT]  = "ENOENT";   /* No such file or directory */
	error[ESRCH]   = "ESRCH";    /* No such process */
	error[EINTR]   = "EINTR";    /* Interrupted system call */
	error[EIO]     = "EIO";      /* I/O error */
	error[ENXIO]   = "ENXIO";    /* No such device or address */
	error[E2BIG]   = "E2BIG";    /* Argument list too long */
	error[ENOEXEC] = "ENOEXEC";  /* Exec format error */
	error[EBADF]   = "EBADF";    /* Bad file number */
	error[ECHILD]  = "ECHILD";   /* No child processes */
	error[EAGAIN]  = "EAGAIN";   /* Try again or operation would block */
	error[ENOMEM]  = "ENOMEM";   /* Out of memory */
	error[EACCES]  = "EACCES";   /* Permission denied */
	error[EFAULT]  = "EFAULT";   /* Bad address */
	error[ENOTBLK] = "ENOTBLK";  /* Block device required */
	error[EBUSY]   = "EBUSY";    /* Device or resource busy */
	error[EEXIST]  = "EEXIST";   /* File exists */
	error[EXDEV]   = "EXDEV";    /* Cross-device link */
	error[ENODEV]  = "ENODEV";   /* No such device */
	error[ENOTDIR] = "ENOTDIR";  /* Not a directory */
	error[EISDIR]  = "EISDIR";   /* Is a directory */
	error[EINVAL]  = "EINVAL";   /* Invalid argument */
	error[ENFILE]  = "ENFILE";   /* File table overflow */
	error[EMFILE]  = "EMFILE";   /* Too many open files */
	error[ENOTTY]  = "ENOTTY";   /* Not a typewriter */
	error[ETXTBSY] = "ETXTBSY";  /* Text file busy */
	error[EFBIG]   = "EFBIG";    /* File too large */
	error[ENOSPC]  = "ENOSPC";   /* No space left on device */
	error[ESPIPE]  = "ESPIPE";   /* Illegal seek */
	error[EROFS]   = "EROFS";    /* Read-only file system */
	error[EMLINK]  = "EMLINK";   /* Too many links */
	error[EPIPE]   = "EPIPE";    /* Broken pipe */
	error[EDOM]    = "EDOM";     /* Math argument out of domain of func */
	error[ERANGE]  = "ERANGE";   /* Math result not representable */
}

syscall:::return
/errno > 0 && errno <= ERANGE/
{
	printf ("%-4d %-6d %-20s %-10s %s()\n", uid, pid, execname, error[errno], probefunc);
}
