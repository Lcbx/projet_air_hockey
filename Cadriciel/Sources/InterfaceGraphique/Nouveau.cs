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
    public partial class Nouveau : Form
    {
        private static Sauvegarde fenetreSauvegarde_;

        public Nouveau(Sauvegarde fenetreSauvegarde)
        {
            InitializeComponent();
            fenetreSauvegarde_ = fenetreSauvegarde;

        }
        //nouveau
        private void button1_Click(object sender, EventArgs e)
        {
            FonctionsNatives.initialiserScene();
            this.Close();
        }
        //annuler
        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        //enregister-sous
        private void button2_Click(object sender, EventArgs e)
        {
           fenetreSauvegarde_.Show();
           this.Close();

        }
    }
}
