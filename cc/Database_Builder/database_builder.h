#ifndef _DATABASE_BUILDER_H_
#define _DATABASE_BUILDER_H_

#include <sqlite3.h>

typedef struct
{
	GtkWidget *edit_add;
	GtkWidget *edit_edit;
	GtkWidget *edit_delete;
	GtkWidget *debug_exec_sql_command;
	GtkWidget *file_close;

	GtkToolItem *tool_button_add;
	GtkToolItem *tool_button_edit;
	GtkToolItem *tool_button_delete;

}SensitiveItem;

typedef struct
{
	GtkWidget *window;
	GtkWidget *statusbar;
	gint	statusbar_context_id;

	gint	page_index;
	GtkWidget *tree_view_cur;

	GtkWidget *tree_view_race;
	GtkWidget *tree_view_class;
	GtkWidget *tree_view_skills;
	GtkWidget *tree_view_feats;
	GtkWidget *tree_view_powers;
	GtkWidget *tree_view_equipment;
	GtkWidget *tree_view_alignment;
	GtkWidget *tree_view_deities;

	GtkTreeSelection *selection;

	SensitiveItem *si;

	gchar	*filename;
	sqlite3 *database;
}DatabaseBuilder;

#endif
