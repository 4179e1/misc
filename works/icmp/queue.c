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
	if (IsFull (Q))
	{
		fprintf (stderr, "ERROR: Full queue\n");
		exit (1);
	} else {
		Q->Size++;
		Q->Rear = Succ (Q->Rear, Q);
		Q->Array[Q->Rear] = X;
		/*
		Q->Array[Q->Rear]->time = X->time;
		Q->Array[Q->Rear]->ip = malloc (sizeof (X->ip) + 1);
		strcpy (Q->Array[Q->Rear]->ip, X->ip);
		Q->Array[Q->Rear]->msg = malloc (sizeof (X->msg) + 1);
		strcpy (Q->Array[Q->Rear]->msg, X->msg);
		*/
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
//		free (Q->Array[Q->Front]->ip);
//		free (Q->Array[Q->Front]->msg);
		Q->Size--;
		Q->Front = Succ (Q->Front, Q);
	}
}

QueueElementType FrontAndDequeue (Queue Q) {
	QueueElementType tmp;

	if (IsEmpty (Q))
	{
		fprintf (stderr, "ERROR: empty queue\n");
		exit (1);
	} else {
		tmp = Q->Array[Q->Front];
//		free (Q->Array[Q->Front]->ip);
//		free (Q->Array[Q->Front]->msg);
		Q->Size--;
		Q->Front = Succ (Q->Front, Q);
	}
	return tmp;
}

