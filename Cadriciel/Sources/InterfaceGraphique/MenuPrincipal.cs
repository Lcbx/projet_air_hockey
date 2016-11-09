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
        public Edition edition_;
        private Configuration configuration_;
        public ModeTournoi tournoi_;


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

        public void setTournoi (ModeTournoi tournoi)
        {
            tournoi_ = tournoi;
        }
        private void quitter_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void editeur_Click(object sender, EventArgs e)
        {
         
            edition_.Show();                   //  l'afficher
            this.Hide();                      // fermer la fenêtre Menu principal
            edition_.passerModeTest(false);
        }

        private void partieRapide_Click(object sender, EventArgs e)
        {
            ChoixProfil choix = new ChoixProfil();
            
            choix.setMenuPrincipal(this, edition_);
            choix.Show();

            //Chargement zoneChar = new Chargement(edition_);
            //zoneChar.ShowDialog();
            //if (zoneChar.estclique == true)
            //{
            //    edition_.Show();
            //    edition_.passerModePartie(true);
            //    this.Hide();
            //}
        }

       
        private void configuration_Click(object sender, EventArgs e)
        {
           configuration_.ShowDialog();  //  afficher la boite de configuration quand on clique sur  
           //this.Hide();
        }

        /// <summary>
        /// Permet d'afficher la fenêtre du mode tournoi
        /// </summary>
        /// <param name="sender">Objet sur lequel l'évènement a été produit</param>
        /// <param name="e">Les arguments d'évèment</param>
        private void modeTournoiClick(object sender, EventArgs e) {
            if(this.tournoi_ == null || this.tournoi_.IsDisposed)
                this.tournoi_ = new ModeTournoi(this);

            tournoi_.Show();
            this.Hide();
        }
    }
}
