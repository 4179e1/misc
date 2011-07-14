//
// Task ventilator
// Binds PUSH socket to tcp://localhost:5557
// Sends batch of tasks to workers via that socket
//
#include "zhelpers.h"

int main (void)
{
	void *context = zmq_init (1);

	// Socket to send messages on
	void *sender = zmq_socket (context, ZMQ_PUSH);
	zmq_bind (sender, "tcp://*:5557");

	printf ("Press Enter when the workers are ready: ");
	getchar ();
	printf ("Sending tasks to workers...\n");

	// The first message is "0" and signals start of batch
	s_send (sender, "0");

	// Initialize random number generator
	srandom ((unsigned) time (NULL));

	// Send 100 tasks
	int task_nbr;
	int total_msec = 0;	// Total expected cost
	for (task_nbr = 0; task_nbr < 100; task_nbr++)
	{
		int workload;
		// Ramdom workload from 1 to 100msecs
		workload = randof (100) + 1;
		total_msec += workload;
		char string [100];
		sprintf (string, "%d", workload);
		s_send (sender, string);
	}
	printf ("Total expected cost: %d msec\n", total_msec);
	sleep (1);		//Give ZMQ time to deliver

	zmq_close (sender);
	zmq_term (context);
	return 0;
}
