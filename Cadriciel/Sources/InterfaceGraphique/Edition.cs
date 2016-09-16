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
            if (e.KeyChar == (char)Keys.Space)
            {
                System.Console.WriteLine("Barre d'espacement appuyée.");
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

        //gere la souris
        
        public enum Etats { SELECTION=0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, AJOUT_MUR, AJOUT_PORTAIL };
        private Etats EtatSouris = Etats.SELECTION;
        public void changerMode(Etats nouvelEtat)
        {
            if (EtatSouris != nouvelEtat)
            {
                EtatSouris = nouvelEtat;
                FonctionsNatives.etatDelaSouris((int)EtatSouris);
            }
        }

        private Boolean mousePressed = false;

        public void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris down : X = " + e.X + " et Y = " + e.Y);
            mousePressed = true;
        }
        public void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            System.Console.WriteLine("Souris up : X = " + e.X + " et Y = " + e.Y);
            mousePressed = false;
        }
        public void Edition_MouseMove(object sender, MouseEventArgs e)
        {
            
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

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void etatDelaSouris(int etat);
    }
}
