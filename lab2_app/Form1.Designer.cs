namespace lab2_app
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this._btn_start = new System.Windows.Forms.Button();
            this._btn_stop = new System.Windows.Forms.Button();
            this._btn_snd = new System.Windows.Forms.Button();
            this._UpDown = new System.Windows.Forms.NumericUpDown();
            this._list = new System.Windows.Forms.ListBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this._txtBox = new System.Windows.Forms.TextBox();
            this._txt_label = new System.Windows.Forms.Label();
            this._adrs_label = new System.Windows.Forms.Label();
            this._rb_Pipes = new System.Windows.Forms.RadioButton();
            this._rb_Sockets = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this._UpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // _btn_start
            // 
            this._btn_start.Location = new System.Drawing.Point(13, 23);
            this._btn_start.Name = "_btn_start";
            this._btn_start.Size = new System.Drawing.Size(75, 23);
            this._btn_start.TabIndex = 0;
            this._btn_start.Text = "Start";
            this._btn_start.UseVisualStyleBackColor = true;
            this._btn_start.Click += new System.EventHandler(this._btn_start_Click);
            // 
            // _btn_stop
            // 
            this._btn_stop.Enabled = false;
            this._btn_stop.Location = new System.Drawing.Point(13, 52);
            this._btn_stop.Name = "_btn_stop";
            this._btn_stop.Size = new System.Drawing.Size(75, 23);
            this._btn_stop.TabIndex = 1;
            this._btn_stop.Text = "Stop";
            this._btn_stop.UseVisualStyleBackColor = true;
            this._btn_stop.Click += new System.EventHandler(this._btn_stop_Click);
            // 
            // _btn_snd
            // 
            this._btn_snd.Location = new System.Drawing.Point(293, 176);
            this._btn_snd.Name = "_btn_snd";
            this._btn_snd.Size = new System.Drawing.Size(75, 23);
            this._btn_snd.TabIndex = 2;
            this._btn_snd.Text = "Send";
            this._btn_snd.UseVisualStyleBackColor = true;
            this._btn_snd.Click += new System.EventHandler(this._btn_snd_Click);
            // 
            // _UpDown
            // 
            this._UpDown.Enabled = false;
            this._UpDown.Location = new System.Drawing.Point(94, 23);
            this._UpDown.Name = "_UpDown";
            this._UpDown.Size = new System.Drawing.Size(77, 20);
            this._UpDown.TabIndex = 3;
            // 
            // _list
            // 
            this._list.FormattingEnabled = true;
            this._list.Location = new System.Drawing.Point(177, 23);
            this._list.Name = "_list";
            this._list.Size = new System.Drawing.Size(191, 108);
            this._list.TabIndex = 4;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(293, 149);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(75, 21);
            this.comboBox1.TabIndex = 5;
            // 
            // _txtBox
            // 
            this._txtBox.Location = new System.Drawing.Point(13, 179);
            this._txtBox.Name = "_txtBox";
            this._txtBox.Size = new System.Drawing.Size(266, 20);
            this._txtBox.TabIndex = 6;
            // 
            // _txt_label
            // 
            this._txt_label.AutoSize = true;
            this._txt_label.Location = new System.Drawing.Point(12, 157);
            this._txt_label.Name = "_txt_label";
            this._txt_label.Size = new System.Drawing.Size(80, 13);
            this._txt_label.TabIndex = 7;
            this._txt_label.Text = "Введите текст";
            // 
            // _adrs_label
            // 
            this._adrs_label.AutoSize = true;
            this._adrs_label.Location = new System.Drawing.Point(159, 152);
            this._adrs_label.Name = "_adrs_label";
            this._adrs_label.Size = new System.Drawing.Size(128, 13);
            this._adrs_label.TabIndex = 8;
            this._adrs_label.Text = "Выберите адрес потока";
            // 
            // _rb_Pipes
            // 
            this._rb_Pipes.AutoSize = true;
            this._rb_Pipes.Checked = true;
            this._rb_Pipes.Location = new System.Drawing.Point(15, 91);
            this._rb_Pipes.Name = "_rb_Pipes";
            this._rb_Pipes.Size = new System.Drawing.Size(83, 17);
            this._rb_Pipes.TabIndex = 9;
            this._rb_Pipes.TabStop = true;
            this._rb_Pipes.Text = "Named Pipe";
            this._rb_Pipes.UseVisualStyleBackColor = true;
            // 
            // _rb_Sockets
            // 
            this._rb_Sockets.AutoSize = true;
            this._rb_Sockets.Location = new System.Drawing.Point(15, 114);
            this._rb_Sockets.Name = "_rb_Sockets";
            this._rb_Sockets.Size = new System.Drawing.Size(106, 17);
            this._rb_Sockets.TabIndex = 10;
            this._rb_Sockets.Text = "Windows Socket";
            this._rb_Sockets.UseVisualStyleBackColor = true;
            this._rb_Sockets.CheckedChanged += new System.EventHandler(this._rb_Sockets_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(375, 208);
            this.Controls.Add(this._rb_Sockets);
            this.Controls.Add(this._rb_Pipes);
            this.Controls.Add(this._adrs_label);
            this.Controls.Add(this._txt_label);
            this.Controls.Add(this._txtBox);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this._list);
            this.Controls.Add(this._UpDown);
            this.Controls.Add(this._btn_snd);
            this.Controls.Add(this._btn_stop);
            this.Controls.Add(this._btn_start);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.form_closing);
            ((System.ComponentModel.ISupportInitialize)(this._UpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button _btn_start;
        private System.Windows.Forms.Button _btn_stop;
        private System.Windows.Forms.Button _btn_snd;
        private System.Windows.Forms.NumericUpDown _UpDown;
        private System.Windows.Forms.ListBox _list;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.TextBox _txtBox;
        private System.Windows.Forms.Label _txt_label;
        private System.Windows.Forms.Label _adrs_label;
        private System.Windows.Forms.RadioButton _rb_Pipes;
        private System.Windows.Forms.RadioButton _rb_Sockets;
    }
}

