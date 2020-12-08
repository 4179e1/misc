#!/usr/sbin/dtrace -qs

BEGIN
{
	start = timestamp;
}

sched:::wakeup
/stringof (args[1]->pr_fname) == "firefox"/
{
	@[execname] = lquantize ((timestamp - start) / 1000000000, 0, 10);
}

profile:::tick-1sec
/++x == 10/
{
	exit(0);
}
