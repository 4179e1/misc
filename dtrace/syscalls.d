#!/usr/sbin/dtrace -qs
/* modprobe systrace */

BEGIN
{
	printf ("%-6s %-4s %-16s %-16s\n", "PID", "UID", "EXECNAME", "FILENAME");
}
syscall::open:entry
{
	printf ("%-6d %-4d %-16s %-16s\n", pid, uid, execname, copyinstr(arg0));
}
