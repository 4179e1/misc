#include <unistd.h>
#include <stdbool.h>
#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct _proxy_queue ProxyQueue;

ProxyQueue *proxy_queue_new (void);
void proxy_queue_free (ProxyQueue *q);
ssize_t proxy_queue_push (ProxyQueue *q, char *buf, ssize_t size);
ssize_t proxy_queue_pop (ProxyQueue *q, char *buf, ssize_t *size);
ssize_t proxy_queue_get_content (ProxyQueue *q, char *buf, ssize_t *size);
off_t proxy_queue_get_size (ProxyQueue *q);
off_t proxy_queue_get_card (ProxyQueue *q);
off_t proxy_queue_get_free_size (ProxyQueue *q);
bool proxy_queue_is_empty (ProxyQueue *q);
void proxy_queue_dump (ProxyQueue *q);

#endif /* _QUEUE_H */
