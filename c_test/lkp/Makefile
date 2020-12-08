all:
	gcc -c lkpsinglefoo.c
	gcc lkpsinglefoo.c -o liblkpsinglefoo.so -shared -fPIC -lc
	LIBRARY_PATH=${LIBRARY_PATH}:./ gcc -o lkpmem lkpmem.c -llkpsinglefoo

run:
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./ ./lkpmem
