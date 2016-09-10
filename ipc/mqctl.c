#include <assert.h>
#include <mqueue.h>
#include "util.h"

int mqcreate (int argc, char *argv[]);
int mqunlink (int argc, char *argv[]);
int mqattr (int argc, char *argv[]);
int mqsend (int argc, char *argv[]);
int mqrecv (int argc, char *argv[]);
static void usage (void);

typedef int (*handler_func_t )(int argc, char** argv);

struct handler {
	const char *name;
	handler_func_t func;
};
typedef struct handler Handler;

Handler handlers[] = 
{
	{"create", mqcreate},
	{"unlink", mqunlink},
	{"attr", mqattr},
	{"send", mqsend},
	{"recv", mqrecv},
};

int mqcreate (int argc, char *argv[])
{
	int c, flags;
	mqd_t mqd;
	struct mq_attr attr = {0};

	flags = O_RDWR | O_CREAT;
	while ((c = getopt (argc, argv, "em:z:")) != -1)
	{
		switch (c) 
		{
			case 'e':
				flags |= O_EXCL;
				break;
			case 'm':
				attr.mq_maxmsg = atol (optarg);
				break;
			case 'z':
				attr.mq_msgsize = atol (optarg);
				break;
			default:
				usage();
		}
	}

	if (optind > argc)
	{
		usage();
		return 1;
	}

	if ((attr.mq_maxmsg != 0 && attr.mq_msgsize == 0) || (attr.mq_maxmsg == 0 && attr.mq_msgsize != 0))
		wp_critical ("must specify bot -m maxmsg and -z msgsize");

	mqd = mq_open (argv[optind], flags, FILE_MODE, (attr.mq_maxmsg != 0) ? &attr : NULL);
	if (mqd == -1)
		wp_critical ("mq_open() failed: %s", strerror (errno));

	mq_close (mqd);
	return 0;
}

int mqunlink (int argc, char *argv[])
{
	if (argc != 2)
	{
		usage();
		return 1;
	}

	if ( mq_unlink (argv[1]) == -1)
	{
		wp_critical ("mq_unlink() failed: %s", strerror (errno));
	}
	return 0;
}

int mqattr (int argc, char *argv[])
{
	mqd_t mqd;
	struct mq_attr attr;
	
	if (argc != 2)
	{
		usage();
		return 1;
	}

	mqd = mq_open (argv[1], O_RDONLY);
	if (mqd == -1)
		wp_critical ("mq_open() failed: %s", strerror (errno));

	mq_getattr (mqd, &attr);
	wp_message ("max #msgs = %ld, max #bytes/msg = %ld, "
				"currently on quque = %ld\n",
				attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

	mq_close (mqd);
	exit (0);
}

int mqsend (int argc, char *argv[])
{
	mqd_t mqd;
	size_t len;
	unsigned int prio;

	if (argc != 4)
	{
		usage();
		return 1;
	}

	len = atoi (argv[2]);
	prio = atoi (argv[3]);

	mqd = mq_open (argv[1], O_WRONLY);
	if (mqd == -1)
		wp_critical ("mq_open() failed: %s", strerror (errno));

	char ptr[len];
	if (mq_send (mqd, ptr, len, prio) == -1)
		wp_critical ("mq_send() failed: %s", strerror (errno));

	return 0;

}

int mqrecv (int argc, char *argv[])
{

	int c, flags;
	mqd_t mqd;
	ssize_t n;
	unsigned int prio;
	struct mq_attr attr;

	flags = O_RDONLY;
	while ((c = getopt (argc, argv, "n")) != -1)
	{
		switch (c)
		{
			case 'n':
				flags |= O_NONBLOCK;
				break;
			default:
				usage();
		}
	}

	if (optind > argc)
	{
		usage();
		return 1;
	}

	mqd = mq_open (argv[optind], flags);
	if (mqd == -1)
		wp_critical ("mq_open() failed: %s", strerror (errno));

	if (mq_getattr (mqd, &attr) == -1)
		wp_critical ("mq_getattr() failed: %s", strerror (errno));

	char buff[attr.mq_msgsize];


	n = mq_receive (mqd, buff, attr.mq_msgsize, &prio);
	if (n == -1)
		wp_critical ("mq_receive() failed: %s", strerror (errno));

	wp_message ("read %ld bytes, priority = %u\n", (long) n, prio);

	
	return 0;
}

static void usage (void)
{
	printf ("usage: mqctl <op> <name>\n"
			"             create [-e] [-n maxsg -z msgsize] <name>\n"
			"             unlink <name>\n"
			"             attr <name>\n"
			"             send <name> <#bytes> <priority>\n"
			"             recv -n <name>\n");
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
