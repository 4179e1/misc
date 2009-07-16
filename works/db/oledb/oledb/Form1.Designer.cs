namespace oledb
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.entry = new System.Windows.Forms.TextBox();
            this.result1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.result2 = new System.Windows.Forms.Label();
            this.result3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(16, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "WebSite:";
            // 
            // entry
            // 
            this.entry.Location = new System.Drawing.Point(73, 19);
            this.entry.Name = "entry";
            this.entry.Size = new System.Drawing.Size(100, 21);
            this.entry.TabIndex = 1;
            // 
            // result1
            // 
            this.result1.AutoSize = true;
            this.result1.Location = new System.Drawing.Point(16, 62);
            this.result1.Name = "result1";
            this.result1.Size = new System.Drawing.Size(17, 12);
            this.result1.TabIndex = 2;
            this.result1.Text = "ID";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(181, 19);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "查询";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // result2
            // 
            this.result2.AutoSize = true;
            this.result2.Location = new System.Drawing.Point(39, 62);
            this.result2.Name = "result2";
            this.result2.Size = new System.Drawing.Size(29, 12);
            this.result2.TabIndex = 4;
            this.result2.Text = "名称";
            // 
            // result3
            // 
            this.result3.AutoSize = true;
            this.result3.Location = new System.Drawing.Point(179, 62);
            this.result3.Name = "result3";
            this.result3.Size = new System.Drawing.Size(29, 12);
            this.result3.TabIndex = 5;
            this.result3.Text = "网址";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 273);
            this.Controls.Add(this.result3);
            this.Controls.Add(this.result2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.result1);
            this.Controls.Add(this.entry);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "OleDb";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox entry;
        private System.Windows.Forms.Label result1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label result2;
        private System.Windows.Forms.Label result3;
    }
}

