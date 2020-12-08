#include <stdio.h>
#include "hidden.h"

int main(void)
{
	Hidden *hide;

	hide = hidden_new (1, 2);

	hid_print (hide);

	seta (hide, geta(hide) * 10);

	hid_print (hide);

	return 0;
}
