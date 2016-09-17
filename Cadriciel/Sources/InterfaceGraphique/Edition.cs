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


        public Edition()
        {
            this.KeyPress += new KeyPressEventHandler(ToucheEnfonce);
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


        /////////////////////////////////////////////////////////////////////////
        //  gere la souris
        /////////////////////////////////////////////////////////////////////////
        public enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL, MISEAECHELLE };

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
            if (mousePressed)
            {
                //System.Console.WriteLine("Souris in : X = " + e.X + " et Y = " + e.Y);
                FonctionsNatives.clickCurrent(e.X, e.Y);
            }
        }


        private void propriétésToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.splitContainer1.Enabled = true;
        }

        private void toolStripButtonSelection_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.SELECTION);
        }

        private void toolStripButtonDeplacement_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.DEPLACEMENT);

        }

        private void toolStripButtonRotation_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.ROTATION);
        }

        private void toolStripButtonMiseAEchelle_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.MISEAECHELLE);
        }

        private void toolStripButtonDuplication_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.DUPLICATION);
        }

        private void toolStripButtonZoom_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.LOUPE);
        }

        private void toolStripButtonAccelerateur_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.AJOUT_ACCELERATEUR);

        }

        private void toolStripButtonPortail_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.AJOUT_PORTAIL);
        }

        private void toolStripButtonMuret_Click(object sender, EventArgs e)
        {
            this.changerMode(Etats.AJOUT_MUR);
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            //this.changerMode(Etats.CONTROLDEPOINTS);

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
        public static extern void toucheControle(bool pressee);
    }
}
