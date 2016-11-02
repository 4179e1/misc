#!/usr/sbin/dtrace -qs
#pragma D option quiet

/* Display the distrubution of I/O throughput for block devices */
/* modprobe sdt for io */

io:::start
{
	start[args[0]->b_edev, args[0]->b_blkno] = timestamp;
}

io:::done
/start[args[0]->b_edev, args[0]->b_blkno]/
{
/*
We want to get an idea of our throughput of this device in KB/sec
but we have values measured in bytes and nanoseconds.
We wnat to cacluate:

bytes / 1024
-------------------------
nanosecondes / 1000000000

As DTrace uses integer arithemtic and the denominator is usually 
between 0 and 1 for most I/O, the calculation as shown will lose
precision, So we restate the fraction as:
bytes         1000000000       bytes * 976562
----------- * ----------- * =  --------------
nanoseconds   1024             nanoseconds

This is easy to cacluate using integer arthmetic.
*/

	this->elapsed = timestamp - start[args[0]->b_edev, args[0]->b_blkno];
	/* b_count, the size for current I/O (once) */
	@[args[1]->dev_statname, args[1]->dev_pathname] =
		quantize ((args[0]->b_bcount * 976562) / this->elapsed);
	start[args[0]->b_edev, args[0]->b_blkno] = 0;
}

END
{
	printa ("%s (%s)\n%@d\n", @);
}
