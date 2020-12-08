#include <stdio.h>
#include <assert.h>

char hex2int(unsigned char hex) {
	hex = hex - '0';
	if (hex > 9) {
		/*< 0x20, the 6th bit is 1, that is convert all upper letter to lower */
		hex = (hex + '0' - 1) | 0x20;
		hex = hex - 'a' + 11;
	}
	if (hex > 15)
		hex = 0xFF;

	return hex;
}

int main (void)
{
	printf ("%d\n", hex2int('0'));
	printf ("%d\n", hex2int('a'));
	printf ("%d\n", hex2int('A'));
	printf ("%d\n", hex2int('Z'));

	return 0;
}
