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
        public static int NB_PARTICIPANTS = 4;
        private static int SPACING_PARTICIPANTS = 10; //Espace entre les participants

        private ModeTournoi parent_ = null;
        private List<ParticipantTournoi> participants = new List<ParticipantTournoi>(NB_PARTICIPANTS);

        /// @fn public CreationTournoi()
        /// @brief Permet de créer un tournoi par défaut
        public CreationTournoi()
        {
            InitializeComponent();
            this.initParticipants();
        }

        /// @fn public CreationTournoi(ModeTournoi parent)
        /// @brief Permet de créer un tournoi avec la fenêtre parent
        public CreationTournoi(ModeTournoi parent) {
            parent_ = parent;
            InitializeComponent();
            this.initParticipants();
        }

        /// @fn private void creerTournoi(object sender, EventArgs e)
        /// @brief Permet de creer un tournoi
        /// TODO: Compléter l'implémentation
        private void creerTournoi(object sender, EventArgs e) {
            this.parent_.SwitchStatusTournoi(ModeTournoi.StatusTournoi.MatchMaking);
        }

        /// @fn private void initParticipants()
        /// @brief Permet d'initialiser la liste des participants
        private void initParticipants() {
            for(int i = 0; i < NB_PARTICIPANTS; i++) {
                ParticipantTournoi participant = new ParticipantTournoi();
                participant.Location = new System.Drawing.Point(0, ((participant.Size.Height + SPACING_PARTICIPANTS) * i + this.title.Height + SPACING_PARTICIPANTS));

                this.Controls.Add(participant);

                participants.Add(participant);
            }

            //Centre pour un participant
            int center = this.participants[0].Size.Width / 2;

            this.createButton.Location = new System.Drawing.Point(
                center - this.createButton.Size.Width / 2, 
                ((participants[0].Size.Height + SPACING_PARTICIPANTS) * NB_PARTICIPANTS + this.title.Height + SPACING_PARTICIPANTS));
            this.title.Location = new System.Drawing.Point(
                center - this.title.Size.Width / 2, 0);
                
        }
    }
}
