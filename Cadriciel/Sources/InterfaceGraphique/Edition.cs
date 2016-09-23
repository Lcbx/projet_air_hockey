﻿using System;
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

        bool supprimer = false;
       private void ToucheEnfonce(Object o, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.LControlKey) { FonctionsNatives.toucheControle(true);  }
            if (e.KeyChar == (char)Keys.Space)
            {
                System.Console.WriteLine("Barre d'espacement appuyée. mode change en : ");
                changerMode( EtatSouris==Etats.SELECTION ? Etats.AJOUT_ACCELERATEUR:Etats.SELECTION );
            }

            //wajdi
            if (e.KeyChar == (char)Keys.Escape)
            {
                System.Console.WriteLine("Echap. enfonce  ");
                compteur = 0;
                //Determiner l'etat : ajout Portail - muret ..
                FonctionsNatives.escEnfonce(true);
                supprimer = true;
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
            lock(Program.unLock)
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
       public enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, DEBUT_AJOUT_MUR, AJOUT_MUR, DEBUT_AJOUT_PORTAIL, AJOUT_PORTAIL };

        private Etats EtatSouris = Etats.SELECTION;

        private Boolean mousePressed = false;

        public void changerMode(Etats nouvelEtat)
        {
            if (EtatSouris != nouvelEtat){
                EtatSouris = nouvelEtat;
                FonctionsNatives.etatDelaSouris((int)EtatSouris);
                string text = "";
                switch (EtatSouris)
                {
                    case Etats.SELECTION:             { text = "selection";  break; }
                    case Etats.LOUPE:                 { text = "loupe"; break; }
                    case Etats.DEPLACEMENT:           { text = "deplacement"; break; }
                    case Etats.ROTATION:              { text = "rotation"; break; }
                    case Etats.DUPLICATION:           { text = "duplication"; break; }
                    case Etats.AJOUT_ACCELERATEUR:    { text = "ajout accelerateur"; break; }
                    case Etats.DEBUT_AJOUT_MUR:       { text = "debut ajout mur"; break; }
                    case Etats.AJOUT_MUR:             { text = "ajout mur"; break; }
                    case Etats.DEBUT_AJOUT_PORTAIL:   { text = "debut ajout portail"; break; }
                    case Etats.AJOUT_PORTAIL:         { text = "ajout portail"; break; }
                    default: break;
                }
                System.Console.WriteLine(text);
            }
        }

        public void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris down : X = " + e.X + " et Y = " + e.Y);
            FonctionsNatives.clickStart(e.X, e.Y);
            if (EtatSouris == Etats.SELECTION) { Program.peutAfficher = false; }
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
           /* if (mousePressed) {
                System.Console.WriteLine("Souris move : X = " + e.X + " et Y = " + e.Y);
                FonctionsNatives.clickCurrent(e.X, e.Y);
            }*/
            //wajdi

                if (firstClick)
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

                    }

                }

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

        

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterPortail(int x1, int y1);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void escEnfonce(bool esc);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterPortailDeux(int x2, int y2);



        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterMuret(int x1, int y1, int x2, int y2);




        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterMuretFantome(int corXin, int corYin, int corX, int corY);
    }
}
