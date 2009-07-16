#ifndef _REG_H
#define _REG_H
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <gtk/gtk.h>

#define REG_BUFFSIZE 1024
#define MAX_VALUE_NAME 16383
#define MAX_VALUE 16383

typedef struct {
	HKEY rootkey;
	int status;
	char *path;
	char *progname;
	GtkTreeIter iter;
	GtkTreeSelection *selection;
	GtkWidget *treeview;
	GtkWidget *listview;
} Reg;

enum {
	COL_ITEM = 0,
	COL_TREE_VIEW,
};

enum {
	COL_NAME = 0,
	COL_TYPE,
	COL_DATA,
	COL_LIST_VIEW,
};
#endif
