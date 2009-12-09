#include "stack.h"
#include "queue.h"

int main(void)
{
	Queue *q;
	q = queue_new (1);
	
	int array[] = {1, 2, 3, 4, 5};
	int i;
	for (i = 0; i < ARRAY_LEN (array); i++)
	{
		queue_push_head (q, &(array[i]));
		queue_dump (q, stdout, NULL);
	}

	printf ("------------------------\n");

#if 1
	while (!queue_is_empty (q))
	{
		printf ("%d", *(int *)(queue_pop_tail (q)));
		queue_dump (q, stdout, NULL);
	}
	printf ("im here");
	//queue_free (q);
#endif	

	return 0;
}
