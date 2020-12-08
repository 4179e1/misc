#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#define _WIN32_WINNT 0x0501

#include <winsock2.h>
#include <ws2tcpip.h>
#include "collection.h"
#include "scan.h"
#include "socket.h"

#define DEFAULT_BUFLEN 512

static int scanning = 0;

enum {
	COL_IP = 0,
	COL_PORT,
	COL_STATUS,
	COL_COUNT,
	COL_REMARKS,
	NUM_COLS
};

typedef struct {
	GtkWidget *scan_window;
	GtkWidget *entry_ip;
	GtkWidget *radio_button_single;
	GtkWidget *radio_button_multi;
	GtkWidget *entry_port;
	GtkWidget *entry_port_start;
	GtkWidget *entry_port_end;
	GtkWidget *entry_count;
	GtkWidget *treeview;
	GtkWidget *progressbar;
} ScanObject;

static GtkTreeIter liststore_insert (GtkTreeView *treeview, const char *ip, int port, char *status, int count, char *remarks) { 

	GtkListStore *store;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));

/* MODIFY IT: columns */	
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_IP, ip,
			COL_PORT, port,
			COL_STATUS, status,
			COL_COUNT, count,
			COL_REMARKS, remarks,
			-1);

	return iter;
}

static void liststore_set_count (GtkTreeView *treeview, GtkTreeIter iter, int count) {
	GtkListStore *store;

	store = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));

	gtk_list_store_set (store, &iter,
			COL_COUNT, count,
			-1);
}

static void liststore_set_status (GtkTreeView *treeview, GtkTreeIter iter, char *status) {
	GtkListStore *store;

	store = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));

	gtk_list_store_set (store, &iter,
			COL_STATUS, status,
			-1);
}

static GtkWidget * create_view_and_model (void) {
	GtkCellRenderer *renderer;
	GtkTreeModel *model;
	GtkWidget *view;

	view = gtk_tree_view_new ();

	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"IP地址",
												renderer,
												"text", COL_IP,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"端口号",
												renderer,
												"text", COL_PORT,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"端口状态",
												renderer,
												"text", COL_STATUS,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"连接次数",
												renderer,
												"text", COL_COUNT,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"备注",
												renderer,
												"text", COL_REMARKS,
												NULL);
	
	model = GTK_TREE_MODEL (gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING));
	gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

	g_object_unref (model);

	return view;
}

static int connect_test (const char *ip, char *port) {
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
//    char *sendbuf = "this is a test";
//    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
//    int recvbuflen = DEFAULT_BUFLEN;
    
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(ip, port, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed: %d\n", iResult);
        return 0;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("Error at socket(): %d\n", WSAGetLastError());
            freeaddrinfo(result);
            return 0;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect!\n");
        return 0;
    }

    closesocket(ConnectSocket);

    return 1;
}

static void on_window_destroy (GtkObject *window, ScanObject *scan_object) {
	if (scanning == 0) {
		g_slice_free (ScanObject, scan_object);

		gtk_widget_destroy (GTK_WIDGET (window));
	}
}

static void on_start_clicked (GtkButton *button_start, ScanObject *scan_object) {

	socket_init();

	const char *ip = NULL;
	const char *count = NULL;
	const char *start = NULL;
	const char *end = NULL;

	gdouble value = 0.0;
	gdouble tick = 0.0;
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(scan_object->progressbar), 0.0);

	char buf[32];

	int status = 0;

	GtkTreeIter iter;

	ip = gtk_entry_get_text (GTK_ENTRY (scan_object->entry_ip));
	count = gtk_entry_get_text (GTK_ENTRY (scan_object->entry_count));
	
	if ( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (scan_object->radio_button_single))) {
		start = end = gtk_entry_get_text (GTK_ENTRY (scan_object->entry_port)); 
	} else {
		start = gtk_entry_get_text (GTK_ENTRY (scan_object->entry_port_start));
		end = gtk_entry_get_text (GTK_ENTRY (scan_object->entry_port_end));
	}

//	g_print ("%s %s %s %s\n", ip, count, start, end);
	scanning = 1;

	int port_start, port_end;
	int count_start, count_end;

	port_start = atoi (start);
	port_end = atoi (end);
	count_end = atoi (count);

	tick = 1 / (port_end - port_end +1);

	for (; port_start <= port_end; port_start++) {
		if (scanning == 0)
		{
			break;
		}

		//do something
		//g_print ("%d\n", port_start);
		iter = liststore_insert (GTK_TREE_VIEW (scan_object->treeview), ip, port_start, "-", 0, NULL);

		for (count_start = 1; count_start <= count_end; count_start++) {
			//do somethint
			//g_print ("%d\n", count_start);
			sprintf (buf, "%d", port_start);
			status = connect_test(ip, buf);
			liststore_set_count (GTK_TREE_VIEW (scan_object->treeview), iter, count_start);
		}

		liststore_set_status (GTK_TREE_VIEW (scan_object->treeview), iter, (status == 0 ? "关闭" : "打开"));

		value += tick;
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(scan_object->progressbar), (value < 1.0 ? value : 1.0));
	}

	scanning = 0;
	socket_terminal();
}

static void on_end_clicked (GtkButton *button, gpointer userdata) {
	scanning = 0;
}

void scan (Collection *collection) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *frame;
	GtkWidget *table;
	GtkWidget *entry_ip;
	GtkWidget *radio_button_single;
	GtkWidget *radio_button_multi;
	GtkWidget *entry_port;
	GtkWidget *entry_port_start;
	GtkWidget *entry_port_end;
	GtkWidget *entry_count;
	GtkWidget *label;
	GtkWidget *sw;
	GtkWidget *treeview;
	GtkWidget *progressbar;
	GtkWidget *hbuttonbox;

	GtkWidget *start;
	GtkWidget *end;

	ScanObject *scan_object;
	scan_object = g_slice_new (ScanObject);
	if (scan_object == NULL)
	{
		fprintf (stderr, "Error: not enough space\n");
		exit (1);
	}

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "端口扫描");
	gtk_window_set_transient_for (GTK_WINDOW (window), GTK_WINDOW (collection->window));
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (window), TRUE);
	gtk_window_set_modal (GTK_WINDOW (window), TRUE);
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 600);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	frame = gtk_frame_new ("主机IP地址");
	gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 2);

	table = gtk_table_new (4, 7, FALSE);
	gtk_table_set_col_spacings (GTK_TABLE (table), 2);
	gtk_table_set_row_spacings (GTK_TABLE (table), 2);
	gtk_container_add (GTK_CONTAINER (frame), table);

	label = gtk_label_new ("IP地址");
	gtk_table_attach (GTK_TABLE (table), label, 0, 2, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);

	entry_ip = gtk_entry_new();
	gtk_entry_set_text (GTK_ENTRY (entry_ip), "127.0.0.1");
	gtk_table_attach (GTK_TABLE (table), entry_ip, 2, 6, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

	radio_button_single = gtk_radio_button_new_with_label (NULL, "扫描一个端口");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_single), TRUE);
	gtk_table_attach (GTK_TABLE (table), radio_button_single, 0, 2, 1, 2, GTK_SHRINK, GTK_SHRINK, 0, 0);

	entry_port = gtk_entry_new();
	gtk_entry_set_text (GTK_ENTRY (entry_port), "135");
	gtk_widget_set_size_request (entry_port, 75, -1);
	gtk_table_attach (GTK_TABLE (table), entry_port, 2, 3, 1, 2, GTK_SHRINK, GTK_SHRINK, 0, 0);

	radio_button_multi = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (radio_button_single), "扫描多个端口");
	gtk_table_attach (GTK_TABLE (table), radio_button_multi, 0, 2, 2, 3, GTK_SHRINK, GTK_SHRINK, 0, 0);

	entry_port_start = gtk_entry_new ();
	gtk_widget_set_size_request (entry_port_start, 75, -1);
	gtk_table_attach (GTK_TABLE (table), entry_port_start, 2, 3, 2, 3, GTK_SHRINK, GTK_SHRINK, 0, 0);

	label = gtk_label_new ("TO");
	gtk_table_attach (GTK_TABLE (table), label, 3, 4, 2, 3, GTK_SHRINK, GTK_SHRINK, 0, 0);

	entry_port_end = gtk_entry_new ();
	gtk_widget_set_size_request (entry_port_end, 75, -1);
	gtk_table_attach (GTK_TABLE (table), entry_port_end, 4, 5, 2, 3, GTK_SHRINK, GTK_SHRINK, 0, 0);

	label = gtk_label_new ("尝试扫描次数");
	gtk_table_attach (GTK_TABLE (table), label, 0, 2, 3, 4, GTK_SHRINK, GTK_SHRINK, 0, 0);

	entry_count = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (entry_count), "3");
	gtk_widget_set_size_request (entry_count, 75, -1);
	gtk_table_attach (GTK_TABLE (table), entry_count, 2, 3, 3, 4, GTK_SHRINK, GTK_SHRINK, 0, 0);

	label = gtk_label_new ("扫描结果");
	gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 2);

	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 2);

	treeview = create_view_and_model ();
	gtk_container_add (GTK_CONTAINER (sw), treeview);

	progressbar = gtk_progress_bar_new();
	gtk_box_pack_start (GTK_BOX (vbox), progressbar, FALSE, FALSE, 2);

	hbuttonbox = gtk_hbutton_box_new();
	gtk_box_pack_start (GTK_BOX (vbox), hbuttonbox, FALSE, FALSE, 2);

	start = gtk_button_new_with_label ("开始");
	gtk_box_pack_start (GTK_BOX (hbuttonbox), start, FALSE, FALSE, 2);

	end = gtk_button_new_with_label ("结束");
	gtk_box_pack_start (GTK_BOX (hbuttonbox), end, FALSE, FALSE, 2);

	scan_object->scan_window = window;
	scan_object->entry_ip = entry_ip;
	scan_object->radio_button_single = radio_button_single;
	scan_object->radio_button_multi = radio_button_multi;
	scan_object->entry_port = entry_port;
	scan_object->entry_port_start = entry_port_start;
	scan_object->entry_port_end = entry_port_end;
	scan_object->entry_count = entry_count;
	scan_object->treeview = treeview;
	scan_object->progressbar = progressbar;


	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (on_window_destroy), scan_object); 
	
	g_signal_connect (GTK_BUTTON (start), "clicked", G_CALLBACK (on_start_clicked), scan_object);

	g_signal_connect (GTK_BUTTON (end), "clicked", G_CALLBACK (on_end_clicked), NULL);

	gtk_widget_show_all (window);
}
