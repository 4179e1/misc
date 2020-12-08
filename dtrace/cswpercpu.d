#!/usr/sbin/dtrace -qs

/* Print number of context switches per CPU once per second */

#pragma D option quiet

dtrace:::BEGIN
{
	printf ("%-25s %5s %15s", "Timestamp", "CPU", "Ncsw");
}

sched:::on-cpu
{
	/* Convert the cpunumber to a string */
	cpustr = lltostr (cpu);
	@n[cpustr] = count();
	@n["total"] = count();
}

profile:::tick-1sec
{
	/* Print the date and time before first result */
	printf ("\n%-25Y", walltimestamp);

	/* Print the aggregated counts for each CPU and the total for all CPUs */
	printa ("%5s %@15d\n                         ", @n);
	
	/* Reset the aggregation */
	clear (@n);
}
