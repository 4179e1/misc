#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main( void )
{
    sqlite3 *db=NULL;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("test.db", &db);   //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件

	printf("rc = %d\n",rc);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    else printf("open zieckey.db successfully!\n");
    
    sqlite3_close(db);               //关闭数据库
    return 0;
}
