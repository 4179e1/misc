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

void file_client (int readfd, int writefd);
void file_server (int readfd, int writefd);

#endif /* _UTIL_H */
