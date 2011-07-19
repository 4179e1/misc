//
// Simple message queuing broker
// Same as request-reply broker but using QUEUE device
#include "zhelpers.h"

int main (void)
{
	void *context = zmq_init (1);
	// Sock facing clients
	void *frontend = zmq_socket (context, ZMQ_ROUTER);
	zmq_bind (frontend, "tcp://*:5559");
	
	// Sock facing services
	void *backend = zmq_socket (context, ZMQ_DEALER);
	zmq_bind (backend, "tcp://*:5560");

	// Start built-in device
	zmq_device (ZMQ_QUEUE, frontend, backend);

	zmq_close (frontend);
	zmq_close (backend);
	zmq_term (context);
	return 0;
}
