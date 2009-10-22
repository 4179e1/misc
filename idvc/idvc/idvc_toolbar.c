#include <gtk/gtk.h>
#include "idvc.h"
#include "idvc_toolbar.h"

enum _tool_button_type
{
	TOOL_BUTTON_NORMAL = 0,
	TOOL_BUTTON_STOCK,
	TOOL_BUTTON_SEP,
	TOOL_BUTTON_END,
};
typedef enum _tool_button_type ToolButtonType;

struct _tool_button
{
	ToolButtonType type;
	GtkWidget *icon_widget;
	const char *label;
	GCallback callback_func;
};
typedef struct _tool_button ToolButton;

static void idvc_toolbar_build (GtkWidget *toolbar, ToolButton *buttonlist, Idvc *idvc_data);

/* a test func for toolbutton callback */
static void idvc_toolbutton_callback_testing (GtkToolButton *toolbutton, Idvc *idvc_data)
{
	g_message ("%s is clicked", gtk_widget_get_name (GTK_WIDGET (toolbutton)));
}

#define TOOL_BUTTON_SIZE 26

/* create the toolbar and buttons on it */
GtkWidget *idvc_toolbar_new (Idvc *idvc_data)
{
	GtkWidget *toolbar;
	toolbar = gtk_toolbar_new ();

	ToolButton buttonlist[] = 
	{
		{TOOL_BUTTON_STOCK, NULL, GTK_STOCK_ADD, G_CALLBACK (idvc_toolbutton_callback_testing)},
		{TOOL_BUTTON_STOCK, NULL, GTK_STOCK_REMOVE, G_CALLBACK (idvc_toolbutton_callback_testing)},
		{TOOL_BUTTON_SEP,NULL, NULL, NULL},
		{TOOL_BUTTON_NORMAL, gtk_image_new_from_stock (GTK_STOCK_DIRECTORY, TOOL_BUTTON_SIZE), "Add Directory", NULL},
		{TOOL_BUTTON_STOCK, NULL, GTK_STOCK_CLEAR, NULL},
		{TOOL_BUTTON_SEP, NULL, NULL, NULL},
		{TOOL_BUTTON_STOCK, NULL, GTK_STOCK_CLOSE, NULL},
		{TOOL_BUTTON_STOCK, NULL, GTK_STOCK_QUIT, NULL},
		{TOOL_BUTTON_END, NULL, NULL, NULL},
	};

	idvc_toolbar_build (toolbar, buttonlist, idvc_data);

	return toolbar;
}

static void idvc_toolbar_build (GtkWidget *toolbar, ToolButton *buttonlist, Idvc *idvc_data)
{
	ToolButton *ptr = buttonlist;
	GtkToolItem *button;

	while (ptr->type != TOOL_BUTTON_END)
	{
		switch (ptr->type)
		{
			case TOOL_BUTTON_NORMAL:
			case TOOL_BUTTON_STOCK:
				{
					if (ptr->type == TOOL_BUTTON_NORMAL)
					{
						button = gtk_tool_button_new (ptr->icon_widget, ptr->label);
						gtk_tool_button_set_label (GTK_TOOL_BUTTON(button), ptr->label);
					}
					else {
						button = gtk_tool_button_new_from_stock (ptr->label);
					}

					if (ptr->callback_func != NULL)
					{
						g_signal_connect (GTK_TOOL_BUTTON (button), "clicked", ptr->callback_func, idvc_data);
					}

					gtk_widget_set_tooltip_text (GTK_WIDGET (button), ptr->label);

					gtk_toolbar_insert (GTK_TOOLBAR (toolbar), button, -1);

					break;
				}
			case TOOL_BUTTON_SEP:
				{
					button = gtk_separator_tool_item_new ();
					gtk_toolbar_insert (GTK_TOOLBAR (toolbar), button, -1);
					break;
				}
			case TOOL_BUTTON_END:
			default:
				{
					g_warning ("Here should not be reached");
					break;
				}
		}
		ptr++;
	}

}
