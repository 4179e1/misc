#include <stdio.h>

struct str
{
	int t;
	char v;
};

union uni {
	int t;
	char v;
} u;

int g = 15;

void fun (int *xp) {
	void (*f)(int*) = fun;

	struct str s = {1, 'a'};

	union uni *up = (union uni *)malloc (sizeof (union uni));

	int *ip[2] = {xp, &g};

	up->v = s.v + 1;	/* 'b' */

	printf ("ip = %p, *ip = %p, **ip = %d\n", ip, *ip, **ip);
	printf ("ip + 1 = %p, ip[1] = %p, *ip[1] = %d\n", ip + 1, ip[1], *ip[1]);
	printf ("&s.v = %p, s.v = '%c'\n", &s.v, s.v);
	printf ("&up->v = %p, up->v = '%c'\n", &up->v, up->v);
	printf ("f = %p\n", f);
	if (--(*xp) > 0)
		f(xp);
}


int main(void)
{
	int x = 2;
	fun (&x);
	return 0;
}
