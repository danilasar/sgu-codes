using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WorkStarter
{
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            mainLabel.Text = "Начало работы";
            OnLabelVisibilityChanged(sender, e);
        }

        private void OnHiddenerClick(object sender, EventArgs e)
        {
            mainLabel.Visible = false;
        }

        private void OnShowerClick(object sender, EventArgs e)
        {
            mainLabel.Visible = true;
        }

        private void OnLabelVisibilityChanged(object sender, EventArgs e)
        {
            if(mainLabel.Visible) {
                showButton.Enabled = false;
                hideButton.Enabled = true;
            } else {
                showButton.Enabled = true;
                hideButton.Enabled = false;
            }
        }
    }
}
