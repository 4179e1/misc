#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libwp.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#ifndef _UTIL_H
#define _UTIL_H

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define SERV_FIFO "/tmp/ipcserver.fifo"

#define MAXLINE 4096

#define MAXMSGDATA (PIPE_BUF - 2 * sizeof (long))
struct mymsg
{
	long	msg_len;
	long	msg_type;
	char	msg_data[MAXMSGDATA];
};

typedef struct mymsg Mymsg;
#define MSGHDRSIZE (sizeof(Mymsg) - MAXMSGDATA)

ssize_t msg_send (int fd, Mymsg *mptr);
ssize_t msg_recv (int fd, Mymsg *mptr);

void file_client (int readfd, int writefd);
void file_server (int readfd, int writefd);

void file_client_mymsg (int readfd, int writefd);
void file_server_mymsg (int readfd, int writefd);


typedef void (*Sigfunc_rt) (int, siginfo_t *, void *);
Sigfunc_rt signal_rt (int signo, Sigfunc_rt func, sigset_t *mask);


#define MESGSIZE 256 /* max #bytes per message, incl. null at end */
#define NMESG 16 /* max #messages */

struct shmstruct {   /* struct stored in shared memory */
	sem_t mutex;	/* three posix memory-based semaphores */
	sem_t nempty;	
	sem_t nstored;
	int nput;		/* index into msgoff[] for next put */
	long noverflow;	 	/* #overflow by senders */
	sem_t noverflowmutex;	/* mutex for noverflow counter */
	long msgoff[NMESG];		/* offset in shared memory of each message */
	char msgdata [NMESG * MESGSIZE]; 	/* the actual messages */
};

void sleep_us(unsigned int nusecs);


#endif /* _UTIL_H */
