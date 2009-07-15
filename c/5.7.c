#include <stdio.h>

static int daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	
	leap =  year%4 == 0 && year%100 != 0 || year%400 == 0;

	for( i = 1; yearday > daytab[leap][i]; i++ )
		yearday -= daytab[leap][i];
	*pmonth = i;
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
