#include <stdio.h>

static int daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;
	int *p;
	
	leap =  year%4 == 0 && year%100 != 0 || year%400 == 0;

	p = daytab[leap];

	while( yearday > *++p)
		yearday -= *p;

	*pmonth = p - daytab[leap];
	*pday = yearday;
}

main()
{
	int pmonth, pday;

	int year = 2000;
	int yearday = 42;

	month_day( year, yearday, &pmonth, &pday );

	printf("%d/%d/%d\n",year, pmonth, pday);

	return 0;
}
