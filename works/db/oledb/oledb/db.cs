using System;
using System.Data.OleDb;
using System.Collections.Generic;
using System.Text;

namespace oledb
{
    class db
    {
        private string ConnectionString;
        public db()
        {
            //数据库连接字符串
            ConnectionString += "Provider=sqloledb;Data Source=LYRE-9A2DCC57F0\\SQLEXPRESS;Initial Catalog=test;Persist Security Info=True;User ID=sa;Password=itsofnouse";
        }

        public OleDbConnection GetConnection()
        {
            OleDbConnection conn = new OleDbConnection();
            conn.ConnectionString = ConnectionString;

            return conn;
        }
    }
}
