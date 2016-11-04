////////////////////////////////////////////////////////////////////////////////////
/// @file MenuPrincipal.cs
/// @author Medaoud Ikram
/// @date 2016-10-10
/// @version 1.0 
///
////////////////////////////////////////////////////////////////////////////////////
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
    public partial class MenuPrincipal : Form
    {
        private Edition edition_;
        private Configuration configuration_;
        private ModeTournoi tournoi_ = new ModeTournoi();


        public MenuPrincipal()
        {
            InitializeComponent();
            this.tournoi.Click += new System.EventHandler(this.modeTournoiClick);
        }

        public void setMenu(Edition edition, Configuration configuration)
        {
            edition_=edition;
            configuration_ = configuration;
        }


        private void quitter_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void editeur_Click(object sender, EventArgs e)
        {
          
            edition_.Show();                   //  l'afficher
            this.Hide();                      // fermer la fenêtre Menu principal

        }

        private void partieRapide_Click(object sender, EventArgs e)
        {
            edition_.Show();
            this.Hide();    
        }

       
        private void configuration_Click(object sender, EventArgs e)
        {
           configuration_.Show();  //  afficher la boite de configuration quand on clique sur  
           this.Hide();
        }

        /// <summary>
        /// Permet d'afficher la fenêtre du mode tournoi
        /// </summary>
        /// <param name="sender">Objet sur lequel l'évènement a été produit</param>
        /// <param name="e">Les arguments d'évèment</param>
        private void modeTournoiClick(object sender, EventArgs e) {
            tournoi_.Show();
            this.Hide();
        }
    }
}
