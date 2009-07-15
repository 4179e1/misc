#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "6.5.h"

struct tnode *tolloc(void);
char *strdupd(char *s);

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	
	if (p == NULL) {
		p = tolloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if ( cond < 0 )
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);

	return p;
}

struct tnode *tolloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdupd(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1); //+1是为了在结尾加上字符'\0'
	if (p != NULL )
		strcpy(p, s);
	return p;
};

void treeprint( struct tnode *p )
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}
