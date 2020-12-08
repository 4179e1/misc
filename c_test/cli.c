/**
 *@compile: gcc cli.c -o cli -DARRAY_SIZE=10
 *@output: hello world \
 *		   sizeof array: 40
 */
#include <stdio.h>

int main(void) {
	printf ("hello world\n");

	int array[ARRAY_SIZE];

	printf ("sizeof array: %d", sizeof (array)); 

	return 0;
}
