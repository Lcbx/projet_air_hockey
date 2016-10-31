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
        Edition edition_;

        public ChoixProfil()
        {
            InitializeComponent();
        }

        public void setMenuPrincipal(MenuPrincipal menuPrincipal, Edition edition)
        {
            menu_ = menuPrincipal;
            edition_ = edition;

        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
            menu_.Show();
        }
        // humain
        private void button1_Click(object sender, EventArgs e)
        {
            Chargement zoneChar = new Chargement(edition_);
            zoneChar.ShowDialog();
            if (zoneChar.estclique == true)
            {
                edition_.Show();
                edition_.passerModePartie(true);
                this.Hide();
            }

        }
        //virtuel
        private void button2_Click(object sender, EventArgs e)
        {
            Chargement zoneChar = new Chargement(edition_);
            zoneChar.ShowDialog();
            if (zoneChar.estclique == true)
            {
                edition_.Show();
                edition_.passerModePartie(true);
                // demarer le joueur virtuel
                edition_.DemarerJoueurVirtuel(1, 0.5);
                this.Hide();
            }

        }
    }
}
