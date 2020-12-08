#!/usr/sbin/dtrace -qs


sched:::off-cpu
/curlwpsinfo->pr_state == SSLEEP/
{
	self->cpu = cpu;
	self->ts = timestamp;
}

sched:::on-cpu
/self->ts/
{
	@[self->cpu == cpu? "sleep time, no CPU migration" : "sleep time, CPU migration"] = quantize ((timestamp - self->ts) / 1000000);
	self->ts = 0;
	self->cpu = 0;
}
