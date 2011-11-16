#include <stdio.h>
#include <assert.h>
#include "queue.h"

int main (void)
{
	char buf[128];
	ProxyQueue *q;
	ssize_t n, z;
	int i = 0;

	q = proxy_queue_new ();

	while ((n = read (STDIN_FILENO, buf, sizeof(buf))) != 0)
	{
		i++;
		z = proxy_queue_push (q, buf, n);
		assert (z == n);

		n = sizeof (buf) / 2;
		z = proxy_queue_pop (q, buf, &n);
		assert (z == n);

		z = write (STDOUT_FILENO, buf, n);
		assert (z == n);
	}

	while (!proxy_queue_is_empty (q))
	{
		n = sizeof (buf) / 2;
		z = proxy_queue_pop (q, buf, &n);
		assert (z == n);

		z = write (STDOUT_FILENO, buf, n);
		assert (z == n);
	}

	proxy_queue_free (q);

	return 0;
}
