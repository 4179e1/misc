#include <stdio.h>

void g(int m, int n) {
	int x = m;
	int y = n;

	printf ("%d\t%d\n", x, y);
}

void h(void) {
	int x = 1, 2;
	printf ("%d\n", x);
}

void f(void) {
	int a = 1;
	int b = 2;
	int c = 3;

	g((a, b), c);

	h();
}

int main(void) {

	f();
	return 0;
}
