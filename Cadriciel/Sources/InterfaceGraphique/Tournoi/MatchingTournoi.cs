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
    /// @class public partial class MatchingTournoi : UserControl
    /// @brief Représente le match making pour un tournoi
    public partial class MatchingTournoi : UserControl
    {
        ModeTournoi parent_;
        private MatchJoueur[] matches;
        private int nbJoueurs = (int) Math.Pow(2, 3) - 1; //TODO: Refactor
        private const int stepDistance = 20;

        /// @fn public MatchingTournoi()
        /// @brief Permet de créer un MatchMaking d'un tournoi
        /// Dessine les différents participants pour le match making à partir du nombre de joueurs
        public MatchingTournoi() {
            InitializeComponent();
            this.initMatchs();
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.matchingTournoi_paint);
        }

        /// @fn public MatchingTournoi()
        /// @brief Permet de créer un MatchMaking d'un tournoi
        /// Dessine les différents participants pour le match making à partir du nombre de joueurs
        public MatchingTournoi(ModeTournoi parent)
        {
            this.parent_ = parent;
            InitializeComponent();
            this.initMatchs();
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.matchingTournoi_paint);
        }

        /// @fn private void initMatchs()
        /// @brief Permet d'initialiser la structure des matchs
        private void initMatchs() {
            this.matches = new MatchJoueur[nbJoueurs];

            this.SuspendLayout();

            int maxDepth = (int)Math.Log((nbJoueurs + 1), 2);

            for (int i = 0; i < nbJoueurs; i++)
            {
                this.matches[i] = new MatchJoueur("", 0);
                int depth = (int)Math.Log((i + 1), 2);
                int height = (i + 1) - (int)Math.Pow(2, depth);
                int ajustedHeight = height * (int)Math.Pow(2, maxDepth - depth);
                this.matches[i].Location =
                    new System.Drawing.Point(depth * (this.matches[i].Size.Width + stepDistance),
                        (ajustedHeight) * (this.matches[i].Size.Height) + this.label1.Size.Height + stepDistance);
                this.Controls.Add(this.matches[i]);
            }

            this.updateMatchups();

            this.ResumeLayout(false);
            this.PerformLayout();
        }

        /// @fn private void updateMatchups()
        /// @brief Permet de mettre à jour les participants des matchup avec le C++
        public void updateMatchups() {
            int nbMatchups = FonctionsNatives.nombreMatchupsTournoi();
            int tailleTableauChar = FonctionsNatives.plusLongNomTournoi() * nbMatchups; ;

            int[] scoresMatchups = new int[nbMatchups];
            char[] nomsJoueursMatchups = new char[tailleTableauChar];
            FonctionsNatives.loadArbreTournoi(nomsJoueursMatchups, scoresMatchups);

            string[] nomsJoueurs = new string(nomsJoueursMatchups).Split('\0');
            for(int i = 0; i < nbMatchups; i++) {
                this.matches[i].ScoreJoueur = scoresMatchups[i];
                this.matches[i].NomJoueur = nomsJoueurs[i];
            }
        }

        /// @fn private void matchingTournoi_paint(object sender, System.Windows.Forms.PaintEventArgs e)
        /// Permet de dessiner le graphe suivant pour les matchups
        ///       P2
        /// P1 ---|--- P4 (Implicite)
        ///       |
        ///       |--- P4 (Explicite)
        ///       P3
        /// @param sender Objet qui appelle la modification
        /// @param e Évènement
        /// @source https://msdn.microsoft.com/en-us/library/system.windows.forms.control.paint(v=vs.110).aspx
        /// @brief Adaptation du MSDN pour notre projet
        private void matchingTournoi_paint(object sender, System.Windows.Forms.PaintEventArgs e)
        {
            // Create a local version of the graphics object for the PictureBox.
            Graphics g = e.Graphics;

            // Draw a line in the PictureBox.
            for (int i = 1; i < nbJoueurs; i++) {
                int indexParent = (i + 1) / 2 - 1;
                // Voir le schéma dans la description de la fonction
                System.Drawing.Point point1 = new Point(this.matches[indexParent].Location.X + this.matches[indexParent].Size.Width,
                    this.matches[indexParent].Location.Y + this.matches[indexParent].Size.Height / 2);
                System.Drawing.Point point2 = new Point(point1.X + stepDistance / 2, point1.Y);
                System.Drawing.Point point4 = new Point(this.matches[i].Location.X,
                    this.matches[i].Location.Y + this.matches[i].Size.Height / 2);
                System.Drawing.Point point3 = new Point(point2.X, point4.Y);

                g.DrawLine(System.Drawing.Pens.Black, point1, point2);
                g.DrawLine(System.Drawing.Pens.Black, point2, point3);
                g.DrawLine(System.Drawing.Pens.Black, point3, point4);
            }
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int nombreMatchupsTournoi();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int plusLongNomTournoi();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void loadArbreTournoi([Out] char[] nomsJoueurs, [Out] int[] scores);
        }
    }
}
