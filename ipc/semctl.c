#include <assert.h>
#include <semaphore.h>
#include "util.h"

int semcreate (int argc, char *argv[]);
int semunlink (int argc, char *argv[]);
int semgetval (int argc, char *argv[]);
int semwait (int argc, char *argv[]);
int sempost (int argc, char *argv[]);
static void usage (void);

typedef int (*handler_func_t )(int argc, char** argv);

struct handler {
	const char *name;
	handler_func_t func;
};
typedef struct handler Handler;

Handler handlers[] = 
{
	{"create", semcreate},
	{"unlink", semunlink},
	{"getval", semgetval},
	{"wait",   semwait},
	{"post",   sempost},
};

int semcreate (int argc, char *argv[])
{
	int c, flags;
	sem_t *sem;
	unsigned int value;
	flags = O_RDWR | O_CREAT;
	value = 1;

	while ((c = getopt (argc, argv, "ei:")) != -1)
	{
		switch (c)
		{
			case 'e':
				flags |= O_EXCL;
				break;
			case 'i':
				value = atoi (optarg);
				break;
			default:
				usage();
				return 1;
		}
	}

	if (optind != argc -1)
	{
		usage();
		return 1;
	}

	if ((sem = wp_sem_open (argv[optind], flags, FILE_MODE, value)) == SEM_FAILED)
		wp_sys_critical ("sem_open() error");

	if (wp_sem_close (sem) == -1)
		wp_sys_critical ("sem_close() error");

	return 0;
}

int semunlink (int argc, char *argv[])
{
	if (argc != 2)
	{
		usage();
		return 1;
	}

	if (wp_sem_unlink (argv[1]) == -1)
		wp_sys_critical ("sem_unlink() error");
	return 0;
}

int semgetval (int argc, char *argv[])
{
	sem_t *sem;
	int val;

	if (argc != 2)
	{
		usage();
		return 1;
	}

	if ((sem = wp_sem_open (argv[1], 0, 0, 0)) == SEM_FAILED)
		wp_sys_critical ("sem_open() error");

	if (wp_sem_getvalue (sem, &val) == -1)
		wp_sys_critical ("sem_getvalue() error");

	printf ("value = %d\n", val);
	return 0;
}
	
int semwait (int argc, char *argv[])
{
	sem_t *sem;
	int val;

	if (argc != 2)
	{
		usage();
		return 1;
	}

	if ((sem = wp_sem_open (argv[1], 0, 0, 0)) == SEM_FAILED)
		wp_sys_critical ("sem_open() error");

	if (wp_sem_wait (sem) == -1)
		wp_sys_critical ("sem_wait() error");

	if (wp_sem_getvalue(sem, &val) == -1)
		wp_sys_critical ("sem_getvalue() error");

	printf ("pid %ld has semaphore, value = %d\n", (long) getpid(), val);
//	pause();
	return 0;
}

int sempost (int argc, char *argv[])
{
	sem_t *sem;
	int val;

	if (argc != 2)
	{
		usage();
		return 1;
	}

	if ((sem = wp_sem_open (argv[1], 0, 0, 0)) == SEM_FAILED)
		wp_sys_critical ("sem_open() error");

	if (wp_sem_post (sem) == -1)
		wp_sys_critical ("sem_post() error");

	if (wp_sem_getvalue(sem, &val) == -1)
		wp_sys_critical ("sem_getvalue() error");

	printf ("value = %d\n", val);
	return 0;
}

static void usage (void)
{
	printf ("usage: semctl <op> <name>\n"
			"              create [-e] [-i initialvalue] <name>\n"
			"              unlink <name>\n"
			"              getval <name>\n"
			"              wait <name>\n"
			"              post <name>\n");
}

static handler_func_t get_handler (const char *name)
{
	int i, n = sizeof (handlers)/sizeof(handlers[0]);
	assert (name != NULL);
	
	for (i = 0; i < n; i++)
		if (strcmp (name, handlers[i].name) == 0)
			return handlers[i].func;

	return NULL;
}


int main (int argc, char *argv[])
{

	handler_func_t func;
	if (argc < 3)
	{
		usage();
		return 1;
	}

	func = get_handler (argv[1]);
	if (func == NULL)
	{
		usage ();
		return 1;
	}

	return func (argc - 1, argv + 1);
}
