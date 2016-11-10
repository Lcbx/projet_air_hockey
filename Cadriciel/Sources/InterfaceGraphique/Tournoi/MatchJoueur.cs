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
    public partial class MatchJoueur : UserControl, INotifyPropertyChanged
    {
        private string NomJoueur_;
        public string NomJoueur {
            get { return NomJoueur_; }
            set {
                if(value != NomJoueur_) {
                    NomJoueur_ = value;
                    RaisePropertyChanged("NomJoueur");
                }
            }
        }

        private int ScoreJoueur_;
        public int ScoreJoueur
        {
            get { return ScoreJoueur_; }
            set {
                if (value != ScoreJoueur_)
                {
                    ScoreJoueur_ = value;
                    RaisePropertyChanged("ScoreJoueur");
                }
            }
        }

        /// @fn public MatchJoueur()
        /// @brief Permet de créer l'objet du match avec des valeurs par défaut
        public MatchJoueur()
        {
            InitializeComponent();
            bindProperties();
            this.NomJoueur = ""; // Aucune personne n'est assignée
            this.ScoreJoueur = 0; // Aucun score n'est assigné
        }

        /// @fn public MatchJoueur(string nomJoueur, int scoreJoueur)
        /// @brief Permet de créer l'objet du match avec des valeurs de nom et de score
        /// @param nomJoueur, Nom du joueur
        /// @param scoreJoueur, Score du joueur
        public MatchJoueur(string nomJoueur, int scoreJoueur)
        {
            InitializeComponent();
            bindProperties();
            this.NomJoueur = nomJoueur; // Aucune personne n'est assignée
            this.ScoreJoueur = scoreJoueur; // Aucun score n'est assigné
        }

        /// @fn private void bindProperties()
        /// @brief Permet de réaliser le databinding des propriétés
        private void bindProperties() {
            this.nomJoueur.DataBindings.Add(new Binding("Text", this, "NomJoueur"));
            this.scoreJoueur.DataBindings.Add(new Binding("Text", this, "ScoreJoueur"));
        }

        /// @fn protected void RaisePropertyChanged(string propertyName)
        /// @brief Permet de réaliser du databinding complet
        /// @param propertyName Nom de la propriété qui est mise à jour
        /// @source http://stackoverflow.com/questions/17764323/how-to-bind-a-simple-string-value-to-a-text-box
        public event PropertyChangedEventHandler PropertyChanged;
        protected void RaisePropertyChanged(string propertyName)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}
