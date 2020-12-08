#include <stdio.h>

typedef struct	_station_record
{
	int *time;
	int *station;
	int *move;
	int *produce;
	int prepare;
	int exit;
} StationRecord;

void fastest_way (StationRecord record[2], int *fastest_time, int *fastest_line, int n )
{
	int j, p1, p2;
	StationRecord *r1 = &record[0];
	StationRecord *r2 = &record[1];
	r1->time[0] = r1->produce[0] + r1->prepare;
	r2->time[0] = r2->produce[0] + r2->prepare;

	for (j = 1; j < n; j++)
	{
		p1 = r1->time[j - 1] + r1->produce[j];
		p2 = r2->time[j - 1] + r2->move[j - 1] + r1->produce[j];
		if (p1 <= p2)
		{
			r1->time[j] = p1;
			r1->station[j] = 0;
		}
		else
		{
			r1->time[j] = p2;
			r1->station[j] = 1;
		}

		p1 = r2->time[j - 1] + r2->produce[j];
		p2 = r1->time[j - 1] + r1->move[j - 1] + r2->produce[j];
		if (p1 <= p2)
		{
			r2->time[j] = p1;
			r2->station[j] = 1;
		}
		else
		{
			r2->time[j] = p2;
			r2->station[j] = 0;
		}
		//printf ("%d %d\n", r1->time[j], r2->time[j]);
	}

	p1 = r1->time[j - 1] + r1->exit;
	p2 = r2->time[j - 1] + r2->exit;
	if (p1 <= p2)
	{
		*fastest_time = p1;
		*fastest_line = 0;
	}
	else
	{
		*fastest_time = p2;
		*fastest_line = 1;
	}
}

void print_station (StationRecord r[2], int ls, int cnt, int n)
{
	if (cnt == 0)
	{
		return;
	}

	int nls = r[ls].station[cnt];

	print_station (r, nls, cnt - 1, n);

	printf ("line %d, station %d\n", nls, cnt);

	if (cnt == n)
	{
		printf ("line %d, station %d\n", ls, cnt + 1);
	}
}

int main (void)
{
	int len = 6;

	int f1[6];
	int l1[6];
	int m1[6 - 1] = {2, 3, 1, 3, 4};
	int p1[6] = {7, 9, 3, 4, 8, 4}; 

	int f2[6];
	int l2[6];
	int m2[6 - 1] = {2, 1, 2, 2, 1};
	int p2[6] = {8, 5, 6, 4, 5, 7};

	StationRecord sr[2] = 
	{
		{f1, l1, m1, p1, 2, 3},
		{f2, l2, m2, p2, 4, 2},
	};

	int fastest_time;
	int fastest_line;

	fastest_way (&sr[0], &fastest_time, &fastest_line, len);

	printf ("time = %d line = %d\n", fastest_time, fastest_line);

	print_station (&sr[0], fastest_line, len - 1, len - 1);
	
	return 0;
}
