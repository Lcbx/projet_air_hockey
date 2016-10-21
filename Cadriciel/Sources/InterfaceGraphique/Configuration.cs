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
    public partial class Configuration : Form
    {
        private static MenuPrincipal menuPrincipal_;
        private int toucheDeplaceAGauche_ = (int)Keys.A;
        private int toucheDeplaceEnBas_ = (int)Keys.S;
        private int toucheDeplaceADroite_ = (int)Keys.D;
        private int toucheDeplaceEnHaut_ = (int)Keys.W;




        public Configuration()

        {
            InitializeComponent();
        }

        public void setMenuPrincipalConfig(MenuPrincipal menuPrincipal)
        {
            menuPrincipal_ = menuPrincipal;
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
          
                if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
                {
                   toucheDeplaceAGauche_ = e.KeyValue;
                  // KeysConverter kc = new KeysConverter();
                  //string keyChar = kc.ConvertToString(e.KeyData);
                  // this.textBox1.Text=keyChar;
                }
                }
                     

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceAGauche_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
                toucheDeplaceADroite_ = e.KeyValue;
        }

        private void textBox3_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceAGauche_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue )
                toucheDeplaceEnBas_ = e.KeyValue;
        }

        private void textBox4_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
                toucheDeplaceEnHaut_ = e.KeyValue;
        }


        private void renitialisation_Click(object sender, EventArgs e)
        {
            toucheDeplaceAGauche_ = (int)Keys.A;
            toucheDeplaceEnBas_ = (int)Keys.S;
            toucheDeplaceADroite_ = (int)Keys.D;
            toucheDeplaceEnHaut_ = (int)Keys.W;
        }

        private void appliquer_Click(object sender, EventArgs e)
        {
            this.Hide();
            menuPrincipal_.Show();
        }
    }
}
