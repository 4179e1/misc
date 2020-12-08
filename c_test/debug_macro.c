/**
 *@compile gcc debug_macro.c -o debug_macro -DDEBUG
 */
#include <stdio.h>
#include "debug_macro.h"

int main(void) {
	DEBUG_PRINT;
	printf ("Hello World!\n");
	DEBUG_PRINT;

	return 0;
}
