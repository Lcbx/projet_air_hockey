using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
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
        private Edition edition_;


        /// @enum public enum StatusTournoi 
        /// @brief Différents status du tournoi
        public enum StatusTournoi
        {
            Creation,
            MatchMaking,
            Won
        };

        private StatusTournoi mode;

        /// @fn public ModeTournoi()
        /// @brief Permet de créer le mode tournoi
        public ModeTournoi()
        {
            InitializeComponent();
            this.initTournoi();
            this.KeyDown += ModeTournoi_KeyDown;
            this.KeyPreview = true;
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

            this.KeyDown += ModeTournoi_KeyDown;
            this.KeyPreview = true;

            //State
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
        public void SwitchStatusTournoi(StatusTournoi status)
        {
            this.panel1.Controls.Clear();
            this.mode = status;
            if (status == StatusTournoi.Creation)
            {
                this.creationTournoi_ = new CreationTournoi(this);
                this.panel1.Controls.Add(this.creationTournoi_);
            }
            else
            {
                this.matchingTournoi_ = new MatchingTournoi(this);
                this.panel1.Controls.Add(this.matchingTournoi_);
            }
        }

        /// @fn private void retourMenuPrincipal(object sender, EventArgs e)
        /// @brief Permet de revenir au menu principal
        /// @param sender, Objet d'envois
        /// @param e, Évènement
        private void retourMenuPrincipal(object sender, EventArgs e)
        {
            this.parent_.Show();
            this.Hide();
        }

        /// @fn private void initTournoi()
        /// @brief Permet d'initialiser la fenêtre du tournoi
        private void initTournoi()
        {
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
        public void setEdition(Edition edition)
        {
            edition_ = edition;
        }

        /// @fn public void passeModeJeu()
        /// @brief Permet de jouer une partie du mode tournoi
        public void passeModeJeu()
        {
            if(this.mode == StatusTournoi.MatchMaking) { 
                if (!FonctionsNatives.gagnerMatchVirtuelsTournoi()) {
                    this.Hide();
                    Edition ptr = this.parent_.edition_;
                    ptr.state = Edition.States.Tournoi;
                    FonctionsNatives.preparerProchainMatchTournoi();
                    ptr.passerModePartie(true);
                    ptr.resetPartie();
                    ptr.Show();
                } else {
                    this.matchingTournoi_.updateMatchups();
                }
            }
        }

        /// @fn private void MatchingTournoi_KeyDown(object sender, KeyEventArgs e)
        /// @brief Permet de capturer l'appuis de la barre d'espacement
        private void ModeTournoi_KeyDown(object sender, KeyEventArgs e)
        {
            if (this.mode != StatusTournoi.Creation)
            {
                if (e.KeyCode == Keys.Space) {
                    this.passeModeJeu();
                }
            }
        }

        /// @fn private void ModeTournoi_FormClosing(object sender, FormClosingEventArgs e)
        /// @brief Permet de fermer la fenêtre du mode tournoi de façon standard
        private void ModeTournoi_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing) {
                e.Cancel = true;
                parent_.Show();
                this.Hide();
            }
        }

        static partial class FonctionsNatives {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void preparerProchainMatchTournoi();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool gagnerMatchVirtuelsTournoi();
        }
    }
}
