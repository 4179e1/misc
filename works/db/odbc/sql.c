#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <gtk/gtk.h>
#include "odbc.h"
#include "sql.h"
#include "liststore.h"

#define LEN 50
#define BUF 1024

void on_button_clicked(GtkButton *button, Data *data)
{
	SQLHENV access_env; //环境句柄
	SQLHDBC access_dbc; //连接句柄
	SQLHSTMT access_stmt; //语句句柄
	SQLRETURN ret;
	SQLINTEGER id;
	SQLCHAR name[LEN];
	SQLCHAR url[LEN];
	SQLINTEGER cbid = 0, cbname = SQL_NTS, cburl = SQL_NTS;

	char stat[BUF];
	stat[0] = '\0';
	const char *val;

	remove_tree_view (GTK_TREE_VIEW (data->treeview));

	val = gtk_entry_get_text (GTK_ENTRY (data->entry));
	sprintf (stat, "SELECT * FROM link WHERE link_text like \'%%%s%%\';", g_convert (val, -1, "GBK", "UTF-8", NULL, NULL, NULL));
//	printf ("%s\n", stat);

	ret = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &access_env);
	ret = SQLSetEnvAttr (access_env, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);

	ret = SQLAllocHandle (SQL_HANDLE_DBC, access_env, &access_dbc);
	ret = SQLConnect (access_dbc, (SQLCHAR*)"access_db", SQL_NTS, NULL, SQL_NTS, NULL, SQL_NTS);
	if (!SQL_SUCCEEDED (ret))
	{
		printf ("error\n");
		return;
	}

	ret = SQLAllocHandle (SQL_HANDLE_STMT, access_dbc, &access_stmt);
	ret = SQLSetStmtAttr (access_stmt, SQL_ATTR_ROW_BIND_TYPE, (SQLPOINTER) SQL_BIND_BY_COLUMN, SQL_IS_INTEGER);

    ret = SQLExecDirect (access_stmt, (SQLCHAR*)stat, SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
		ret = SQLBindCol (access_stmt, 1, SQL_C_LONG, &id, 0, &cbid);
		ret = SQLBindCol (access_stmt, 2, SQL_C_CHAR, name, LEN, &cbname);
		ret = SQLBindCol (access_stmt, 3, SQL_C_CHAR, url, LEN, &cburl);
	}

	while ( (SQLFetch (access_stmt)) != SQL_NO_DATA_FOUND) {
		if (ret == SQL_ERROR)
			printf ("Fetch error\n");
		else
		{
//			printf ("%d %s %s\n", (int)id, name, url);
			liststore_insert (GTK_TREE_VIEW (data->treeview), id, g_convert (name, -1, "UTF-8", "GBK", NULL, NULL, NULL), url);
		}	
	}

	SQLFreeHandle (SQL_HANDLE_STMT, access_stmt);
	SQLDisconnect (access_stmt);
	SQLFreeHandle (SQL_HANDLE_DBC, access_dbc);
	SQLFreeHandle (SQL_HANDLE_ENV, access_env);
}

