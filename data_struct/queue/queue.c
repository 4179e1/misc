#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include "queue.h"

struct _proxy_queue 
{
	off_t		mem_card;
	unsigned int	mem_max;
	off_t		mem_front;
	off_t		mem_rear;
	char		*mem_ptr;

	off_t		hdd_card;
	unsigned int	hdd_max;
	off_t		hdd_front;
	off_t		hdd_rear;
	char		*hdd_ptr;
};

#define MEM_MIN ((off_t)1 << 4)
#define MEM_MAX ((off_t)1 << 32)

#define HDD_MIN ((off_t)1 << 30)
#define HDD_MAX ((off_t)1 << 64)

static off_t next(off_t cur, off_t cnt, off_t size)
{
	return ((cur + cnt) % size);
}

#if 0
static off_t prev(off_t cur, off_t cnt, off_t size)
{
	return ((cur + size - 1) % size);
}
#endif

ProxyQueue *proxy_queue_new (void)
{
	ProxyQueue *q;

	q = malloc (sizeof (ProxyQueue));
	if (q == NULL)
	{
		fprintf (stderr, "%s:%s():%d\n", __FILE__, __func__,__LINE__);
		return NULL;
	}
	
	q->mem_max = MEM_MIN;

	q->mem_ptr = malloc (q->mem_max);
	if (q->mem_ptr == NULL)
	{
		free (q);
		return NULL;
	}

	q->mem_card = 0;
	q->mem_front = 0;
	q->mem_rear = 0;

	q->hdd_card = 0;
	q->hdd_max = 0;
	q->hdd_front = 0;
	q->hdd_rear = 0;
	q->hdd_ptr = 0;


	return q;
}

void proxy_queue_free (ProxyQueue *q)
{
	assert (q != NULL);
	free (q->mem_ptr);
	free (q);
}

ssize_t proxy_queue_push (ProxyQueue *q, char *buf, ssize_t size)
{
	off_t avail;
	off_t tail;

	assert (q != NULL);
	
	avail = q->mem_max - q->mem_card; 


	/* note the equal, while front == rear, it means nothing in queue */
	if (avail <= size)
	{
		char *tmp;
		if (q->mem_max >= MEM_MAX)
		{
			/* extended to max */
			return -1;
		}

		off_t part = q->mem_max - q->mem_front;
		while (avail <= size)
		{
			q->mem_max = q->mem_max << 1;
			avail = q->mem_max - q->mem_card; 
		}
		
		tmp = malloc (q->mem_max);
		if (tmp == NULL)
		{
			return -1;
		}

		//assert (q->mem_front != q->mem_rear);
		if (q->mem_front <= q->mem_rear)
		{
			memcpy (tmp, &(q->mem_ptr[q->mem_front]), q->mem_rear - q->mem_front);
		}
		else
		{
			memcpy (tmp, &(q->mem_ptr[q->mem_front]), part);
			memcpy (&tmp[part], q->mem_ptr, q->mem_rear);
		}

		free (q->mem_ptr);
		q->mem_ptr = tmp;
		q->mem_front = 0;
		q->mem_rear = q->mem_card;
	}

	tail = q->mem_max - q->mem_rear; 
	if (tail > size)
	{
		memcpy (&(q->mem_ptr[q->mem_rear]), buf, size);
	}
	else
	{
		memcpy (&(q->mem_ptr[q->mem_rear]), buf, tail);
		memcpy (q->mem_ptr, &buf[tail], size - tail);
	}
	q->mem_rear = next (q->mem_rear, size, q->mem_max);
	q->mem_card += size;

	return size;
}

ssize_t proxy_queue_pop (ProxyQueue *q, char *buf, ssize_t *size)
{
	assert (q != NULL);
	assert (size != NULL);

	if (*size > q->mem_card)
	{
		*size = q->mem_card;
	}

	if (buf)
	{
		proxy_queue_get_content (q, buf, size);
	}
	
	q->mem_front = next (q->mem_front, *size, q->mem_max);
	q->mem_card -= *size;

	return *size;
}

ssize_t proxy_queue_get_content (ProxyQueue *q, char *buf, ssize_t *size)
{
	off_t tail;

	assert (q != NULL);
	assert (buf != NULL);
	assert (size != NULL);

	if (*size > q->mem_card)
	{
		*size = q->mem_card;
	} 
	
	if (q->mem_front <= q->mem_rear)
	{
		memcpy (buf, &(q->mem_ptr[q->mem_front]), *size);
	}
	else
	{
		tail = q->mem_max - q->mem_front;
		if (tail >= *size)
		{
			memcpy (buf, &(q->mem_ptr[q->mem_front]), *size);
		}
		else
		{
			memcpy (buf, &(q->mem_ptr[q->mem_front]), tail);
			memcpy (&buf[tail], q->mem_ptr, *size - tail);
		}
	}
	
	return *size;
}

off_t proxy_queue_get_size (ProxyQueue *q)
{
	assert (q != NULL);
	return MEM_MAX;
}

off_t proxy_queue_get_card (ProxyQueue *q)
{
	assert (q != NULL);
	return q->mem_card;
}

off_t proxy_queue_get_free_size (ProxyQueue *q)
{
	assert (q != NULL);
	return (MEM_MAX - q->mem_card);
}

bool proxy_queue_is_empty (ProxyQueue *q)
{
	assert (q != NULL);
	return (q->mem_front == q->mem_rear);
}

void proxy_queue_dump (ProxyQueue *q)
{
	assert (q != NULL);
	fprintf (stderr, "<QUEUE mem_max='%jd' mem_card='%jd' mem_front='%jd' mem_rear='%jd' mem_ptr='%#x'>", (intmax_t)(q->mem_max), (intmax_t)(q->mem_card), (intmax_t)(q->mem_front), (intmax_t)(q->mem_rear), (unsigned int)(q->mem_ptr));
	if (q->mem_front < q->mem_rear)
	{
		write (STDERR_FILENO, &(q->mem_ptr[q->mem_front]), q->mem_card);
	}
	else
	{
		off_t tail = q->mem_max - q->mem_front;
		write (STDERR_FILENO, &(q->mem_ptr[q->mem_front]), tail);
		write (STDERR_FILENO, q->mem_ptr, q->mem_rear);
	}
	fprintf (stderr, "</QUEUE>\n");
}
