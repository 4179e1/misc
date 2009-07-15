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

char *month_name(int n)
{
	static char *name[] = {
		"Illegal month",
		"January", "February", "Macrh",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December"
	};

	return ( n < 1 || n > 12 ) ? name[0] : name[n];
}

main()
{
	int pmonth, pday;

	int year = 2000;
	int yearday = 42;

	month_day( year, yearday, &pmonth, &pday );

	printf("%d/%s/%d\n",year, month_name(pmonth), pday);

	return 0;
}
