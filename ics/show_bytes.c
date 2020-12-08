#include <stdio.h>

#define VAL 3490593

void show_bytes (unsigned char *start, int len);
void show_int (int x);
void show_float (float x);
void show_pointer (void *x);

int main(void) {
	int x = VAL;
	show_int (x);
	show_float ((float)x);
	show_pointer (&x);

	return 0;
}

void show_bytes (unsigned char *start, int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf ("%.2x", start[i]);
	}
	printf("\n");
}

void show_int (int x) {
	show_bytes ((unsigned char*)&x, sizeof(int));
}

void show_float (float x) {
	show_bytes ((unsigned char*)&x, sizeof(float));
}

void show_pointer (void *x) {
	show_bytes ((unsigned char *)&x, sizeof(void *));
}
