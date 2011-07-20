//
// Durable subscriber
//
#include "zhelpers.h"

int main (void)
{
	void *context = zmq_init (1);

	// Connect our subscriber socket
	void *subscriber = zmq_socket (context, ZMQ_SUB);
	zmq_setsockopt (subscriber, ZMQ_IDENTITY, "Hello", 5);
	zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "", 0);
	zmq_connect (subscriber, "tcp://localhost:5565");

	// Synchronize with publisher
	void *sync = zmq_socket (context, ZMQ_PUSH);
	zmq_connect (sync, "tcp://localhost:5564");
	s_send (sync, "");

	// Get updates, exit when told to do so
	while (1)
	{
		char *string = s_recv (subscriber);
		printf ("%s\n", string);
		if (strcmp (string, "END") == 0)
		{
			free (string);
			break;
		}
		free (string);
	}
	zmq_close (sync);
	zmq_close (subscriber);
	zmq_term (context);
	return 0;
}
