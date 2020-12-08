#ifndef _STACK_H_
#define _STACK_H_

struct StructRecord;
typedef struct StackRecord *Stack;
typedef int StackElementType;

int IsEmpty (Stack S);
int IsFull (Stack S);
Stack CreateStack (int MaxElements);
void DisposeStack (Stack S);
void MakeEmpty (Stack S);
void Push (StackElementType X, Stack S);
StackElementType Top (Stack S);
void Pop (Stack S);
StackElementType TopAndPop (Stack S);

#endif /* _STACK_H_ */

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	StackElementType *Array;
};
