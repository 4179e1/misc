#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i = 1;

	if ( *(char *)&i == 1) {
		printf ("Little-endian\n");
	} else {
		printf ("Big-endian\n");
	}

	return 0;
}
