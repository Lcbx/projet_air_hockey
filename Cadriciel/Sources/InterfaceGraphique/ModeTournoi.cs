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


        /// @enum public enum StatusTournoi 
        /// @brief Différents status du tournoi
        public enum StatusTournoi {
            Creation,
            MatchMaking,
            Won
        };

        /// @fn public ModeTournoi()
        /// @brief Permet de créer le mode tournoi
        public ModeTournoi() {
            InitializeComponent();
            this.SwitchStatusTournoi(StatusTournoi.Creation);
        }

        /// @fn public ModeTournoi(MenuPrincipal parent_)
        /// @brief Permet de créer le mode tournoi
        public ModeTournoi(MenuPrincipal parent)
        {
            this.parent_ = parent;
            InitializeComponent();
            this.SwitchStatusTournoi(StatusTournoi.Creation);
        }

        /// @fn public SwitchStatusTournoi(StatusTournoi status)
        /// @brief Permet de changer le status et changer le user control
        public void SwitchStatusTournoi(StatusTournoi status) {
            this.panel1.Controls.Clear();
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
    }
}
