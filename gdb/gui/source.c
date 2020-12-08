#if 0
${CC-gcc} -g -Wall -o `basename $0 .c` $0 -lncurses
exit
#endif

#define MAXROW 1000
#define MAXCOL 500

#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <signal.h>
#include <stdlib.h>

WINDOW *scrn;
char cmdoutlines[MAXROW][MAXCOL];

int ncmdlines,
    nwinlines,
    winrow,
    cmdstartrow,
    cmdlastrow;

void highlight (void)
{
	int clinenum;
	attron (A_BOLD);
	clinenum = cmdstartrow + winrow;
	mvaddstr (winrow, 0, cmdoutlines[clinenum]);
	attroff (A_BOLD);
	refresh ();
}

void runpsax ()
{
	FILE *p; 
	char ln[MAXCOL];
	int row;
    char *tmp;
	
	p = popen ("ps ax", "r");
	for (row = 0; row < MAXROW; row++)
	{
		tmp = fgets (ln, MAXCOL, p);
		if (tmp == NULL)
		{
			break;
		}
		strncpy (cmdoutlines[row], ln, COLS);
		cmdoutlines[row][MAXCOL - 1] = 0;
	}
	ncmdlines = row;
	fclose (p);
}

void showlastpart (void)
{
	int row;
	clear ();
	if (ncmdlines <= LINES)
	{
		cmdstartrow = 0;
		nwinlines = ncmdlines;
	}
	else
	{
		cmdstartrow = ncmdlines - LINES;
		nwinlines = LINES;
	}

	cmdlastrow = cmdstartrow + nwinlines - 1;
	for (row = cmdstartrow, winrow = 0; row <= cmdlastrow; row++, winrow++)
	{
		mvaddstr (winrow, 0, cmdoutlines[row]);
	}

	refresh ();

	winrow--;

	highlight ();
}

void updown (int inc)
{
	int tmp = winrow + inc;
	if (tmp >= 0 && tmp < LINES)
	{
		mvaddstr (winrow, 0, cmdoutlines[cmdstartrow + winrow]);
		winrow = tmp;
		highlight ();
	}
}

void rerun (void)
{
	runpsax ();
	showlastpart ();
}

void prockill (void)
{
	char *pid;
	pid = strtok (cmdoutlines[cmdstartrow + winrow], " ");
	kill (atoi (pid), 9);

	rerun ();
}

int main (void)
{
	char c;
	scrn = initscr ();
	noecho ();
	cbreak ();
	runpsax ();
	showlastpart ();
	while (1)
	{
		c = getch ();
		if (c == 'u')
		{
			updown (-1);
		}
		else if (c == 'd')
		{
			updown (1);
		}
		else if (c == 'r')
		{
			rerun ();
		}
		else if (c == 'k')
		{
			prockill ();
		}
		else
		{
			break;
		}
	}
	endwin ();
	return 0;
}
