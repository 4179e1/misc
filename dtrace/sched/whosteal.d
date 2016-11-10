#!/usr/sbin/dtrace -qs

sched:::dequeue
/args[2]->cpu_id != -1 && cpu != args[2]->cpu_id && (curlwpsinfo->pr_flag &PR_IDLE)/
{
	@[stringof(args[1]->pr_fname), args[2]->cpu_id] = quantize (cpu);
}

END
{
	printa ("%s stolen from CPU %d by:\n@d\n", @);
}
