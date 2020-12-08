//
// Hello World server
// Connect REP socket to tcp://*:5560
// Expects "Hello" from client, replies with "World"
//
#include "zhelpers.h"

int main (void)
{
	void *context = zmq_init (1);

	// Socket to talk to clients
	void *responder = zmq_socket (context, ZMQ_REP);
	zmq_connect (responder, "tcp://localhost:5560");

	while (1)
	{
		// Wait for next request from client
		char *string = s_recv (responder);
		printf ("Received request: [%s]\n", string);
		free (string);

		// Do some 'work'
		sleep (1);

		// Send reply back to client
		s_send (responder, "World");
	}

	zmq_close (responder);
	zmq_term (context);
	return 0;
}
