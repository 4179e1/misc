#include <gtk/gtk.h>
#include "database_builder.h"
#include "other.h"
#include "edit_menu.h"

void on_help_about_activate (GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
    static const gchar * const authors[] = {
		"Lyre <4179e1@gmail.com>",
		NULL
	};

	static const gchar copyright[] = \
		"Copyright \xc2\xa9 2008 Lyre";

	static const gchar comments[] = "Build database for Character Creator";

	gtk_show_about_dialog (GTK_WINDOW (builder->window),
			       "authors", authors,
			       "comments", comments,
			       "copyright", copyright,
			       "version", "0.1",
			       "program-name", "Database Builder",
			       "logo-icon-name", GTK_STOCK_INDEX,
			       NULL); 
}

/* 3 buttons on toolbar */
void on_tool_button_add_clicked(GtkToolButton *button, DatabaseBuilder *dbb)
{
	on_edit_add_activate(NULL, dbb);
}

void on_tool_button_edit_clicked(GtkToolButton *button, DatabaseBuilder *dbb)
{
	on_edit_edit_activate(NULL, dbb);
}

void on_tool_button_delete_clicked(GtkToolButton *button, DatabaseBuilder *dbb)
{
	on_edit_delete_activate(NULL, dbb);
}

