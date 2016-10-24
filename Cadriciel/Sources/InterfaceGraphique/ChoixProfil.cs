using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class ChoixProfil : Form
    {
        MenuPrincipal menu_;

        public ChoixProfil()
        {
            InitializeComponent();
        }

        public void setMenuPrincipal(MenuPrincipal menuPrincipal)
        {
            menu_ = menuPrincipal;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
            menu_.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
           

        }
    }
}
