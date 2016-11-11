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
    /// @class public partial class ModeTournoi : Form
    /// @brief Fenêtre du mode tournoi
    /// TODO: Transformer en observateur pour créer le changement de fenêtre
    public partial class ModeTournoi : Form
    {
        private CreationTournoi creationTournoi_;
        private MatchingTournoi matchingTournoi_;
        private MenuPrincipal parent_;
        

        //wajdi 
        private Chargement menuChargement_;
        private Edition edition_;


        /// @enum public enum StatusTournoi 
        /// @brief Différents status du tournoi
        public enum StatusTournoi {
            Creation,
            MatchMaking,
            Won
        };

        private StatusTournoi mode;

        /// @fn public ModeTournoi()
        /// @brief Permet de créer le mode tournoi
        public ModeTournoi() {
            InitializeComponent();
            this.initTournoi();
        }

        /// @fn public ModeTournoi(MenuPrincipal parent_)
        /// @brief Permet de créer le mode tournoi
        public ModeTournoi(MenuPrincipal parent)
        {
            mode = StatusTournoi.Creation;
            this.parent_ = parent;
            InitializeComponent();
            this.initTournoi();

            this.VisibleChanged += ModeTournoi_Shown;

            //State
            this.parent_.edition_.state = Edition.States.Tournoi;
            parent_.setTournoi(this);
        }

        /// @fn private void ModeTournoi_Shown(object sender, EventArgs e)
        /// @brief Permet de réaliser des modifications à l'affichage
        /// @param sender : Objet d'envois
        /// @param e : Évènement
        private void ModeTournoi_Shown(object sender, EventArgs e)
        {
            if (Visible == false) //Workaround for Shown
                return;

            if (mode == StatusTournoi.Creation)
            {
                this.creationTournoi_.refreshProfils();
            }
        }

        /// @fn public SwitchStatusTournoi(StatusTournoi status)
        /// @brief Permet de changer le status et changer le user control
        public void SwitchStatusTournoi(StatusTournoi status) {
            this.panel1.Controls.Clear();
            this.mode = status;
            if (status == StatusTournoi.Creation) {
                this.creationTournoi_ = new CreationTournoi(this);
                this.panel1.Controls.Add(this.creationTournoi_);
            } else {
                this.matchingTournoi_ = new MatchingTournoi(this);
                this.panel1.Controls.Add(this.matchingTournoi_);
            }
        }

        /// @fn private void button1_Click(object sender, EventArgs e)
        /// @brief Permet de revenir au menu principal
        /// @param sender, Objet d'envois
        /// @param e, Évènement
        private void button1_Click(object sender, EventArgs e)
        {
            this.parent_.Show();
            this.Hide();
        }

        /// @fn private void initTournoi()
        /// @brief Permet d'initialiser la fenêtre du tournoi
        private void initTournoi(){
            this.SwitchStatusTournoi(StatusTournoi.Creation);

            this.panel1.Size = new System.Drawing.Size(0, 0);
            this.panel1.AutoSize = true;
            this.panel1.Location = new Point(
                this.ClientSize.Width / 2 - this.panel1.Size.Width / 2,
                this.ClientSize.Height / 2 - this.panel1.Size.Height / 2);
            this.panel1.Anchor = AnchorStyles.None;
        }

        /// @fn public void setEdition(Edition edition) 
        /// @brief Permet de lier la fenêtre d'édition au mode tournoi
        public void setEdition(Edition edition) {
            edition_ = edition;
        }


        //wajdi -- permet de passer au mode partie rapide (a travers la selection de zone 
        public void passeModeJeu()
        {
            this.Hide();
            setEdition(this.parent_.getEdition());

            Chargement zoneChar = new Chargement(edition_);
            zoneChar.ShowDialog();

            if (zoneChar.estclique == true)
            {
                edition_.Show();
                // 
                edition_.estjoueurvirtuel = false;
                edition_.passerModePartie(true);
                edition_.resetPartie();
            }
        }
        //wajdi -- sert a appeller la fct qui a son tour affiche la fenetre de chargement
        private void button3_Click(object sender, EventArgs e)
        {
            passeModeJeu();
        }
        

    }
}
