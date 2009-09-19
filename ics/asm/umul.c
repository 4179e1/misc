#include <stdio.h>

int umul (unsigned x, unsigned y, unsigned *dest)
{
	int result;

	asm ("movl %2, %%eax; mull %3; movl %%eax, %0;\
		 	setae %%dl; movzbl %%dl, %1" 
		  : "=r" (*dest), "=r" (result)
		  : "r" (x), "r" (y)
		  : "%eax", "%edx"
		);

	return result;
}

int main(void)
{
#if 0
	unsigned x = 10;
	unsigned y = 20;
#endif

#if 1
	unsigned x = 0xffffffff;
	unsigned y = 0xfffffffe;
#endif
	unsigned result;

	if (umul (x, y, &result) == 0)
	{
		printf ("overflow\n");
	}

	printf ("%u mul %u Result: %d\n", x, y, result);
}
