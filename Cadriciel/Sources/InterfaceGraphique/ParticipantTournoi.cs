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

    /// @class public partial class ParticipantTournoi : UserControl
    /// @brief Permet de créer un participant (nom et type d'usager)
    public partial class ParticipantTournoi : UserControl
    {
        private bool nameTextBoxIsSet = false;

        /// @fn public int TypeJoueur
        /// @brief Permet de get le type de joueur sélectionné
        /// @return Le type de joueur sélectionné
        public int TypeJoueur {
            get {
                return this.typeJoueurCBO.SelectedItem.GetHashCode();
            }
        }

        /// @fn public string NomJoueur
        /// @brief Permet de get le nom du joueur
        /// @return Le nom du joueur
        public string NomJoueur {
            get {
                return this.nameTextBox.Text;
            }
        }

        /// @fn public ParticipantTournoi()
        /// @brief Constructeur par défaut
        public ParticipantTournoi() {
            InitializeComponent();

            this.nameTextBox_Init();
            this.typeJoueurCBO_Init();
        }


        /// @fn private void nameTextBox_Enter(object sender, EventArgs e)
        /// @brief Permet de cacher le placeholder s'il y en a un.
        /// @param[in] sender: objet d'appel
        /// @param[in] e: évènement à gérer
        /// @return rien
        private void nameTextBox_Enter(object sender, EventArgs e) {
            if (this.nameTextBoxIsSet == false)
                this.nameTextBox.Text = "";
        }

        /// @fn private void nameTextBox_Leave(object sender, EventArgs e)
        /// @brief Permet de mettre en place le placeholder si nécessaire
        /// @param[in] sender: objet d'appel
        /// @param[in] e: évènement à gérer
        /// @return rien
        private void nameTextBox_Leave(object sender, EventArgs e) {
            if(this.nameTextBox.Text.Trim() == "") {
                this.nameTextBox_Init();
            } else {
                this.nameTextBoxIsSet = true;
            }
        }

        /// @fn private void nameTextBox_Init()
        /// @brief Permet de mettre en place le placeholder du text box
        /// @return rien
        private void nameTextBox_Init() {
            this.nameTextBoxIsSet = false;
            this.nameTextBox.Text = "Nom joueur";
        }

        /// @fn private void typeJoueurCBO_Init() {
        /// @brief Permet de charger l'ensemble des types de joueurs
        /// @return rien
        private void typeJoueurCBO_Init() {
            this.typeJoueurCBO.BeginUpdate();
            this.typeJoueurCBO.Text = "Type de joueur";
            this.typeJoueurCBO.EndUpdate();
        }
    }
}
