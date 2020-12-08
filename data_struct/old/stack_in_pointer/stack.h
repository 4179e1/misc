#ifndef _STACK_H_
#define _STACK_H_

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int StackElementType;

int IsEmpty (Stack S);
Stack CreateStack (void);
void DisposeStack (Stack S);
void MakeEmpty (Stack S);
void Push (StackElementType X, Stack S);
StackElementType Top (Stack S);
void Pop (Stack S);

#endif /* _STACK_H_ */

struct Node
{
	StackElementType Element;
	PtrToNode Next;
};
