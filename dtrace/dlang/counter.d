#!/usr/sbin/dtrace -qs

BEGIN
{
	i = 0;
	isum = 0;
}

profile:::tick-1s
{
	@s["sum"] = sum(i);
	@a["avg"] = avg(i);
	@c["count"] = count();
	@min["min"] = min(i);
	@max["max"] = max(i);
	@stddev["stddev"] = stddev (i);
	printf ("i = %d\n", i);
	isum += i;
	i++;
}

END
{
/*
	printa ("%s: %@d\n", @a);
	printa ("%s: %@d\n", @c);
*/

	printf ("Sum = %d\n", isum);
	printf ("Count = %d\n", i);
	printf ("Average = %d\n", isum/i);
}
