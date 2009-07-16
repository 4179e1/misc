#include <stdio.h>
#include <windows.h>

typedef (*MY_PRINT)(void);

int main()
{
	int *j;
	HINSTANCE hdll = NULL;
	MY_PRINT pmyPrint;
	hdll = LoadLibrary ("libtest.dll");

	pmyPrint = (MY_PRINT)GetProcAddress (hdll, "my_print");

	pmyPrint();

	j = (int *)GetProcAddress (hdll, "i");

	printf ("j = %d\n", *j);

	FreeLibrary (hdll);

	return 0;
}
