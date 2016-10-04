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
        //private static double friction_;
        //private static double rebond_;
        //private static double acceleration_;
        //private static Point point_;
        //private static double angleDeRotation_;
        //private static double facteurEchelle_;

 BoitePropriete boiteProp = new BoitePropriete();

        public Edition()
        {
            this.KeyPreview = true;
            (this as Control).KeyDown += new KeyEventHandler(keyDownHandler);
            (this as Control).KeyUp += new KeyEventHandler(keyUpHandler);
            InitializeComponent();
            InitialiserAnimation();
            supprimerToolStripMenuItem.Enabled = false;

            textBox1.Enabled = false;
            textBox2.Enabled = false;
            textBox3.Enabled = false;
            textBox4.Enabled = false;
            label6.Show();

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

        /////////////////////////////////////////////////////////////////////////
        //  gere le clavier
        /////////////////////////////////////////////////////////////////////////

        private void keyDownHandler(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.ControlKey) FonctionsNatives.toucheControl(true);
            if (e.KeyCode == Keys.Alt) FonctionsNatives.toucheAlt(true);
            if (e.KeyCode == Keys.Menu) FonctionsNatives.toucheAlt(true);
            if (e.KeyCode == Keys.Add) FonctionsNatives.zoomIn();
            if (e.KeyCode == Keys.Subtract) FonctionsNatives.zoomOut();
            if (e.KeyCode == Keys.Up) FonctionsNatives.deplacerVueXY(0,-0.1);
            if (e.KeyCode == Keys.Right) FonctionsNatives.deplacerVueXY(0.1, 0);
            if (e.KeyCode == Keys.Down) FonctionsNatives.deplacerVueXY(0, 0.1);
            if (e.KeyCode == Keys.Left) FonctionsNatives.deplacerVueXY(-0.1, 0);
        }

        private void keyUpHandler(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode) {
                case Keys.ControlKey:        { FonctionsNatives.toucheControl(false); break; }
                case Keys.Alt:               { FonctionsNatives.toucheAlt(false); break; }
                case Keys.Menu: { FonctionsNatives.toucheAlt(false); break; }
                case Keys.Escape:            { FonctionsNatives.escEnfonce(); break; }
                case Keys.Delete:            {FonctionsNatives.supprimerObjet(); break; }
                case Keys.D:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonDeplacement.Checked = true;
                        this.changerMode(Etats.DEPLACEMENT); break;
                    }
                case Keys.S:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonSelection.Checked = true;
                        this.changerMode(Etats.SELECTION); break;
                    }
                case Keys.R:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonRotation.Checked = true;
                        this.changerMode(Etats.ROTATION);break;
                    }
                case Keys.E:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonMiseAEchelle.Checked = true;
                        this.changerMode(Etats.MISEAECHELLE);break;
                    }
                case Keys.C:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonDuplication.Checked = true;
                        this.changerMode(Etats.DUPLICATION);break;
                    }
                case Keys.Z:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonZoom.Checked = true;
                        this.changerMode(Etats.LOUPE);break;
                    }
                case Keys.M:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonMuret.Checked = true;
                        this.changerMode(Etats.AJOUT_MUR);break;
                    }
                case Keys.P:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonPortail.Checked = true;
                        this.changerMode(Etats.AJOUT_PORTAIL);break;
                    }
                case Keys.B:
                    {
                        desactiverAutresBoutons();
                        toolStripButtonAccelerateur.Checked = true;
                        this.changerMode(Etats.AJOUT_ACCELERATEUR);break;
                    }
                case Keys.G:
                    {
                        desactiverAutresBoutons();
                        toolStripButton1.Checked = true;
                        this.changerMode(Etats.POINTSDECONTROLE);break;
                    }

                case Keys.O:        { FonctionsNatives.deplacerPointHaut(2); break; }//A Verifier ou a enlever !!
                default: break;
            }
        }



        /////////////////////////////////////////////////////////////////////////
        //  gere la souris
        /////////////////////////////////////////////////////////////////////////
        public enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, AJOUT_MUR, AJOUT_PORTAIL, MISEAECHELLE, POINTSDECONTROLE, REDIMENSIONNEMENT, NBETATS };

        private Etats EtatSouris = Etats.SELECTION;

        private Boolean mousePressed = false;

        private int x, y;

        public void changerMode(Etats nouvelEtat)
        {
            if (EtatSouris != nouvelEtat)
            {
                string text = "";
                switch (EtatSouris)
                {
                    case Etats.SELECTION: {             text = "selection";         break; }
                    case Etats.LOUPE: {                 text = "loupe";             break; }
                    case Etats.DEPLACEMENT: {           text = "deplacement";       break; }
                    case Etats.ROTATION: {              text = "rotation";          break; }
                    case Etats.DUPLICATION: {           text = "duplication";       break; }
                    case Etats.AJOUT_ACCELERATEUR: {    text = "ajout bonus";       break; }
                    case Etats.AJOUT_MUR: {             text = "ajout mur";         break; }
                    case Etats.AJOUT_PORTAIL: {         text = "ajout portail";     break; }
                    case Etats.MISEAECHELLE:  {         text = "mise a echelle";     break; }
                    case Etats.POINTSDECONTROLE: {      text = "points de controle"; break; }
                    default: break;
                }
                System.Console.WriteLine(text);
                EtatSouris = nouvelEtat;
                FonctionsNatives.etatDelaSouris((int)EtatSouris);
            }
        }

        public void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris down : X = " + e.X + " et Y = " + e.Y);

            if (e.Button == System.Windows.Forms.MouseButtons.Right) FonctionsNatives.rightClick(true);
            else if (EtatSouris == Etats.SELECTION || EtatSouris == Etats.LOUPE)
            {
                Program.peutAfficher = false;
            }
            FonctionsNatives.clickStart(e.X, e.Y);



            mousePressed = true;
        }

        public void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris up : X = " + e.X + " et Y = " + e.Y);

            FonctionsNatives.clickEnd(e.X, e.Y);

            if (e.Button == System.Windows.Forms.MouseButtons.Right) FonctionsNatives.rightClick(false);

            Program.peutAfficher = true;
            mousePressed = false;

          //  mettreAjourPos();
            if (EtatSouris == Etats.SELECTION)
            {
                mettreAjourPos();
            }
        }

        public void Edition_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right) FonctionsNatives.rightClick(true);
            else FonctionsNatives.rightClick(false);

            if (mousePressed) FonctionsNatives.clickCurrent(e.X, e.Y);
            else FonctionsNatives.positionSouris(e.X, e.Y);

            x = e.X; y = e.Y;

        }


        /////////////////////////////////////////////////////////////////////////
        //  ...
        /////////////////////////////////////////////////////////////////////////


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
            //afficher la boite de configuration
            boiteProp.Show();
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
     

        private void éditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int nbreObSelectionnes= FonctionsNatives.nombreObjetSelectionne();
            if(nbreObSelectionnes >= 1)
            {
                supprimerToolStripMenuItem.Enabled = true;
            }
            else
            {
                supprimerToolStripMenuItem.Enabled = false;
            }
        }
        public void Edition_MouseWheel(object sender, MouseEventArgs e)
        {
            if(e.Delta >  0)
            { FonctionsNatives.zoomIn(); }
            if(e.Delta < 0)
            { FonctionsNatives.zoomOut(); }

        }


        private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.supprimerObjet();
        }


        //data Biding
        private void mettreAjourPos()
        {
            if (FonctionsNatives.nombreObjetSelectionne() == 1)
            {
                textBox1.Enabled = true;
                textBox2.Enabled = true;
                textBox3.Enabled = true;
                textBox4.Enabled = true;
                label6.Hide();

                //Position en X
                double posX = (FonctionsNatives.getPosX());
                posX = Math.Round(posX, 2); //arrondi la position 
                textBox1.Text = posX.ToString();

                //Position Y
                double posY = (FonctionsNatives.getPosY());
                posY = Math.Round(posY, 2); //arrondi la position 
                textBox2.Text = posY.ToString();

                //Angle
                double angle = (FonctionsNatives.getAngle());
                angle = Math.Round(angle, 2);
                textBox3.Text = angle.ToString();

                //Scale
                double scale = (FonctionsNatives.getScale());
                scale = Math.Round(scale, 2);
                textBox4.Text = scale.ToString();

            }
            else
            {
                textBox1.Enabled = false;
                textBox2.Enabled = false;
                textBox3.Enabled = false;
                textBox4.Enabled = false;

                label6.Show();
                
            }
        }

        private void sélectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonSelection.Checked = true;
            this.changerMode(Etats.SELECTION);
        }

        private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDeplacement.Checked = true;
            this.changerMode(Etats.DEPLACEMENT);
        }

        private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonRotation.Checked = true;
            this.changerMode(Etats.ROTATION);
        }

        private void miseÀLéchelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMiseAEchelle.Checked = true;
            this.changerMode(Etats.MISEAECHELLE);
        }

        private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDuplication.Checked = true;
            this.changerMode(Etats.DUPLICATION);
        }

        private void ToolStripMenuItemAccelerateur_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonAccelerateur.Checked = true;
            this.changerMode(Etats.AJOUT_ACCELERATEUR);

        }

        private void portailToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonPortail.Checked = true;
            this.changerMode(Etats.AJOUT_PORTAIL);
        }

        private void muretToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMuret.Checked = true;
            this.changerMode(Etats.AJOUT_MUR);
        }

        private void gestionDesPointsDeContrôleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButton1.Checked = true;
            this.changerMode(Etats.POINTSDECONTROLE);
        }

        //button ok 
        private void button1_Click(object sender, EventArgs e)
        {
            double x = Convert.ToDouble(textBox1.Text);
            double y = Convert.ToDouble(textBox2.Text);
            double angle = Convert.ToDouble(textBox3.Text);
            double scale = Convert.ToDouble(textBox4.Text);

            //assigner les nouvelles valeurs
            FonctionsNatives.configurerObjet(x, y, angle, scale);
        }

        
        private void aideToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BoiteAide helpbox = new BoiteAide();
            helpbox.ShowDialog();
        }
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

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rightClick(bool presse);

        //touche control
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void toucheControl(bool presse);

        //touche alt
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void toucheAlt(bool presse);

        //touche escape
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void escEnfonce();



        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPosX();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPosY();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerObjet();



        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void configurerObjet(double x, double y, double angle, double scale);

        // Pour touche +
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();

        // Pour touche -
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();

        // Pour les touches de fleche
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerVueXY(double deplacementX, double deplacementY);

        //foction test bidon
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void test();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerPointHaut(int index);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int nombreObjetSelectionne();



        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getAngle();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getScale();
    }
}
