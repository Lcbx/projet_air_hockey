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

namespace InterfaceGraphique
{

    /// @class public partial class ParticipantTournoi : UserControl
    /// @brief Permet de créer un participant (nom et type d'usager)
    public partial class ParticipantTournoi : UserControl
    {
        private bool nameTextBoxIsSet = false;
        private List<Profil> profileList;

        /// @fn public int TypeJoueur
        /// @brief Permet de get le type de joueur sélectionné
        /// @return Le type de joueur sélectionné
        public Profil TypeJoueur {
            get {
                if (this.typeJoueurCBO.Enabled)
                    return (Profil)this.typeJoueurCBO.SelectedItem;
                else
                    return new Profil();
            }
        }

        /// @fn public void setTypeJoueur(string nomType)
        /// @brief Permet de set le type de joueur sélectionné
        /// @param nomType Nom du profil sélectionné
        public void setTypeJoueur(string nomType) {
            Profil profilChoisi = this.profileList.Find(x => x.Nom == nomType);
            if (profilChoisi != null) {
                this.typeJoueurCBO.SelectedItem = profilChoisi;
            }
        }

        /// @fn public void setEstHumain(bool estHumain)
        /// @brief Permet de changer si le joueur est humain ou non
        /// @param estHumain : Si le joueur est humain ou non
        public void setEstHumain(bool estHumain) {
            this.isHuman.Checked = estHumain;
        }

        public void setNomJoueur(string nomJoueur) {
            this.nameTextBox.Text = nomJoueur;
            if (this.nameTextBox.Text.Trim() == "") {
                this.nameTextBox_Init();
            }
            else
            {
                this.nameTextBoxIsSet = true;
            }
        }

        public bool EstHumain {
            get {
                return this.isHuman.Checked;
            }
        }

        /// @fn public string NomJoueur
        /// @brief Permet de get le nom du joueur
        /// @return Le nom du joueur
        public string NomJoueur {
            get {
                if(this.nameTextBoxIsSet)
                    return this.nameTextBox.Text;
                return String.Empty;
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
            this.profileList = Profil.obtenirListeNomsProfils();
            this.typeJoueurCBO.DataSource = this.profileList;
            this.typeJoueurCBO.DisplayMember = "Nom";
            this.typeJoueurCBO.EndUpdate();
        }


        /// @fn private void isHuman_CheckedChanged(object sender, EventArgs e)
        /// @brief Permet de retirer la sélection d'un profil
        /// @return rien
        private void isHuman_CheckedChanged(object sender, EventArgs e) {
            this.typeJoueurCBO.Enabled = !this.isHuman.Checked;
        }

        /// @fn public void refreshProfils()
        /// @brief Permet de rafraichir la liste des profils
        public void refreshProfils() {
            string nom = this.TypeJoueur.Nom;
            this.profileList = Profil.obtenirListeNomsProfils();
            this.typeJoueurCBO.DataSource = this.profileList;
            this.setTypeJoueur(nom);
        }


        static partial class FonctionsNatives {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void obtenirListeProfils(int[] noms);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int obtenirNombreProfils();
        }
    }
}
