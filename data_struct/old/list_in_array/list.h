#ifndef _LIST_H_
#define _LIST_H_

typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ListElementType;

void InitializeCursorSpace (void);

List CreateList (void);
int IsEmpty (List L);
int IsLast (Position P, List L);
Position Find (ListElementType X, List L);
void Delete (ListElementType X, List L);
Position FindPrevious (ListElementType X, List L);
void Insert (ListElementType X, List L, Position P);
void DeleteList (List L);
Position Header (List L);
Position First (List L);
Position Advance (Position P);
ListElementType Retrieve (Position P);	/* ElementType Retrieve (Position P), that is data type of Element in struct Node */

#endif /* _LIST_H_ */

struct Node
{
	ListElementType Element;
	Position Next;
};

#define SPACESIZE (100)
struct Node CursorSpace [SPACESIZE];
