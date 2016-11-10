syscall::write:entry
{
	self->ts = timestamp;
}

syscall::write:return
/self->ts/
{
	t = timestamp - self->ts;
	@time0[execname] = avg(t);
	@time1[execname] = quantize(t); 
/*	@time2[execname] = lquantize(t, 0, 100, 1); */
	self->ts
}
