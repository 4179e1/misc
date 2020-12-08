#include "unp.h"

char* Fgets (char* ptr, int n, FILE* stream) {
	char *rptr;
	if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream)) {
		err_sys ("fgets error");
	}

	return (rptr);
}

void
Fputs (const char* ptr, FILE* stream) {
	if (fputs (ptr, stream) == EOF) {
		err_sys("fputs error");
	}
}
