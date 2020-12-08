#!/usr/sbin/dtrace -qs
#pragma D option quiet

profile:::tick-10sec
{
	exit(0);
}

io:::start
{
	iodir = args[0]->b_flags & B_READ ? "READ" : "WRITE";
	start[args[0]->b_edev, args[0]->b_blkno, iodir] = timestamp;
}

io:::done
{

	iodir = args[0]->b_flags & B_READ ? "READ" : "WRITE";
	this->elapsed = timestamp - start[args[0]->b_edev, args[0]->b_blkno, iodir];
	/* b_count, the size for current I/O (once) */
	@[args[1]->dev_statname, args[1]->dev_pathname, iodir] =
		quantize ((args[0]->b_bcount * 976562) / this->elapsed);
	start[args[0]->b_edev, args[0]->b_blkno, iodir] = 0;
}

END
{
	printa ("%s (%s) %s\n%@d\n", @);
}
