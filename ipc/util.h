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
#endif /* _UTIL_H */
