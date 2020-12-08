#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "reg.h"
#include "registry.h"
#include "treeview.h"
#include "stack.h"


static char *list[] = {
	"HKEY_CLASSES_ROOT",
	"HKEY_CURRENT_USER",
	"HKEY_LOCAL_MACHINE",
	"HKEY_USERS",
	"HKEY_CURRENT_CONFIG",
	NULL
};

GtkWidget* create_tree_view_and_model (void) {
	GtkCellRenderer *renderer;
	GtkTreeStore *store;
	GtkWidget *view;
	GtkTreeIter toplevel;
	char **lp;

	view = gtk_tree_view_new ();

	renderer = gtk_cell_renderer_text_new ();

/* MODIFY IT: column attributes */
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"项目",
												renderer,
												"text", COL_ITEM,
												NULL);

/* END OF column attributes */


/* MODIFY IT: column data types */
	store = gtk_tree_store_new (COL_TREE_VIEW, G_TYPE_STRING);
	for (lp = list; *lp != NULL; lp++) {
		gtk_tree_store_append (store, &toplevel, NULL);
		gtk_tree_store_set (store, &toplevel,
							COL_ITEM, *lp,
							-1);
	}

/*	
	gtk_tree_store_append (store, &child, &toplevel);
	gtk_tree_store_set (store, &child,
						COL_ITEM, "ORZ",
						-1);

	toplevel = child;
	gtk_tree_store_append (store, &child, &toplevel);
	gtk_tree_store_set (store, &child,
						COL_ITEM, "vvvv",
						-1);
*/						

	gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL (store));

	g_object_unref (store);

	return view;
}

static HKEY get_rootkey (const char *str) {
	HKEY key;

	if (strcmp (str, list[0]) == 0) {
		key = HKEY_CLASSES_ROOT;
	} else if (strcmp (str, list[1]) == 0) {
		key = HKEY_CURRENT_USER;
	} else if (strcmp (str, list[2]) == 0) {
		key = HKEY_LOCAL_MACHINE;
	} else if (strcmp (str, list[3]) == 0) {
		key = HKEY_USERS;
	} else if (strcmp (str, list[4]) == 0) {
		key = HKEY_CURRENT_CONFIG;
	}
	
	return key;
}
			

void on_tree_view_row_activated (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, Reg *reg) {
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreePath *temp_path;

	reg->status = 0;

	HKEY cur_key;

	/* 不初始化数组会导致后面一个奇怪的bug */
	char buf[REG_BUFFSIZE];
	buf[0] = '\0';

	Stack stack;
	stack = CreateStack();

	remove_tree_view (GTK_TREE_VIEW (reg->listview));

	model = gtk_tree_view_get_model (view);

	if (gtk_tree_model_get_iter (model, &iter, path))
	{
		temp_path = gtk_tree_path_copy (path);
		reg->iter = iter;
		if (gtk_tree_model_iter_has_child (model, &iter) ) {
			reg->status = 1;
		}

		gchar *name;

		
		gtk_tree_model_get (model, &iter, COL_NAME, &name, -1);
//		g_print ("%s\n", name);
		Push (name, stack);
		g_free (name);


		while (gtk_tree_path_up (path)) {
			if (gtk_tree_path_get_depth (path) > 0) {
				gtk_tree_model_get_iter (model, &iter, path);

				gtk_tree_model_get (model, &iter, COL_NAME, &name, -1);
//				g_print ("%s\n", name);
				Push (name, stack);
				g_free (name);
			}
		}

		reg->rootkey = get_rootkey (Top (stack));
		Pop (stack);
		
		while (!IsEmpty (stack)) {
//			printf ("%s\n", Top (stack));
			strcat (buf, Top (stack));
			strcat (buf, "\\\\");
			Pop (stack);
		}

		int len = strlen(buf);
		if (len > 2) {
			buf[len - 2] = '\0';
		}

		strcpy (reg->path, buf);

//		printf ("buf: %s\n", buf);

		if ( RegOpenKeyEx(reg->rootkey,
	 		TEXT(buf),
	 		0,
	 		KEY_READ,
	 		&cur_key) == ERROR_SUCCESS
		)
		{
			QueryKey(cur_key, reg);
		}
		RegCloseKey(cur_key);
		
		
		gtk_tree_view_expand_row (GTK_TREE_VIEW (reg->treeview), temp_path, FALSE);

		DisposeStack (stack);
		free (stack);
	}
}

void treestore_insert (Reg *reg, const char *str) {
	GtkTreeStore *store;
	GtkTreeIter child;
	
	store = GTK_TREE_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (reg->treeview)));

	gtk_tree_store_append (store, &child, &(reg->iter));
	gtk_tree_store_set (store, &child,
						COL_ITEM, str,
						-1);
}

void remove_tree_view(GtkTreeView *tree)
{
	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree)));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree));
	
	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
		return;

	gtk_list_store_clear(store);
}
