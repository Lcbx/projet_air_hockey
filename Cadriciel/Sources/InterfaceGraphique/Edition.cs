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
            (this as Control).KeyDown += new KeyEventHandler(keyDownHandler);
            (this as Control).KeyUp += new KeyEventHandler(keyUpHandler);
            InitializeComponent();
            InitialiserAnimation();

           

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

        private void keyDownHandler(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.ControlKey) FonctionsNatives.toucheControl(true);
        }

        bool supprimer = false;
        private void keyUpHandler(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode) {
                case Keys.ControlKey:   FonctionsNatives.toucheControl(false);  break; 
                case Keys.Escape:       FonctionsNatives.escEnfonce();          break;
                case Keys.Delete:
                    {
                        System.Console.WriteLine("touche Delete");
                        FonctionsNatives.supprimerObjet();
                    
                        break; }

                default: break;
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



        /////////////////////////////////////////////////////////////////////////
        //  gere la souris
        /////////////////////////////////////////////////////////////////////////
        public enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL, MISEAECHELLE, POINTSDECONTROLE, REDIMENSIONNEMENT, NBETATS };

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
                    case Etats.SELECTION: {             text = "selection";         break; }
                    case Etats.LOUPE: {                 text = "loupe";             break; }
                    case Etats.DEPLACEMENT: {           text = "deplacement";       break; }
                    case Etats.ROTATION: {              text = "rotation";          break; }
                    case Etats.DUPLICATION: {           text = "duplication";       break; }
                    case Etats.AJOUT_ACCELERATEUR: {    text = "ajout accelerateur"; break; }
                    case Etats.DEBUT_AJOUT_MUR: {       text = "debut ajout mur";   break; }
                    case Etats.AJOUT_MUR: {             text = "ajout mur";         break; }
                    case Etats.DEBUT_AJOUT_PORTAIL: {   text = "debut ajout portail"; break; }
                    case Etats.AJOUT_PORTAIL: {         text = "ajout portail";     break; }
                    default: break;
                }
                System.Console.WriteLine(text);
            }
        }

        public void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris down : X = " + e.X + " et Y = " + e.Y);
            FonctionsNatives.clickStart(e.X, e.Y);
            mettreAjourPos();
            if (EtatSouris == Etats.SELECTION)
            {
                Program.peutAfficher = false;
                mettreAjourPos();
            }

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

            //wajdi

            /* if (firstClick)
             {
                 if (coordXin != e.X && coordYin != e.Y)
                 {
                     if (!supprimer)
                     {
                         FonctionsNatives.ajouterMuretFantome(coordXin, coordYin, e.X, e.Y);
                         supprimer = true;
                     }
                    // int nb = FonctionsNatives.obtenirNombreElemntSurScene();
                     FonctionsNatives.ajouterMuret(coordXin, coordYin, e.X, e.Y);
                    /*if ((nb + 1) == FonctionsNatives.obtenirNombreElemntSurScene())
                     {
                         supprimer = false;
                     }*/

            //  }

            // }

        }

        


        int compteur = 0;
        bool firstClick = false;
        int coordXin = 0, coordYin = 0;

        private void panel1_MouseClick(object sender, MouseEventArgs e)
        {
            //ETAT AJOUT PORTAIL

            /*
                   //FonctionsNatives.ajouterPortail(e.X, e.Y);

                   //Pour vérifier qu'on a cliqué 2 fois 
                     compteur += 1;
                     if (compteur <= 1)
                     {
                         compteur += 1;
                         System.Console.WriteLine("Premier clic:  x=  " + e.X + " y= " + e.Y);
                         FonctionsNatives.ajouterPortail(e.X, e.Y);

                     }
                     if (compteur > 2)
                     {
                           System.Console.WriteLine("Deuxieme clic:  x=  " + e.X + " y= " + e.Y);
                           compteur = 0;
                           FonctionsNatives.ajouterPortailDeux(e.X, e.Y);
                      }
                         */

            //Etat AJOUT MURET

            /*
                        //Pour vérifier qu'on a cliqué 2 fois 
                        compteur += 1;
                        if (compteur <= 1)
                        {
                            compteur += 1;
                            System.Console.WriteLine("Premier clic:  x=  " + e.X + " y= " + e.Y);
                            firstClick = true;
                            coordXin = e.X;
                            coordYin = e.Y;

                        }
                        if (compteur > 2)
                        {
                            System.Console.WriteLine("Deuxieme clic:  x=  " + e.X + " y= " + e.Y);
                            compteur = 0;
                            FonctionsNatives.ajouterMuret(coordXin, coordYin, e.X, e.Y);
                            firstClick = false;
                        }

                        */

        }

        private void propriétésToolStripMenuItem_Click(object sender, EventArgs e)
        {
        
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
            this.changerMode(Etats.DEBUT_AJOUT_PORTAIL);
        }

        private void toolStripButtonMuret_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMuret.Checked = true;
            this.changerMode(Etats.DEBUT_AJOUT_MUR);
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
      
       

   

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            
        }


        //data Biding
        private void mettreAjourPos()
        {

            //Position en X
            System.Console.WriteLine("Mettre a jour");
            double posX= (FonctionsNatives.getPosX());
            posX=Math.Round(posX, 2); //arrondi la position 

            boiteProp.textBox1.Text = posX.ToString();

            //Position Y

            System.Console.WriteLine("Mettre a jour");
            double posY = (FonctionsNatives.getPosY());
            posX = Math.Round(posY, 2); //arrondi la position 

            boiteProp.textBox2.Text = posY.ToString();

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

        //touche escape
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void toucheControl(bool presse);

        //touche escape
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void escEnfonce();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterPortail(int x1, int y1);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterPortailDeux(int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterMuret(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterMuretFantome(int corXin, int corYin, int corX, int corY);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPosX();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPosY();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerObjet();



        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerObjet(double x, double y);

    }
}
