#include <gtk/gtk.h>
#include <assert.h>
#include "database_builder.h"
#include "edit_menu.h"
#include "database.h"
#include "tree.h"
#include "handler.h"

static GtkWidget *add_entry(GtkWidget *vbox, const gchar *text);
static gchar *get_entry (GtkEntry *entry);

enum
{
	RACE = 0,
	CLASS,
	SKILLS,
	FEATS,
	POWERS,
	EQUIPMENT,
	ALIGNMENT,
	DEITIES,
};	

void on_switch_page (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, DatabaseBuilder *builder)
{
	builder->page_index = gtk_notebook_get_current_page (notebook);

	switch (builder->page_index) {
		case RACE:
			builder->tree_view_cur = builder->tree_view_race;
			break;
		case CLASS:
			builder->tree_view_cur = builder->tree_view_class;
			break;
		case SKILLS:
			builder->tree_view_cur = builder->tree_view_skills;
			break;
		case FEATS:
			builder->tree_view_cur = builder->tree_view_feats;
			break;
		case POWERS:
			builder->tree_view_cur = builder->tree_view_powers;
			break;
		case EQUIPMENT:
			builder->tree_view_cur = builder->tree_view_equipment;
			break;
		case ALIGNMENT:
			builder->tree_view_cur = builder->tree_view_alignment;
			break;
		case DEITIES:
			builder->tree_view_cur = builder->tree_view_deities;
			break;
		default:
			assert (FALSE);
			break;
	}

	builder->selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(builder->tree_view_cur));
}

/* Edit->Add */
void on_edit_add_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	switch (builder->page_index) {
		case RACE:
			return;
			break;
		case CLASS:
			return;
			break;
		case SKILLS:
			return;
			break;
		case FEATS:
			return;
			break;
		case POWERS:
			return;
			break;
		case EQUIPMENT:
			return;
			break;
		case ALIGNMENT:
			add_to_alignment(builder, FALSE);
			break;
		case DEITIES:
			return;
			break;
		default:
			assert (FALSE);
			break;
	}
}


/* Edit->Edit */
void on_edit_edit_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	switch (builder->page_index) {
		case RACE:
			return;
			break;
		case CLASS:
			return;
			break;
		case SKILLS:
			return;
			break;
		case FEATS:
			return;
			break;
		case POWERS:
			return;
			break;
		case EQUIPMENT:
			return;
			break;
		case ALIGNMENT:
			add_to_alignment(builder, TRUE);
			break;
		case DEITIES:
			return;
			break;
		default:
			assert (FALSE);
			break;
	}
}


/* Edit->Delete */
void on_edit_delete_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	if(! check ("Do you want to delete selected item?"))
		return;
	GtkTreeIter iter;
	GtkTreeModel *model;
	gchar *value;
	gchar *table = NULL;
	gchar *sql;

	if(!gtk_tree_selection_get_selected(GTK_TREE_SELECTION(builder->selection), &model, &iter)) 
	{
		return;
	}
	else
	{
		gtk_tree_model_get(model, &iter, 0, &value, -1);
	}

	switch (builder->page_index) {
		case RACE:
			return;
			break;
		case CLASS:
			return;
			break;
		case SKILLS:
			return;
			break;
		case FEATS:
			return;
			break;
		case POWERS:
			return;
			break;
		case EQUIPMENT:
			return;
			break;
		case ALIGNMENT:
			table = "alignment";
			break;
		case DEITIES:
			return;
			break;
		default:
			assert (FALSE);
			break;
	}
	
	sql = g_strdup_printf ("DELETE FROM %s WHERE %s = '%s'", table, table, value);
	//delete from "table" where "name" = "name"

	if (exec_sql(builder->filename, sql))
	{
		remove_item(builder->tree_view_cur, builder->selection);
	}

	g_free (sql);
	g_free(value);

}


static GtkWidget *add_entry(GtkWidget *vbox, const gchar *text)
{
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *entry;

	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);

	label = gtk_label_new (text);
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	entry = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 2);

	return entry;

}


static gchar *get_entry (GtkEntry *entry)
{	
	const gchar *text;
	gchar *str = NULL;

	text = gtk_entry_get_text (entry);

	if (g_str_equal ("", text))
		str = g_strdup_printf("%s", "NULL");
	else
		str = g_strdup_printf("'%s'", text);

	return str;
}

typedef struct
{
	GtkWidget *window;
	GtkWidget *entry_alignment;
	GtkWidget *entry_description;
	DatabaseBuilder *builder;
	gboolean edit;
	gchar *value;
} Alignment;

static void on_alignment_destroy (GtkObject *window, Alignment *data)
{
	gtk_widget_destroy (GTK_WIDGET (window));
	g_slice_free (Alignment, data);
}

static void on_alignment_button_clicked (GtkButton *button, Alignment *data)
{
	gchar *sql;
	gchar *alignment;
	gchar *description;
	
	alignment = get_entry (GTK_ENTRY (data->entry_alignment));
	description = get_entry (GTK_ENTRY (data->entry_description));

	if (data->edit)
	{
		sql = g_strdup_printf ("UPDATE alignment SET alignment = %s, description = %s WHERE alignment = '%s';", alignment, description, data->value);
		g_free (data->value);
		//update alignment set alignment = 'zzz', description = 'vvv' where alignment = 'orz'
	}
	else
	{
		sql = g_strdup_printf ("INSERT INTO alignment VALUES (%s, %s);", alignment, description);
	}

	if(exec_sql (data->builder->filename, sql))
	{
		remove_tree_view (GTK_TREE_VIEW (data->builder->tree_view_alignment));
		load_alignment (data->builder);
	}

	gtk_widget_destroy (data->window);

	g_free (sql);
	g_free (alignment);
	g_free (description);
}

void add_to_alignment(DatabaseBuilder *builder, gboolean edit)
{
	Alignment *data;
	data = g_slice_new(Alignment);

	GtkWidget *vbox;
	GtkWidget *button;

	data->builder = builder;
	data->edit = edit;

	data->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_transient_for (GTK_WINDOW (data->window), GTK_WINDOW (builder->window));
	gtk_window_set_position (GTK_WINDOW (data->window), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_title (GTK_WINDOW (data->window), "Input datas");
//	gtk_widget_set_size_request (data->window, 400, 300);
	gtk_container_set_border_width (GTK_CONTAINER (data->window), 20);

	vbox = gtk_vbox_new (TRUE, 5);
	gtk_container_add (GTK_CONTAINER (data->window), vbox);

	data->entry_alignment = add_entry (vbox, "Alignment: ");
	data->entry_description = add_entry (vbox, "Description: ");

	button = gtk_button_new_from_stock (GTK_STOCK_OK);
	gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 10);

	if (data->edit)
	{
		GtkTreeIter iter;
		GtkTreeModel *model;
		gchar *alignment;
		gchar *description;

	
		if(!gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data->builder->selection), &model, &iter)) 
		{
			return;
		}
		else
		{
			gtk_tree_model_get(model, &iter, 0, &alignment, 1, &description, -1);
		}
		
		gtk_entry_set_text (GTK_ENTRY (data->entry_alignment), alignment);
		gtk_entry_set_text (GTK_ENTRY (data->entry_description), description);

		data->value = g_strdup_printf ("%s", alignment);
		
		g_free (alignment);
		g_free (description);
	}


	g_signal_connect (G_OBJECT (data->window), "destroy", G_CALLBACK (on_alignment_destroy), NULL);
	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (on_alignment_button_clicked), data);

	gtk_widget_show_all (data->window);
}
