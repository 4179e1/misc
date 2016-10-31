#!/usr/sbin/dtrace -qs

/* modprobe profile */

BEGIN
{
	i = 0;
}

profile:::tick-1sec
{
	printf ("i = %d\n", ++i);
}

END
{
	printf ("Final: i = %d\n", i);
}

