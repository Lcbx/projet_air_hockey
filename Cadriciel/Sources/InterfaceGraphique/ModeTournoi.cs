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

        /// @fn public ModeTournoi()
        /// @brief Permet de créer le mode tournoi
        public ModeTournoi()
        {
            InitializeComponent();
            this.creationTournoi_ = new CreationTournoi();
            this.matchingTournoi_ = new MatchingTournoi();

            this.panel1.Controls.Clear();
            this.panel1.Controls.Add(this.matchingTournoi_);
        }
    }
}
