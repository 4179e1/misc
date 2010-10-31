#if 0
gcc -Wall -g -o `basename $0 .c` $0
exit
#endif

int main (void)
{
	int x = 1;
	int y = 2;
	int z;

	z = x + y;

	return 0;
}
