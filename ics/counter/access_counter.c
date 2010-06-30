#include <stdio.h>
#include <stdbool.h>


static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;

void access_counter (unsigned *hi, unsigned *lo)
{
	asm ("rdtsc; movl %%edx, %0; movl %%eax, %1"
			: "=r" (*hi), "=r" (*lo)
			: /* no input */
			: "%edx", "%eax");
}

void start_counter ()
{
	access_counter (&cyc_hi, &cyc_lo);
}

double get_counter ()
{
	unsigned ncyc_hi, ncyc_lo;
	unsigned hi, lo, borrow;
	double result;

	access_counter (&ncyc_hi, &ncyc_lo);

	lo = ncyc_lo - cyc_lo;
	borrow = lo > ncyc_lo;
	hi = ncyc_lo - cyc_hi - borrow;
	result = (double)hi * (1 << 30) * 4 + lo;
	if (result < 0)
	{
		fprintf (stderr, "Error: counter return neg value: %.0f\n", result);
	}
	
	return result;
}

double mhz (bool verbose, int sleeptime)
{
	double rate;
	start_counter ();
	sleep (sleeptime);
	rate = get_counter() / (1e6*sleeptime);
	if (verbose)
	{
		printf ("Processor clock rate ~= %.1f MHz\n", rate);
	}
	return rate;
}

int main (void)
{
	mhz (true, 1);
	return 0;
}
