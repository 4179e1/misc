#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int IsEmpty (Queue Q) {
	return (Q->Size == 0);
}

int IsFull (Queue Q) {
	return (Q->Size == Q->Capacity);
}

Queue CreateQueue (int MaxElements) {
	Queue Q;
	Q = malloc (sizeof(struct QueueRecord));

	if (Q == NULL)
	{
		fprintf (stderr, "ERROR: not engouh space\n");
		exit (1);
	}

	Q->Array = malloc (MaxElements * sizeof (QueueElementType));
	if (Q->Array == NULL)
	{
		fprintf (stderr, "ERROR: not engouh space\n");
		exit (1);
	}

	MakeEmpty (Q);
	Q->Capacity = MaxElements;

	return Q;
}

void DisposeQueue (Queue Q) {
	free (Q->Array);
	free (Q);
}

void MakeEmpty (Queue Q) {
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

static int Succ (int Value, Queue Q)
{
	if (++Value == Q->Capacity)
		Value = 0;
	return Value;
}

void Enqueue (QueueElementType X, Queue Q) {
	QueueElementType tmp;

	if (IsFull (Q))
	{
		fprintf (stderr, "ERROR: Full queue\n");
		exit (1);
	} else {
		Q->Size++;
		Q->Rear = Succ (Q->Rear, Q);

		tmp.path = malloc (strlen (X.path) + 1);
		if (tmp.path == NULL) {
			fprintf (stderr, "Error: not enough space\n");
			exit (1);
		}
		strcpy (tmp.path, X.path);

		tmp.name = malloc (strlen(X.name) +1 );
		if (tmp.name == NULL) {
			fprintf (stderr, "Error: not enough space\n");
			exit (1);
		}		
		strcpy (tmp.name, X.name);


		tmp.value = malloc (strlen(X.value) +1 );
		if (tmp.value == NULL) {
			fprintf (stderr, "Error: not enough space\n");
			exit (1);
		}		
		strcpy (tmp.value, X.value);

		Q->Array[Q->Rear] = tmp;
	}
}

QueueElementType Front (Queue Q) {
	return Q->Array[Q->Front];
}

void Dequeue (Queue Q) {
	if (IsEmpty (Q))
	{
		fprintf (stderr, "ERROR: empty queue\n");
		exit (1);
	} else {
		QueueElementType tmp;
		tmp = Front (Q);
		free (tmp.path);
		free (tmp.name);
		free (tmp.value);
		Q->Size--;
		Q->Front = Succ (Q->Front, Q);
	}
}
