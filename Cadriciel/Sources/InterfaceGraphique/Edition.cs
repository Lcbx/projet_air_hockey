using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;



namespace InterfaceGraphique
{
    public partial class Edition : Form
    {
        private static MenuPrincipal menuPrincipal_;
        private static double friction_;
        private static double rebond_;
        private static double acceleration_;
        private static Point point_;
        private static double angleDeRotation_;
        private static double facteurEchelle_;



        public Edition()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
            InitializeComponent();
            InitialiserAnimation();

            this.panel1.Resize += new System.EventHandler(this.panel1_Resize);
            FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height);
        }

        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;

            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }

        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();
                });
            }
            catch (Exception)
            {
            }

        }

        private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {
            //if(e.KeyChar == (char)Keys.LControlKey) FonctionsNatives.toucheControle(true);
            if (e.KeyChar == (char)Keys.Space)
            {
                System.Console.WriteLine("Barre d'espacement appuyée. mode change en : ");
                changerMode(EtatSouris == Etats.SELECTION ? Etats.AJOUT_ACCELERATEUR : Etats.SELECTION);
            }
        }

        private void nouveauToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Console.WriteLine("Nouveau");
        }

        private void quitterToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Console.WriteLine("Quitter");
        }

        private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }
        }
        public void setMenuPrincipal(MenuPrincipal menuPrincipal)
        {
            menuPrincipal_ = menuPrincipal;
        }
        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            menuPrincipal_.Show();
            this.Hide();
        }
        private void propriétésToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.splitContainer1.Enabled = true;
        }

        private void toolStripButtonSelection_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonSelection.Checked = true;
            this.changerMode(Etats.SELECTION);
        }

        private void toolStripButtonDeplacement_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDeplacement.Checked = true;
            this.changerMode(Etats.DEPLACEMENT);

        }

        private void toolStripButtonRotation_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonRotation.Checked = true;
            this.changerMode(Etats.ROTATION);
        }

        private void toolStripButtonMiseAEchelle_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMiseAEchelle.Checked = true;
            this.changerMode(Etats.MISEAECHELLE);
        }

        private void toolStripButtonDuplication_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDuplication.Checked = true;
            this.changerMode(Etats.DUPLICATION);
        }

        private void toolStripButtonZoom_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonZoom.Checked = true;
            this.changerMode(Etats.LOUPE);
        }

        private void toolStripButtonAccelerateur_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonAccelerateur.Checked = true;
            this.changerMode(Etats.AJOUT_ACCELERATEUR);

        }

        private void toolStripButtonPortail_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonPortail.Checked = true;
            this.changerMode(Etats.AJOUT_PORTAIL);
        }

        private void toolStripButtonMuret_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMuret.Checked = true;
            this.changerMode(Etats.AJOUT_MUR);
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButton1.Checked = true;
            this.changerMode(Etats.POINTSDECONTROLE);

        }
        private void desactiverAutresBoutons()
        {
            toolStripButtonSelection.Checked = false;
            toolStripButtonDeplacement.Checked = false;
            toolStripButtonRotation.Checked = false;
            toolStripButtonMiseAEchelle.Checked = false;
            toolStripButtonDuplication.Checked = false;
            toolStripButtonZoom.Checked = false;
            toolStripButtonAccelerateur.Checked = false;
            toolStripButtonPortail.Checked = false;
            toolStripButtonMuret.Checked = false;
            toolStripButton1.Checked = false;
        }
        ///////////////////////////////////////////////////////////////////////
        //bool Dans_Intervalle( double valeur, double borneMin, double borneMax ) 
        ///
        /// Cette fonction vérifie si une valeur est dans un intervalle.
        ///
        /// @param[in] valeur   : La valeur à vérifier.
        /// @param[in] borneMin : La borne inférieure de l'intervalle.
        /// @param[in] borneMax : La borne supérieure de l'intervalle.
        ///
        /// @return Vrai si la valeur est dans l'intervalle, faux autrement.
        //
        //////////////////////////////////////////////////////////////////////////////////////////

        bool Dans_Intervalle(double valeur, double borneMin, double borneMax)
        {
            return (valeur >= borneMin) && (valeur <= borneMax);
        }
        ///  //////////////////////////////////////////////////////////////////////
        ///void numericUpDown1_ValueChanged(object sender, EventArgs e)
        /// Cette fonction affecte la valeur de friction de l'interface dans 
        ///
        /// @param[in] valeur   : La valeur à vérifier.
        /// @param[in] borneMin : La borne inférieure de l'intervalle.
        /// @param[in] borneMax : La borne supérieure de l'intervalle.
        ///
        /// @return Vrai si la valeur est dans l'intervalle, faux autrement.
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if (Dans_Intervalle(Convert.ToDouble(numericUpDown1.Value), 0.0, 1.5))
                friction_ = Convert.ToDouble(numericUpDown1.Value);
        }

        ///  //////////////////////////////////////////////////////////////////////
        ///void numericUpDown1_ValueChanged(object sender, EventArgs e)
        /// Cette fonction affecte la valeur de friction de l'interface dans 
        ///
        /// @param[in] valeur   : La valeur à vérifier.
        /// @param[in] borneMin : La borne inférieure de l'intervalle.
        /// @param[in] borneMax : La borne supérieure de l'intervalle.
        ///
        /// @return Vrai si la valeur est dans l'intervalle, faux autrement.
        /// ////////////////////////////////////////////////////////////////////

        private void numericUpDown2_ValueChanged(object sender, EventArgs e)
        {
            if (Dans_Intervalle(Convert.ToDouble(numericUpDown2.Value), -1.0, 1.0))
                rebond_ = Convert.ToDouble(numericUpDown2.Value);
        }
        private void numericUpDown3_ValueChanged(object sender, EventArgs e)
        {
            if (Dans_Intervalle(Convert.ToDouble(numericUpDown3.Value), 0.0, 200))
                acceleration_ = Convert.ToDouble(numericUpDown3.Value);
        }

        private void numericUpDown4_ValueChanged(object sender, EventArgs e)
        {
            if (Dans_Intervalle(Convert.ToDouble(numericUpDown4.Value), 0.0, 200))
                point_.X = Convert.ToInt32(numericUpDown4.Value);
        }

        private void numericUpDown5_ValueChanged(object sender, EventArgs e)
        {
            if (Dans_Intervalle(Convert.ToDouble(numericUpDown5.Value), 0.0, 200))
                point_.Y = Convert.ToInt32(numericUpDown5.Value);
        }


        private void numericUpDown6_ValueChanged(object sender, EventArgs e)
        {
            if (Dans_Intervalle(Convert.ToDouble(numericUpDown6.Value), 0.0, 200))
                angleDeRotation_ = Convert.ToDouble(numericUpDown6.Value);
            System.Console.WriteLine("Rotation:" + angleDeRotation_);
        }
        private void numericUpDown7_ValueChanged(object sender, EventArgs e)
        {
            if (Dans_Intervalle(Convert.ToDouble(numericUpDown7.Value), 0.0, 200))
                facteurEchelle_ = Convert.ToDouble(numericUpDown7.Value);
            System.Console.WriteLine("Facteur d' échelle:" + facteurEchelle_);
        }





        /////////////////////////////////////////////////////////////////////////
        //  gere la souris
        /////////////////////////////////////////////////////////////////////////
        public enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL, MISEAECHELLE, POINTSDECONTROLE, NBETATS };

        private Etats EtatSouris = Etats.SELECTION;

        private Boolean mousePressed = false;

        public void changerMode(Etats nouvelEtat)
        {
            if (EtatSouris != nouvelEtat)
            {
                EtatSouris = nouvelEtat;
                FonctionsNatives.etatDelaSouris((int)EtatSouris);
                string text = "";
                switch (EtatSouris)
                {
                    case Etats.SELECTION: { text = "selection"; break; }
                    case Etats.LOUPE: { text = "loupe"; break; }
                    case Etats.DEPLACEMENT: { text = "deplacement"; break; }
                    case Etats.ROTATION: { text = "rotation"; break; }
                    case Etats.DUPLICATION: { text = "duplication"; break; }
                    case Etats.AJOUT_ACCELERATEUR: { text = "ajout accelerateur"; break; }
                    case Etats.DEBUT_AJOUT_MUR: { text = "debut ajout mur"; break; }
                    case Etats.AJOUT_MUR: { text = "ajout mur"; break; }
                    case Etats.DEBUT_AJOUT_PORTAIL: { text = "debut ajout portail"; break; }
                    case Etats.AJOUT_PORTAIL: { text = "ajout portail"; break; }
                    default: break;
                }
                System.Console.WriteLine(text);

            }
        }

        public void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris down : X = " + e.X + " et Y = " + e.Y);
            FonctionsNatives.clickStart(e.X, e.Y);
            if (EtatSouris == Etats.SELECTION) Program.peutAfficher = false;
            mousePressed = true;
        }
        public void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris up : X = " + e.X + " et Y = " + e.Y);
            FonctionsNatives.clickEnd(e.X, e.Y);
            Program.peutAfficher = true;
            mousePressed = false;
        }
        public void Edition_MouseMove(object sender, MouseEventArgs e)
        {
            if (mousePressed) FonctionsNatives.clickCurrent(e.X, e.Y);
            else FonctionsNatives.positionSouris(e.X, e.Y);
        }

        private void panel1_Resize(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height);
        }


        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void initialiserOpenGL(IntPtr handle);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void libererOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void dessinerOpenGL();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void animer(double temps);


            //Click

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void etatDelaSouris(int etat);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void clickStart(int x, int y);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void clickCurrent(int x, int y);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void clickEnd(int x, int y);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void positionSouris(int x, int y);

            // Redimensionnement de la fenêtre

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)] // pour utiliser une fonction qui se trouve dans le fichier Noyau.dll
            public static extern void redimensionnerFenetre(int largeur, int hauteur);


        }
    }
}
