#include <stdio.h>
#include "queue.h"

int main (void) {
	
	Queue queue;
	queue = CreateQueue (100);


	int i;
	for (i = 0; i < 10; i++)
	{
		Enqueue (i , queue);
	}

	while (!IsEmpty(queue))
	{
		printf ("%d\n", FrontAndDequeue (queue));
	}

	return 0;
}
