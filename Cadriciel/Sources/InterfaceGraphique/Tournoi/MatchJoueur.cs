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
    /// @class public partial class MatchJoueur : UserControl
    /// @brief Permet d'afficher le nom et le score du joueur
    public partial class MatchJoueur : UserControl
    {
        /// @fn public MatchJoueur()
        /// @brief Permet de créer l'objet du match avec des valeurs par défaut
        public MatchJoueur()
        {
            InitializeComponent();
            this.nomJoueur.Text = ""; // Aucune personne n'est assignée
            this.scoreJoueur.Text = ""; // Aucun score n'est assigné
        }

        /// @fn public MatchJoueur(string nomJoueur, int scoreJoueur)
        /// @brief Permet de créer l'objet du match avec des valeurs de nom et de score
        /// @param nomJoueur, Nom du joueur
        /// @param scoreJoueur, Score du joueur
        public MatchJoueur(string nomJoueur, int scoreJoueur)
        {
            InitializeComponent();
            this.nomJoueur.Text = nomJoueur; // Aucune personne n'est assignée
            this.scoreJoueur.Text = String.Format("{0}", scoreJoueur); // Aucun score n'est assigné
        }
    }
}
