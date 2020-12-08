#include <stdio.h>


void fw (int f[2][6], int l[2][6], int e[2][7], int a[2][6], int *fs, int *ls)
{
	int j;

	f[0][0] = a[0][0] + e[0][0];
	f[1][0] = a[1][0] + e[1][0];

	int p1, p2;
	for (j = 1; j < 6; j++)
	{
		p1 = f[0][j - 1] + a[0][j];
		p2 = f[1][j - 1] + e[1][j] + a[0][j];
		if (p1 <= p2)
		{
			f[0][j] = p1;
			l[0][j] = 0;
		}
		else
		{
			f[0][j] = p2;
			l[0][j] = 1;
		}
		
		p1 = f[1][j - 1] + a[1][j];
		p2 = f[0][j - 1] + e[0][j] + a[1][j];
		if (p1 <= p2)
		{
			f[1][j] = p1;
			l[1][j] = 1;
		}
		else
		{
			f[1][j] = p2;
			l[1][j] = 0;
		}
	}

	p1 = f[0][5] + e[0][6];
	p2 = f[1][5] + e[1][6];
	if (p1 <= p2)
	{
		*fs = p1;
		*ls = 0;
	}
	else
	{
		*fs = p2;
		*ls = 1;
	}
}

void ps (int cnt, int ls, int l[2][6])
{
	if (cnt == 0)
	{
		return;
	}

	ps (cnt - 1, l[ls][cnt], l);
	printf ("line %d, station %d\n", l[ls][cnt], cnt);

	if (cnt == 5)
	{
		printf ("line %d, station %d\n", ls, cnt + 1);
	}
}

int main (void)
{
	
	int f[2][6];
	int l[2][6];
	
	int e[2][7] = 
	{
		{2, 2, 3, 1, 3, 4, 3},
		{4, 2, 1, 2, 2, 1, 2},
	};
	
	int a[2][6] =
	{
		{7, 9, 3, 4, 8, 4},
		{8, 5, 6, 4, 5, 7},
	};
	
	int fs;
	int ls;


	fw(f, l, e, a, &fs, &ls);
	printf ("ls = %d fs = %d\n", ls, fs);

	//print_station ();
	ps(5, ls, l);

	return 0;
}
