using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    /// @class public partial class CreationTournoi : UserControl
    /// @brief Permet de créer un tournoi
    public partial class CreationTournoi : UserControl
    {
        ModeTournoi parent_;

        /// @fn public CreationTournoi()
        /// @brief Permet de créer un tournoi par défaut
        public CreationTournoi()
        {
            InitializeComponent();
        }

        /// @fn public CreationTournoi(ModeTournoi parent)
        /// @brief Permet de créer un tournoi avec la fenêtre parent
        public CreationTournoi(ModeTournoi parent) {
            parent_ = parent;
            InitializeComponent();
        }

        /// @fn private void creerTournoi(object sender, EventArgs e)
        /// @brief Permet de creer un tournoi
        /// TODO: Compléter l'implémentation
        private void creerTournoi(object sender, EventArgs e) {
            this.parent_.SwitchStatusTournoi(ModeTournoi.StatusTournoi.MatchMaking);
        }
    }
}
