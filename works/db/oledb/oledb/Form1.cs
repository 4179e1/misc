using System;
using System.Data.OleDb;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace oledb
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            result1.Text = "ID\n";
            result2.Text = "Ãû³Æ\n";
            result3.Text = "ÍøÖ·\n";
            db accdb = new db();
            OleDbConnection conn = accdb.GetConnection();

            OleDbCommand cmd = new OleDbCommand();
            cmd.CommandType = CommandType.Text;
            cmd.CommandText = "select * from link where link_text like '%" + entry.Text.ToString() + "%'";
            cmd.Connection = conn;

            conn.Open();

            OleDbDataReader reader = cmd.ExecuteReader();

            while (reader.Read())
            {
                result1.Text += reader["id"].ToString() + "\n";
                result2.Text += reader["link_text"].ToString() + "\n";
                result3.Text += reader["link_url"].ToString() + "\n";
            }

            reader.Close();

            conn.Close();
        }
    }
}