//
// Pubsub envelop publisher
//

#include "zhelpers.h"

int main (void)
{
	// Prepare our context and publisher
	void *context= zmq_init (1);
	void *publisher = zmq_socket (context, ZMQ_PUB);
	zmq_bind (publisher, "tcp://*:5563");

	while (1)
	{
		// Write two messages, echo with an envelope and content
		s_sendmore (publisher, "A");
		s_send (publisher, "We don't want to see this");
		s_sendmore (publisher, "B");
		s_send (publisher, "We would like to see this");
		sleep (1);
	}

	zmq_close (publisher);
	zmq_term (context);
	return 0;
}
