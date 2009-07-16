#include <gtk/gtk.h>
#include <direct.h>
#include "reg.h"
#include "menu.h"
#include "handler.h"
#include "listview.h"

typedef struct {
	GtkWidget *entry_name;
	GtkWidget *entry_value;
	GtkWidget *window;
	Reg *reg;
} INSERT_REG_SZ;

static void on_reg_sz_quit (GtkButton *button, INSERT_REG_SZ *reg_sz) {
	gtk_widget_destroy (reg_sz->window);
	g_slice_free (INSERT_REG_SZ, reg_sz);
}

static void on_reg_sz_ok_activate (GtkButton *button, INSERT_REG_SZ *reg_sz) {
	const char *name;
	const char *value;
	HKEY cur_key;

	name = gtk_entry_get_text (GTK_ENTRY (reg_sz->entry_name));
	value = gtk_entry_get_text (GTK_ENTRY (reg_sz->entry_value));

//	printf ("%s %s \n", name, value);
	if ( RegOpenKeyEx(reg_sz->reg->rootkey,
 		TEXT(reg_sz->reg->path),
 		0,
 		KEY_SET_VALUE,
 		&cur_key) == ERROR_SUCCESS
	)
	{
//		printf ("opened\n");

		if (RegSetValueEx(
				cur_key,
				g_convert(name, -1, "GBK", "UTF-8", NULL, NULL, NULL),
				0,
				REG_SZ,
				g_convert(value, -1, "GBK", "UTF-8", NULL, NULL, NULL),
				strlen (g_convert(value, -1, "GBK", "UTF-8", NULL, NULL, NULL)) + 1
				) == ERROR_SUCCESS)
		{
			liststore_insert (GTK_TREE_VIEW (reg_sz->reg->listview), name, "REG_SZ", value);
		} else {
			error_message ("插入失败，请检查权限");
		}
		on_reg_sz_quit (NULL, reg_sz);
	}
	RegCloseKey(cur_key);
}


void on_edit_insert_reg_sz_activate (GtkMenuItem *menuitem, Reg *reg) {
	INSERT_REG_SZ *reg_sz;
	reg_sz = g_slice_new (INSERT_REG_SZ);
	if (reg_sz == NULL) {
		fprintf (stderr, "Error: not enough space\n");
		exit (1);
	}

	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *entry_name;
	GtkWidget *entry_value;
	GtkWidget *hbuttonbox;
	GtkWidget *button_ok;
	GtkWidget *button_cancel;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "新建");
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);
	
	label = gtk_label_new ("名称:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

	entry_name = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (hbox), entry_name, FALSE, FALSE, 0);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);
	
	label = gtk_label_new ("键值:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

	entry_value = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (hbox), entry_value, FALSE, FALSE, 0);

	hbuttonbox = gtk_hbutton_box_new();
	gtk_box_pack_start (GTK_BOX (vbox), hbuttonbox, FALSE, FALSE, 5);

	button_ok = gtk_button_new_with_label ("OK");
	gtk_box_pack_start (GTK_BOX (hbuttonbox), button_ok, FALSE, FALSE, 0);

	button_cancel = gtk_button_new_with_label ("Cancel");
	gtk_box_pack_start (GTK_BOX (hbuttonbox), button_cancel, FALSE, FALSE, 0);

	reg_sz->entry_name = entry_name;
	reg_sz->entry_value = entry_value;
	reg_sz->reg = reg;
	reg_sz->window = window;

//	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (on_reg_sz_quit), reg_sz);
	g_signal_connect (GTK_BUTTON (button_cancel), "clicked", G_CALLBACK (on_reg_sz_quit), reg_sz);

	g_signal_connect (GTK_BUTTON (button_ok), "clicked", G_CALLBACK (on_reg_sz_ok_activate), reg_sz);

	gtk_widget_show_all (window);

}

void on_edit_delete_key_activate (GtkMenuItem *menuitem, Reg *reg) {
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *value;

	HKEY cur_key;

	if (gtk_tree_selection_get_selected (reg->selection, &model, &iter)) {
		if (check ("确定要删除？")) {
//			printf ("comfirmed, delete\n");

			gtk_tree_model_get (model, &iter, COL_NAME, &value, -1);

			if (RegOpenKeyEx (reg->rootkey, TEXT(reg->path), 0, KEY_SET_VALUE, &cur_key) == ERROR_SUCCESS) {
//				printf ("key opened\n");
			}

			if (RegDeleteValue (cur_key, g_convert(value, -1, "GBK", "UTF-8", NULL, NULL, NULL)) == ERROR_SUCCESS) {
				gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
//				printf ("deleted\n");
			}

			RegCloseKey (cur_key);

		}
	}
}

void on_option_add_to_run_activate (GtkMenuItem *menuitem, Reg *reg) {

	HKEY cur_key;

	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE,
 		TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
 		0,
 		KEY_SET_VALUE,
 		&cur_key) == ERROR_SUCCESS
	)
	{

		if (RegSetValueEx(
				cur_key,
				"reg",
				0,
				REG_SZ,
				reg->progname,
				strlen (reg->progname) + 1
				) == ERROR_SUCCESS)
		{
			message ("操作成功");
		}
	}
			

	RegCloseKey(cur_key);

}

typedef struct {
	GtkWidget *entry_ip;
	GtkWidget *entry_mac;
	GtkWidget *window;
	Reg *reg;
} GATEWAY;

static void on_gateway_quit (GtkButton *button, GATEWAY *gateway) {
	gtk_widget_destroy (gateway->window);
	g_slice_free (GATEWAY, gateway);
}

static void on_gateway_ok_activate (GtkButton *button, GATEWAY *gateway) {
	const char *ip;
	const char *mac;
	char buf[MAX_VALUE];
	HKEY cur_key;

	ip = gtk_entry_get_text (GTK_ENTRY (gateway->entry_ip));
	mac = gtk_entry_get_text (GTK_ENTRY (gateway->entry_mac));

	sprintf (buf, "arp -s %s %s", ip, mac );
//	printf ("buf: %s\n", buf);

//	printf ("%s %s \n", name, value);
	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE,
 		TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
 		0,
 		KEY_SET_VALUE,
 		&cur_key) == ERROR_SUCCESS
	)
	{
//		printf ("opened\n");

		if (RegSetValueEx(
				cur_key,
				"gateway",
				0,
				REG_SZ,
				g_convert(buf, -1, "GBK", "UTF-8", NULL, NULL, NULL),
				strlen (g_convert(buf, -1, "GBK", "UTF-8", NULL, NULL, NULL)) + 1
				) == ERROR_SUCCESS)
		{
			message ("操作成功");
		} else {
			error_message ("插入失败，请检查权限");
		}
		on_gateway_quit (NULL, gateway);
	}
	RegCloseKey(cur_key);
}
void on_option_bind_gateway_activate (GtkMenuItem *menuitem, Reg *reg) {
	GATEWAY *gateway;
	gateway = g_slice_new (GATEWAY);
	if (gateway == NULL) {
		fprintf (stderr, "Error: not enough space\n");
		exit (1);
	}

	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *entry_ip;
	GtkWidget *entry_mac;
	GtkWidget *hbuttonbox;
	GtkWidget *button_ok;
	GtkWidget *button_cancel;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "新建");
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);
	
	label = gtk_label_new ("网关ip:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

	entry_ip = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (hbox), entry_ip, FALSE, FALSE, 0);

	hbox = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 5);
	
	label = gtk_label_new ("网关mac:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

	entry_mac = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (hbox), entry_mac, FALSE, FALSE, 0);

	hbuttonbox = gtk_hbutton_box_new();
	gtk_box_pack_start (GTK_BOX (vbox), hbuttonbox, FALSE, FALSE, 5);

	button_ok = gtk_button_new_with_label ("OK");
	gtk_box_pack_start (GTK_BOX (hbuttonbox), button_ok, FALSE, FALSE, 0);

	button_cancel = gtk_button_new_with_label ("Cancel");
	gtk_box_pack_start (GTK_BOX (hbuttonbox), button_cancel, FALSE, FALSE, 0);

	gateway->entry_ip = entry_ip;
	gateway->entry_mac = entry_mac;
	gateway->reg = reg;
	gateway->window = window;

//	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (on_reg_sz_quit), reg_sz);
	g_signal_connect (GTK_BUTTON (button_cancel), "clicked", G_CALLBACK (on_gateway_quit), gateway);

	g_signal_connect (GTK_BUTTON (button_ok), "clicked", G_CALLBACK (on_gateway_ok_activate), gateway);

	gtk_widget_show_all (window);


}
