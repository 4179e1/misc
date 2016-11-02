#!/usr/sbin/dtrace -qs

BEGIN
{
	i = 10;
}

profile:::tick-1s
/i > 0/
{
	trace (i--);
}

profile:::tick-1s
/i <= 0/
{
	trace ("blastoff!");
	exit (0);
}
