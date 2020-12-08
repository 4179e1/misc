#include <assert.h>
#include <wprt.h>
#include "util.h"

int shmcreate (int argc, char *argv[]);
int shmunlink (int argc, char *argv[]);
int shmread (int argc, char *argv[]);
int shmwrite (int argc, char *argv[]);
static void usage (void);

typedef int (*handler_func_t )(int argc, char** argv);

struct handler {
	const char *name;
	handler_func_t func;
};
typedef struct handler Handler;

Handler handlers[] = 
{
	{"create", shmcreate},
	{"unlink", shmunlink},
	{"read", shmread},
	{"write", shmwrite},
};

int shmcreate (int argc, char *argv[])
{
	int c, fd, flags;
	off_t length;

	flags = O_RDWR | O_CREAT;
	while ((c = getopt (argc, argv, "e")) != -1)
	{
		switch (c)
		{
			case 'e':
				flags |= O_EXCL;
				break;
			default:
				usage();
				return 1;
		}
	}

	if (optind != argc - 2)
	{
		usage();
		return 1;
	}
	length = atoi (argv[optind + 1]);

	fd = wp_shm_open (argv[optind], flags, FILE_MODE);
	wp_ftruncate (fd, length);

	wp_mmap (NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	return 0;
}

int shmunlink (int argc, char *argv[])
{
	if (argc != 2)
	{
		usage();
		return 1;
	}

	wp_shm_unlink (argv[1]);
	return 0;
}

int shmread (int argc, char *argv[])
{ 
	int i, fd;
	struct stat stat;
	unsigned char c, *ptr;

	if (argc != 2)
	{
		usage();
		return 1;
	}

	fd = wp_shm_open (argv[1], O_RDONLY, FILE_MODE);
	wp_fstat (fd, &stat);
	ptr = wp_mmap (NULL, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	wp_close (fd);

	for (i = 0; i < stat.st_size; i++)
		if ((c = *ptr++) != (i % 256))
			wp_critical ("ptr[%d] = %d", i, c);

	return 0;
}

int shmwrite (int argc, char *argv[])
{
	int i, fd;
	struct stat stat;
	unsigned char *ptr;

	if (argc != 2)
	{
		usage();
		return 1;
	}

	fd = wp_shm_open (argv[1], O_RDWR, FILE_MODE);
	wp_fstat (fd, &stat);
	ptr = wp_mmap (NULL, stat.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
	wp_close (fd);

	for (i = 0; i < stat.st_size; i++)
		*ptr++ = i % 256;

	return 0;
}

static void usage (void)
{
	printf ("usage: shmctl <op> <name>\n"
			"              create [-e] <name> <length>\n"
			"              unlink <name>\n"
			"              read <name>\n"
			"              write <name>\n"
			);
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
