#include <stdio.h>
#define DEBUG
#include "debug_macro.h"

int main(void) {
	DEBUG_PRINT;
	printf ("Hello World!\n");
	DEBUG_PRINT;

	return 0;
}
