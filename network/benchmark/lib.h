#ifndef _LIBS_H
#define _LIBS_H

#define MAXN 16484
#define MAXLINE 4096

void sig_int (int signo);
void sig_chld (int signo);
void pr_cpu_time (void);
void web_child (int sockfd);

#endif /* _LIBS_H */

