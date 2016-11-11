using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using InterfaceGraphique.Utility;
using System.IO;

namespace InterfaceGraphique.Tournoi
{
    /// @brief Permet d'affichier un combobox de zones de jeux
    public partial class ZoneDeJeu : UserControl
    {
        /// @brief La liste pour le databinding des zones de jeux
        private BindingList<Fichier> listeFichiers;

        /// @brief Permet d'obtenir le fichier de la zone de jeux
        public Fichier choixZoneDeJeu {
            get {
                return (Fichier) this.cbmZonesDeJeu.SelectedItem;
            }
        }

        /// @fn public bool setChoixZone(char[] nomZone)
        /// @brief Permet de choisir la zone de jeu à partir de son nom
        /// @param nomZone : Nom de la zone de jeu
        /// @return True if a zone with the name exists, false otherwise
        public bool setChoixZone(char[] nomZone) {
            string stripNomZone = new string(nomZone).Split('\0')[0];
            Fichier choix = this.listeFichiers.FirstOrDefault(x => x.PathNameFichier.SequenceEqual(stripNomZone.ToCCharArray()));
            if(choix != null) {
                this.cbmZonesDeJeu.SelectedItem = choix;
                return true;
            }
            return false;
        }

        /// @biref Constructeur par défaut de la zone de jeu
        public ZoneDeJeu()
        {
            InitializeComponent();

            listeFichiers = new BindingList<Fichier>(Fichier.getListFichierZones());
            cbmZonesDeJeu.DataSource = listeFichiers;
            cbmZonesDeJeu.DisplayMember = "NomFichier";
        }

    }
}
