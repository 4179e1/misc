#include <stdio.h>

void int_bin (int x)
{
	unsigned i;
	int j;
	unsigned char *p;
	p = (char *)&x;
	p += (sizeof(int) - 1);

	printf ("the binary of %d(0x%08X) is: \n", x, x);

	for (i = 0x80000000, j = 1; i != 0x00000000; i >>= 1, j++)
	{

		if (((j - 1) % 8) == 0)
		{
			printf (" 0x%02X(", *p);
			p--;
		}

		printf ((((x & i) == 0) ? "0" : "1"));

		if ((j % 4) == 0 && (j % 8) != 0)
		{
			printf (", ");
		}

		if ((j % 8) == 0)
		{
			printf (") ");
		}
	}

	printf("\n");
}

int main(void)
{
	int i;

	while (1)
	{
		printf ("\nInput a value: ");
		scanf ("%d", &i);
		int_bin (i);
	}

	return 0;
}
