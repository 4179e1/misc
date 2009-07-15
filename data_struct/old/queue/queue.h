#ifndef _QUEUE_H_
#define _QUEUE_H_

struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int QueueElementType;

int IsEmpty (Queue Q);
int IsFull (Queue Q);
Queue CreateQueue (int MaxElements);
void DisposeQueue (Queue Q);
void MakeEmpty (Queue Q);
void Enqueue (QueueElementType X, Queue Q);
QueueElementType Front (Queue Q);
void Dequeue (Queue Q);
QueueElementType FrontAndDequeue (Queue Q);

#endif /* _QUEUE_H_ */

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	QueueElementType *Array;
};
