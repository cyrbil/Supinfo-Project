using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Klout
{
    public partial class Klout : Form
    {
        public Klout()
        {
            InitializeComponent();
        }

        private void search_bt_Click(object sender, EventArgs e)
        {
            info_label.Text = "Fetching Data ... Please Wait ...";

            kloutConnection work = new kloutConnection();
            work.BeginGetUserInfo(search_tb.Text, info_label);
        }

    }
}
