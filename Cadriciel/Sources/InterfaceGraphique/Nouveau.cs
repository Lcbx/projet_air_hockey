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
    /// @class Nouveau
    /// @brief Permet d'afficher une boîte de dialogue afin d'éviter la suppression de la table
    public partial class Nouveau : Form
    {
        private static Sauvegarde fenetreSauvegarde_;

        /// @fn public Nouveau(Sauvegarde fenetreSauvegarde)
        /// @param fenetreSauvegarde Fenêtre de sauvegarde à appeler si nécessaire
        /// @brief Constructeur par paramètre
        public Nouveau(Sauvegarde fenetreSauvegarde)
        {
            InitializeComponent();
            fenetreSauvegarde_ = fenetreSauvegarde;
            TopMost = true;

        }

        /// @fn private void nouvelleTable(object sender, EventArgs e)
        /// @brief Permet d'initialiser une nouvelle table
        /// @param sender Objet d'appel
        /// @param e Évènement qui cause l'appel
        private void nouvelleTable(object sender, EventArgs e)
        {
            this.reinitialiserTable();
            this.Close();
        }

        /// @fn private void annuler(object sender, EventArgs e)
        /// @brief Permet d'annuler la création d'une nouvelle table
        /// @param sender Objet d'appel
        /// @param e Évènement qui cause l'appel
        private void annuler(object sender, EventArgs e)
        {
            this.Close();
        }

        /// @fn private void enregistrerSous(object sender, EventArgs e)
        /// @brief Permet d'enregistrer sous une table si le nom du fichier n'existe pas, sinon enregistre dans le nom du fichier
        /// @param sender Objet d'appel
        /// @param e Évènement qui cause l'appel
        private void enregistrerSous(object sender, EventArgs e)
        {
            if (fenetreSauvegarde_.Filename == String.Empty) {
                fenetreSauvegarde_.WipeAfter = true;
                fenetreSauvegarde_.Show();
            } else {
                fenetreSauvegarde_.saveLastFile();
            }
            this.Close();

        }

        /// @fn private void reinitialiserTable()
        /// @brief Permet de réinitialiser la table
        private void reinitialiserTable() {
            FonctionsNatives.initialiserScene();
            fenetreSauvegarde_.Filename = "";
        }
    }
}
