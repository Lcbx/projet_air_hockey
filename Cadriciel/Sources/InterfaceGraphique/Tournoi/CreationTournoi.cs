using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using InterfaceGraphique.Utility;

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

        private Timer t;

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
        /// Crée le tournoi et change à la prochaine fenêtre qui est celle du match making
        private void creerTournoi(object sender, EventArgs e) {
            char[] nomZone = this.cbmZoneDeJeu.choixZoneDeJeu.PathNameFichier;
            string[] nomsParticipants = this.participants.Select(x => x.NomJoueur.ToString()).ToArray();
            bool[] sontHumains = this.participants.Select(x => x.EstHumain).ToArray();
            string[] nomsProfilsVirtuels = this.participants.Select(x => x.TypeJoueur.Nom.ToString()).ToArray();

            FonctionsNatives.createTournoi(nomZone, NB_PARTICIPANTS, nomsParticipants, sontHumains, nomsProfilsVirtuels);
            
            ///wajdi code 
            t = new Timer(); //creer le timer 
            t.Interval = 5000;     // specify interval time as you want (en milisecondes) ( 5000 = 5 sec)
            t.Tick += new EventHandler(timer1_Tick);  //evenement qui se declanche a la fin des 5 sec
            t.Start();
            this.parent_.SwitchStatusTournoi(ModeTournoi.StatusTournoi.MatchMaking);

            //enable le boutton
            this.parent_.button3.Enabled = true;

        }

        /// @fn private void initParticipants()
        /// @brief Permet d'initialiser la liste des participants
        private void initParticipants() {
            for(int i = 0; i < NB_PARTICIPANTS; i++) {
                ParticipantTournoi participant = new ParticipantTournoi();
                participant.Location = new System.Drawing.Point(0, ((participant.Size.Height + SPACING_PARTICIPANTS) * i + this.title.Height + SPACING_PARTICIPANTS));

                foreach (Control c in participant.Controls) {
                    c.Validating += ValidateForm;
                    if (c is CheckBox) (c as CheckBox).CheckedChanged += ValidateForm;
                }
                
                this.Controls.Add(participant);
                participants.Add(participant);
            }

            this.cbmZoneDeJeu.Validating += ValidateForm;
            this.createButton.Enabled = false;

            //Centre pour un participant
            int center = this.participants[0].Size.Width / 2;

            this.cbmZoneDeJeu.Location = new System.Drawing.Point(
                center - this.cbmZoneDeJeu.Size.Width / 2,
                ((participants[0].Size.Height + SPACING_PARTICIPANTS) * NB_PARTICIPANTS + this.title.Height + SPACING_PARTICIPANTS));
            this.createButton.Location = new System.Drawing.Point(
                center - this.createButton.Size.Width / 2,
                ((participants[0].Size.Height + SPACING_PARTICIPANTS) * NB_PARTICIPANTS + this.title.Height + SPACING_PARTICIPANTS * 2 + this.cbmZoneDeJeu.Height));
            this.title.Location = new System.Drawing.Point(
                center - this.title.Size.Width / 2, 0);
        }

        /// @fn private void ValidateForm(object sender, EventArgs e)
        /// @brief Permet de changer l'état du bouton de création
        /// @param sender : objet d'appel
        /// @param e : Évènement
        private void ValidateForm(object sender, EventArgs e) {
            this.createButton.Enabled = isValidForm();
        }

        //wajdi-- temps fini
        private void timer1_Tick(object sender, EventArgs e)
        {
            this.parent_.Hide();
            this.parent_.passeModeJeu();
            t.Stop();
        }

        /// @fn private bool isValidForm()
        /// @brief Permet de vérifier la validité du formulaire
        /// @return Vrai si le formulaire, faux autrement
        private bool isValidForm() {
            if (this.cbmZoneDeJeu.choixZoneDeJeu == null)
                return false;

            bool humanExists = participants.Exists(x => x.EstHumain);
            bool nomsRemplis = !participants.Exists(x => x.NomJoueur == String.Empty);
            bool uniqueNames = participants.Select(x => x.NomJoueur).Distinct().Count() == participants.Count();

            return humanExists && nomsRemplis && uniqueNames;
        }

        static partial class FonctionsNatives {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void createTournoi(char[] nomZone, int count, string[] nomsJoueurs, bool[] sontHumains, string[] nomProfils);
        }
    }
}
