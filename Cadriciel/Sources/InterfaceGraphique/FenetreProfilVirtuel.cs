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

    public partial class FenetreProfilVirtuel : Form
    {
        public Edition edition_;

        public FenetreProfilVirtuel(Edition edition)
        {
            InitializeComponent();
            edition_ = edition;
        }


        private void chargerProfil_Click(object sender, EventArgs e)
        {
            Chargement zoneChar = new Chargement(edition_);
            
            zoneChar.ShowDialog();
            if (zoneChar.estclique == true)
            {
                edition_.Show();
                //edition_.BringToFront();
                
                edition_.passerModePartie(true);
                // demarer le joueur virtuel
                edition_.estjoueurvirtuel = true;
                // il faut passer les parametres du joueur virtuel ici
                // TODO recuper vitesse et prob du joueur 

                edition_.DemarerJoueurVirtuel(1, 0.5);
                edition_.resetPartie();
                this.Hide();

            }
        }
    }
}
