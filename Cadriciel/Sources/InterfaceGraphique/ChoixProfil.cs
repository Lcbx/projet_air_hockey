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

        // button Annuler
        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
            menu_.Show();
        }
        // button joueur Humain
        private void button1_Click(object sender, EventArgs e)
        {
            Chargement zoneChar = new Chargement(edition_);
            zoneChar.ShowDialog();
            if (zoneChar.estclique == true)
            {
                edition_.Show();

                edition_.estjoueurvirtuel = false;
                edition_.passerModePartie(true);
                edition_.resetPartie();
                edition_.ArreterJoueurVirtuel();
    

                menu_.Hide();
                this.Hide();
            }

        }
        // click sur button joueur virtuel
        private void button2_Click(object sender, EventArgs e)
        {
            FenetreProfilVirtuel fenetre = new FenetreProfilVirtuel(edition_, menu_);

            this.Hide();
           // menu_.Hide();
            fenetre.ShowDialog();
        }

    }
}
