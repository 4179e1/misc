#include <stdio.h>

static char hex_list[] = "0123456789ABCDEF";

int main (void)
{
	unsigned char c = 0x00;
	char hex1;
	char hex2;
	int i;

	i=c/16;
	hex1=hex_list[i];

	i=c%16;
	hex2=hex_list[i];

	printf ("0x%c%c\n", hex1, hex2);

	return 0;
}
