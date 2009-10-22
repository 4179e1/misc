#include <gtk/gtk.h>
#include "idvc.h"
#include "idvc_toolbar.h"

enum _idvc_tool_button_type
{
	IDVC_TOOL_BUTTON_NORMAL = 0,
	IDVC_TOOL_BUTTON_STOCK,
	IDVC_TOOL_BUTTON_SEP,
	IDVC_TOOL_BUTTON_END,
};
typedef enum _idvc_tool_button_type IdvcToolButtonType;

struct _idvc_toolbutton
{
	IdvcToolButtonType type;
	GtkWidget *icon_widget;
	const char *label;
	GCallback callback_func;
};
typedef struct _idvc_toolbutton IdvcToolButton;

static void idvc_toolbar_build (GtkWidget *toolbar, IdvcToolButton *buttonlist, Idvc *idvc_data);

/* a test func for toolbutton callback */
static void idvc_toolbutton_callback_testing (GtkToolButton *toolbutton, Idvc *idvc_data)
{
	g_message ("%s is clicked", gtk_widget_get_name (GTK_WIDGET (toolbutton)));
}

/* create the toolbar and buttons on it */
GtkWidget *idvc_toolbar_new (Idvc *idvc_data)
{
	GtkWidget *toolbar;
	toolbar = gtk_toolbar_new ();

	IdvcToolButton buttonlist[] = 
	{
		{IDVC_TOOL_BUTTON_STOCK, NULL, GTK_STOCK_ADD, G_CALLBACK (idvc_toolbutton_callback_testing)},
		{IDVC_TOOL_BUTTON_STOCK, NULL, GTK_STOCK_REMOVE, G_CALLBACK (idvc_toolbutton_callback_testing)},
		{IDVC_TOOL_BUTTON_SEP,NULL, NULL, NULL},
		{IDVC_TOOL_BUTTON_STOCK, NULL, GTK_STOCK_DIRECTORY, NULL},
		{IDVC_TOOL_BUTTON_STOCK, NULL, GTK_STOCK_CLEAR, NULL},
		{IDVC_TOOL_BUTTON_SEP, NULL, NULL, NULL},
		{IDVC_TOOL_BUTTON_STOCK, NULL, GTK_STOCK_CLOSE, NULL},
		{IDVC_TOOL_BUTTON_STOCK, NULL, GTK_STOCK_QUIT, NULL},
		{IDVC_TOOL_BUTTON_END, NULL, NULL, NULL},
	};

	idvc_toolbar_build (toolbar, buttonlist, idvc_data);

	return toolbar;
}

static void idvc_toolbar_build (GtkWidget *toolbar, IdvcToolButton *buttonlist, Idvc *idvc_data)
{
	IdvcToolButton *ptr = buttonlist;
	GtkToolItem *button;

	while (ptr->type != IDVC_TOOL_BUTTON_END)
	{
		switch (ptr->type)
		{
			case IDVC_TOOL_BUTTON_NORMAL:
			case IDVC_TOOL_BUTTON_STOCK:
				{
					if (ptr->type == IDVC_TOOL_BUTTON_NORMAL)
					{
						/* TODO: not knowing how to do */;
						button = gtk_tool_button_new (ptr->icon_widget, ptr->label);
					}
					else {
						button = gtk_tool_button_new_from_stock (ptr->label);
					}

					if (ptr->callback_func != NULL)
					{
						g_signal_connect (GTK_TOOL_BUTTON (button), "clicked", ptr->callback_func, idvc_data);
					}

					gtk_toolbar_insert (GTK_TOOLBAR (toolbar), button, -1);

					break;
				}
			case IDVC_TOOL_BUTTON_SEP:
				{
					button = gtk_separator_tool_item_new ();
					gtk_toolbar_insert (GTK_TOOLBAR (toolbar), button, -1);
					break;
				}
			case IDVC_TOOL_BUTTON_END:
			default:
				{
					g_warning ("Here should not be reached");
					break;
				}
		}
		ptr++;
	}

}
