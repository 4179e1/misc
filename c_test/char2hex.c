#include <stdio.h>

int main (void)
{
	unsigned char c = 0xab;

	char hex1=c/16;
	if (hex1<=9)
		hex1+='0';
	else
		hex1=hex1-10+'A';

	char hex2=c%16;
	if (hex2<=9)
		hex2+='0';
	else
		hex2=hex2-10+'A';

	printf ("0x%c%c\n", hex1, hex2);

	return 0;
}
