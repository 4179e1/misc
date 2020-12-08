//
// Hello World client
// Connects REQ socket to tcp://localost:5555
// Sends "Hello" to server, expects "World" back
//
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (void)
{
	void *context = zmq_init (1);

	// Socket to talk to server
	printf ("Connecting to hello world server...\n");
	void *requester = zmq_socket (context, ZMQ_REQ);
	zmq_connect (requester, "tcp://localhost:5555");
	char buf[100];

	int request_nbr;
	for (request_nbr = 0; request_nbr < 10; request_nbr++)
	{
		zmq_msg_t request;
		zmq_msg_init_size (&request, 5);
		memcpy (zmq_msg_data (&request), "Hello", 5);
		printf ("Sending Hello %d...\n", request_nbr);
		zmq_send (requester, &request, 0);
		zmq_msg_close (&request);

		zmq_msg_t reply;
		zmq_msg_init (&reply);
		zmq_recv (requester, &reply, 0);
		//printf ("Received World %d\n", request_nbr);
		snprintf (buf, 6, "%s", (char *)zmq_msg_data (&reply));
		printf ("Receive %s %d\n", buf, request_nbr);

		zmq_msg_close (&reply);
	}
	zmq_close (requester);
	zmq_term (context);
	return 0;
}
