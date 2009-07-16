#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

QueueElementType q, r;

int main (void) {

	Queue queue;
	queue = CreateQueue (100);

	printf ("queue created\n");
	int i;
	for (i = 0; i < 10; i++) {

		q.path = "path";
		q.name = "name";
		q.value = "value";

		Enqueue(q, queue);
	}

	while (!IsEmpty (queue)) {
		r = Front(queue);
		printf ("path: %s name: %s value: %s\n", r.path, r.name, r.value);
		Dequeue (queue);
	}
	return 0;
}
