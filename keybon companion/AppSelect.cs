using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace keybon
{
    public partial class AppSelect : Form
    {
        MainWindow ownerForm = null;
        public AppSelect(MainWindow ownerForm)
        {
            InitializeComponent();
            this.ownerForm = ownerForm;
        }

        private void AppSelect_Load(object sender, EventArgs e)
        {
            //keybon.MainWindow.
            Process[] AllProcess = Process.GetProcesses();
            List<string> processNames = new List<string>();
            foreach(Process pro in AllProcess)
            {
                processNames.Add(pro.ProcessName);
            }
            processNames = processNames.Distinct().ToList();
            listBox1.DataSource = processNames;
            //listBox1.DisplayMember = "ProcessName";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.ownerForm.addAppSelection(listBox1.SelectedItem.ToString());
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
