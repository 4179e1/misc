#include <iostream>
#include <sqlite3.h>
using namespace std;

int print_result_cb(void* data, int n_columns, char** column_values,
                    char** column_names);
void print_row(int n_values, char** values);

int main()
{
	sqlite3 *pDB = NULL;
 char * errMsg = NULL;
 const char * databaseName = "test";

 //打开一个数据库，如果改数据库不存在，则创建一个名字为databaseName的数据库文件
  int rc = sqlite3_open(databaseName, &pDB);

  if(rc)
  {
    cout << " Open the database " << databaseName << " failed" << endl;
  }

  //如果创建成功，添加表

  else
  {
    cout << "create the database successful!" << endl;

    //creat the table
    //插入一个表，返回值为SQLITE_OK为成功，否则输出出错信息

    //函数参数：第一个为操作数据库的指针，第二句为SQL命令字符串

    //第三个参数为callback函数，这里没有用，第四个参数为callback函数

    //中的第一个参数，第五个为出错信息

    rc = sqlite3_exec(pDB, "CREATE TABLE chn_to_eng(chinese QString, english QString)", 0, 0, &errMsg);

    if(rc == SQLITE_OK)
       cout << "create the chn_to_eng table successful!" << endl;
    else
       cout << errMsg << endl;

    //同上，插入另一个表

    rc = sqlite3_exec(pDB, "CREATE TABLE eng_to_chn(english QString, chinese QString)", 0, 0, &errMsg);

    if(rc == SQLITE_OK)
        cout << "create the eng_to_chn table successful!" << endl;
    else
       cout << errMsg << endl;
   
  }

  //往表中添加数据

  char chn[]="...";

  char eng[]="...";

  char value[500];
  //定义一条参数SQL命令，其中chn,eng为需要插入的数据    
  sprintf(value, "INSERT INTO chn_to_eng(chinese, english) VALUES('%s', '%s')", chn, eng);
  
  //use the SQLITE C/C++ API to create and adjust a database.
  rc = sqlite3_exec(pDB,
                       value,
                      0, 0, &errMsg);

 //查询一条记录


 //定义一条查询语句，其中条件为当english为target时的中文记录

 //print_result_cb为callback函数，在其中可以得到查询的结果，具体见下文
 sprintf(value, "SELECT chinese FROM eng_to_chn where english='%s' ", eng);

  rc = sqlite3_exec(pDB,
                      value,
                      print_result_cb, 0, &errMsg);

  if(rc == SQLITE_OK)
      {
//        #ifdef_debug
           cout << "select the record successful!" << endl;
//        #endif
      }
      else
      {
//        #ifdef_debug
          cout << errMsg << endl; 
//        #endif                           
          return false;
      }
}

//callback回调函数print_result_cb的编写，其中data为sqlite3_exec中的第四个参数，第二个参数是栏的数目，第三个是栏的名字，第四个为查询得到的值得。这两个函数输出所有查询到的结果

int print_result_cb(void* data, int n_columns, char** column_values,
                    char** column_names)
{
    static int column_names_printed = 0;
    int i;
    if (!column_names_printed) {
        print_row(n_columns, column_names);
        column_names_printed = 1;
    }

    print_row(n_columns, column_values);
    return 0;
}


void print_row(int n_values, char** values)
{
    int i;
    for (i = 0; i < n_values; ++i) {
        if (i > 0) {
            printf("\t");
        }

        printf("%s", values[i]);
       
    }
    printf("\n");
}

