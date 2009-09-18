#include <stdio.h>

#define STICK(i_postfix) int int_##(i_postfix)

int main(void) {
	STICK (i);

	return 0;
}
