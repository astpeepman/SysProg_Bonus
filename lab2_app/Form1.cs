using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace lab2_app
{
    public partial class Form1 : Form
    {
        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg4_LIBRARY.dll", EntryPoint = "init")]
        private static extern bool init0();
        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg5_LIBRARY.dll", EntryPoint = "init")]
        private static extern bool init1();


        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg4_LIBRARY.dll", EntryPoint = "StartThread")]
        private static extern int StartThread0(int count);
        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg5_LIBRARY.dll", EntryPoint = "StartThread")]
        private static extern int StartThread1(int count);


        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg4_LIBRARY.dll", EntryPoint = "StopThread")]
        private static extern int StopThread0(int count);
        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg5_LIBRARY.dll", EntryPoint = "StopThread")]
        private static extern int StopThread1(int count);


        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg4_LIBRARY.dll", EntryPoint = "SendMess")]
        private static extern void SendMess0(string pStr, int a);
        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg5_LIBRARY.dll", EntryPoint = "SendMess")]
        private static extern void SendMess1(string pStr, int a);


        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg4_LIBRARY.dll", EntryPoint = "deinit")]
        private static extern void deinit0();
        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg5_LIBRARY.dll", EntryPoint = "deinit")]
        private static extern void deinit1();


        [DllImport("G:\\универ\\3 курс\\2 сем\\Леонов\\SysProg_Bonus\\SysProg_Bonus\\Debug\\SysProg5_LIBRARY.dll", CharSet = CharSet.Ansi)]
        private static extern void INITAFX();

        public Form1()
        {
            InitializeComponent();
            _UpDown.Enabled = true;
        }



        int CountOfThreads = 0;

        void UpdateLists()
        {
            _list.Items.Clear();
            comboBox1.Items.Clear();

            _list.Items.Add("Main Thread");
            comboBox1.Items.Add("All Threads");

            for (int i = 0; i < CountOfThreads; i++)
            {
                comboBox1.Items.Add(i);
                _list.Items.Add(String.Format("Thread {0}", i));
            }
        }
        
        private void _btn_start_Click(object sender, EventArgs e)
        {
            if (_rb_Pipes.Checked)
            {
                if (init0())
                {
                    int count = Convert.ToInt32(Math.Round(_UpDown.Value, 0));
                    CountOfThreads = StartThread0(count);
                    UpdateLists();
                    deinit0();
                    _btn_stop.Enabled = true;
                }
                else
                {
                    _list.Items.Add("ERROR :: CAN'T CONNECT TO SERVER");
                }
            }

            if (_rb_Sockets.Checked)
            {
                if (init1())
                {
                    int count = Convert.ToInt32(Math.Round(_UpDown.Value, 0));
                    CountOfThreads = StartThread1(count);
                    UpdateLists();
                    deinit1();
                    _btn_stop.Enabled = true;
                }
                else
                {
                    _list.Items.Add("ERROR :: CAN'T CONNECT TO SERVER");
                }
            }
            
        }

        private void _btn_stop_Click(object sender, EventArgs e)
        {
            if (_rb_Pipes.Checked)
            {
                if (init0())
                {
                    int count = Convert.ToInt32(Math.Round(_UpDown.Value, 0));
                    if (count > CountOfThreads)
                    {
                        count = -1;
                        _btn_stop.Enabled = false;
                    }
                    CountOfThreads = StopThread0(count);
                    UpdateLists();
                    deinit0();
                }
                else
                {
                    _list.Items.Clear();
                    comboBox1.Items.Clear();
                    _list.Items.Add("ERROR :: CAN'T CONNECT TO SERVER");
                }
            }

            if (_rb_Sockets.Checked)
            {
                if (init1())
                {
                    int count = Convert.ToInt32(Math.Round(_UpDown.Value, 0));
                    if (count > CountOfThreads)
                    {
                        count = -1;
                        _btn_stop.Enabled = false;
                    }
                    CountOfThreads = StopThread1(count);
                    UpdateLists();
                    deinit1();
                }
                else
                {
                    _list.Items.Clear();
                    comboBox1.Items.Clear();
                    _list.Items.Add("ERROR :: CAN'T CONNECT TO SERVER");
                }
            }
           

        }

        private void _btn_snd_Click(object sender, EventArgs e)
        {
            if (_rb_Pipes.Checked)
            {
                if (init0())
                {
                    _adrs_label.ForeColor = Color.Black;
                    int id = (comboBox1.SelectedIndex) - 1;
                    string text = _txtBox.Text;

                    SendMess0(text, id);
                    deinit0();
                }
            }

            if (_rb_Sockets.Checked)
            {
                if (init1())
                {
                    _adrs_label.ForeColor = Color.Black;
                    int id = (comboBox1.SelectedIndex) - 1;
                    string text = _txtBox.Text;

                    SendMess1(text, id);
                    deinit1();
                }
            }
           

            //if (Confirm())
            //{
            //    MessageBox.Show("Successfully");
            //}



        }

        private void form_closing(object sender, FormClosingEventArgs e)
        {
            //StopThread(-1);
        }

        private void _rb_Sockets_CheckedChanged(object sender, EventArgs e)
        {
            INITAFX();
        }
    }
}
