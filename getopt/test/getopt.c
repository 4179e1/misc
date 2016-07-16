#if 0
${CC-gcc} ${CFLAGS--g -Wall} -o `basename $0 .c` $0
exit 0
#endif

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

void usage (char *str)
{
	printf ("usage : %s [-i input] [--verbose] [-s size] [-v] [-o [output]] file\n", str ? str : "");
}

static const struct option myopt[] =
{
	{"input",	required_argument, 	NULL, 'i'},
	{"verbose", no_argument, 		NULL, 0},
	{"size", 	required_argument, 	NULL, 's'},
	{NULL, 		no_argument, 		NULL, 'v'},
	{"output", 	optional_argument, 	NULL, 'o'}
	{0,			0,					0,	0},
};

static char *input = NULL;
static bool verbose = false;
static int size = 0;
static char *output = NULL;
static bool version = false;

int main (int argc, char *argv[])
{
	int opt;
	int index;

	while ((opt = getopt_long (argc, argv, "i:s:vo:", myopt, &index)) != -1)
	{
		switch (opt) {
			case 'i':
				input = optarg;
				break;
			case 's':
				size = atoi (optarg);
				break;
			case 'v':
				version = true;
				break;
			case 'o':
				output = optarg;
				break;
			case 0:
				if (strcmp ("verbose", myopt[index].name) == 0)
				{
					verbose = true;
				}
				break;
			default:
				usage (argv[0]);
				exit (-1);
				break;
		}
	}

	if (input) printf ("input: %s\n", input);
	if (size) printf ("size: %d\n", size);
	if (output) printf ("output: %s\n", output);
	if (verbose) printf ("verbose\n");
	if (version)	printf ("version 0.0.1\n");
	printf ("argc=%d\n", argc);
	if (optind <= argc - 1)
	{
		printf ("target: %s\n", argv[optind]);
	}
	else
	{
		printf ("not specify target\n");
	}

	return 0;
}
