////////////////////////////////////////////////////////////////////////////////////
/// @file Edition.cs
/// @author Medaoud Ikram
/// @date 2016-9-15
/// @version 1.0 
///
////////////////////////////////////////////////////////////////////////////////////

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

        private static Sauvegarde fenetreSauvegarde_;
        private static Chargement fenetreChargement_;
        private static Nouveau boiteNouv;

        public bool estEnModeTest = false;
        public bool estEnPause = false;
        public bool estEnModePartie = false;
        public bool estjoueurvirtuel = false;


        public bool avant = false;
        public bool arriere = false;
        public bool haut = false;
        public bool bas = false;

        // Ali
        // mode partie rapide
        
        public int nbButsJoueur1 = 0;
        public int nbButsJoueur2 = 0;

        int ancienPosX;
        int ancienPosY;

        /////////////////////////////////////////////////////////////////////////
        ///  @fn public Edition()
        /// 
        ///  @brief Constructeur de la classe Edition
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        public Edition()
        {
            this.KeyPreview = true;
            (this as Control).KeyDown += new KeyEventHandler(keyDownHandler);
            (this as Control).KeyUp += new KeyEventHandler(keyUpHandler);
            (this as Control).KeyDown += new KeyEventHandler(toucheManuel);
            (this as Control).KeyUp += new KeyEventHandler(toucheManuel2);

            InitializeComponent();
            InitialiserAnimation();
            supprimerToolStripMenuItem.Enabled = false;

            textBox1.Enabled = false;
            textBox2.Enabled = false;
            textBox3.Enabled = false;
            //  textBox4.Enabled = false;
            numericUpDown1.Enabled = false;
            numericUpDown1.ResetText();

            button1.Enabled = false;
            label6.Show();

            this.panel1.Resize += new System.EventHandler(this.panel1_Resize);
            FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height);


            this.enregistrerToolStripMenuItem.Click += new System.EventHandler(this.enregistrerToolStripMenuItem_Click);
            // FonctionsNatives.passerLargeur(panel1.Width);

            fenetreSauvegarde_ = new Sauvegarde(this);
            fenetreChargement_ = new Chargement(this);
            boiteNouv = new Nouveau(fenetreSauvegarde_);

            //masquer bouton mode edition quand on est dans le mode edition
            modeEditionToolStripMenuItem.Visible = false;

            // make textbox joueur 1 et 2 uneditable
            this.textBox4.ReadOnly = true;
            this.textBox5.ReadOnly = true;


           ancienPosX = panel1.Location.X;
           ancienPosY = panel1.Location.Y;

            panel2.Hide();
        

        }



        /////////////////////////////////////////////////////////////////////////
        ///  @fn         public void InitialiserAnimation()
        /// 
        ///  @brief Permet d'initialiser le contexte OpenGL
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()       
        {
            this.DoubleBuffered = false;

            FonctionsNatives.initialiserOpenGL(panel1.Handle);
            FonctionsNatives.dessinerOpenGL();
        }


        /////////////////////////////////////////////////////////////////////////
        ///  @fn   public void MettreAJour(double tempsInterAffichage)
        /// 
        ///  @brief mettre a jour le contexte openGl, cette methode est appelé a chaque Delta(temps) 
        ///  pour refraichir la scene
        /// 
        /// @param[in] double tempsInterAffichage
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {   
                this.Invoke((MethodInvoker)delegate 
                {  
                    FonctionsNatives.animer(tempsInterAffichage);
                    FonctionsNatives.dessinerOpenGL();

                    /// Ali
                    /// On demare la partie rapide

                    if (estEnModePartie)
                        DemarrerPartie();
                    // si je suis en mode test
                    if (estEnModeTest)
                    {
                        if (FonctionsNatives.estButDroite() || FonctionsNatives.estButGauche())
                        {
                            FonctionsNatives.reinitialiserPartieCourante();
                            FonctionsNatives.setButDroite(false);
                            FonctionsNatives.setButGauche(false);
                        }
                    }
          

                });

            }
            catch (Exception)
            {
            }

        }


        /////////////////////////////////////////////////////////////////////////
        ///  @fn   private void keyDownHandler(object sender, KeyEventArgs e)
        /// 
        ///  @brief gere les clics du clavier en mode down (juste appuyer sur la touche) 
        ///  
        /// @param[in] sender , e
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void keyDownHandler(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.ControlKey) FonctionsNatives.toucheControl(true);
            if (e.KeyCode == Keys.Alt) FonctionsNatives.toucheAlt(true);
            if (e.KeyCode == Keys.Menu) FonctionsNatives.toucheAlt(true);
            if (e.KeyCode == Keys.Add) FonctionsNatives.zoomIn();
            if (e.KeyCode == Keys.Subtract) FonctionsNatives.zoomOut();
            if (e.KeyCode == Keys.Up) FonctionsNatives.deplacerVueXY(0, -0.1);
            if (e.KeyCode == Keys.Right) FonctionsNatives.deplacerVueXY(0.1, 0);
            if (e.KeyCode == Keys.Down) FonctionsNatives.deplacerVueXY(0, 0.1);
            if (e.KeyCode == Keys.Left) FonctionsNatives.deplacerVueXY(-0.1, 0);
        }


        private void toucheManuel(object sender, KeyEventArgs e)
        {
            //TO-DO: Changer les touches par les touches enregistres !!
            
            int temp = e.KeyValue;
            int avant_ = Program.configuration.toucheDeplaceADroite_;
            int arriere_ = Program.configuration.toucheDeplaceAGauche_;
            int haut_ = Program.configuration.toucheDeplaceEnHaut_;
            int bas_ = Program.configuration.toucheDeplaceEnBas_;


            //deplacer le maillet de 2eme joueur
            if (estEnModeTest == true || estEnModePartie == true)
            {
                if (estEnPause == false) // si on est pause, on ne peut pas deplacer le maillet
                {
                    if (!estjoueurvirtuel)
                    {
                        if (temp == avant_)//avant
                        {
                            avant = true;
                            if (haut)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(1, 1);
                            }
                            else if (bas)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(1, -1);
                            }
                            else FonctionsNatives.deplacerMailletAvecClavier(1, 0);
                        }

                        if (temp == arriere_)//arriere
                        {
                            arriere = true;
                            if (haut)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(-1, 1);
                            }
                            else if (bas)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(-1, -1);
                            }
                            else FonctionsNatives.deplacerMailletAvecClavier(-1, 0);

                        }

                        if (temp == haut_)//haut
                        {
                            haut = true;
                            if (avant)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(1, 1);
                            }
                            else if (arriere)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(-1, 1);
                            }

                            else FonctionsNatives.deplacerMailletAvecClavier(0, 1);

                        }
                        if (temp == bas_)//bas
                        {
                            bas = true;

                            if (avant)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(1, -1);
                            }
                            else if (arriere)
                            {
                                FonctionsNatives.deplacerMailletAvecClavier(-1, -1);
                            }
                            else FonctionsNatives.deplacerMailletAvecClavier(0, -1);
                        }
                    } // endif joueurvirtuel
                }   // endif enpause
            }   // endif modetest || modepartierapide
        }


        private void toucheManuel2(object sender, KeyEventArgs e)
        {
            int temp = e.KeyValue;
            int avant_ = Program.configuration.toucheDeplaceADroite_;
            int arriere_ = Program.configuration.toucheDeplaceAGauche_;
            int haut_ = Program.configuration.toucheDeplaceEnHaut_;
            int bas_ = Program.configuration.toucheDeplaceEnBas_;

            //deplacer le maillet de 2eme joueur
            if (estEnModeTest == true || estEnModePartie == true)
            {
                if (estEnPause == false) // si on est pause, on ne peut pas deplacer le maillet
                {
                    if (!estjoueurvirtuel)
                    {
                        if (temp == avant_) avant = false;
                        if (temp == arriere_) arriere = false;
                        if (temp == haut_) haut = false;
                        if (temp == bas_) bas = false; //bas
                    }
                }
            }
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn   private void keyUpHandler(object sender, KeyEventArgs e)
        /// 
        ///  @brief gere les clics du clavier en mode up (appuyer et relacher sur la touche) 
        ///  
        /// @param[in] sender , e
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void keyUpHandler(object sender, KeyEventArgs e)
        {
            //Dans le mode edition
            if (estEnModeTest == false && estEnModePartie == false)
            {
                // deactiver le joueur virtuel
                ArreterJoueurVirtuel();

                switch (e.KeyCode)
                {
                    case Keys.ControlKey: { FonctionsNatives.toucheControl(false); break; }
                    case Keys.Alt: { FonctionsNatives.toucheAlt(false); break; }
                    case Keys.Menu: { FonctionsNatives.toucheAlt(false); break; }
                    case Keys.Delete: { FonctionsNatives.supprimerObjet(); break; }
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
                            this.changerMode(Etats.ROTATION); break;
                        }
                    case Keys.E:
                        {
                            desactiverAutresBoutons();
                            toolStripButtonMiseAEchelle.Checked = true;
                            this.changerMode(Etats.MISEAECHELLE); break;
                        }
                    case Keys.C:
                        {
                            desactiverAutresBoutons();
                            toolStripButtonDuplication.Checked = true;
                            this.changerMode(Etats.DUPLICATION); break;
                        }
                    case Keys.Z:
                        {
                            desactiverAutresBoutons();
                            toolStripButtonZoom.Checked = true;
                            this.changerMode(Etats.LOUPE); break;
                        }
                    case Keys.M:
                        {
                            desactiverAutresBoutons();
                            toolStripButtonMuret.Checked = true;
                            this.changerMode(Etats.AJOUT_MUR); break;
                        }
                    case Keys.P:
                        {
                            desactiverAutresBoutons();
                            toolStripButtonPortail.Checked = true;
                            this.changerMode(Etats.AJOUT_PORTAIL); break;
                        }
                    case Keys.B:
                        {
                            desactiverAutresBoutons();
                            toolStripButtonAccelerateur.Checked = true;
                            this.changerMode(Etats.AJOUT_ACCELERATEUR); break;
                        }
                    case Keys.G:
                        {
                            desactiverAutresBoutons();
                            toolStripButton1.Checked = true;
                            this.changerMode(Etats.POINTSDECONTROLE); break;
                        }
                    case Keys.T:
                        {
                            //afficher fenetre test 
                            passerModeTest(true);
                            break;
                        }
                    case Keys.Escape:
                        {
                            FonctionsNatives.escEnfonce();
                            break;
                        }
                    case Keys.J: {
                            FonctionsNatives.changerLumieresActives(true, false, false);
                            break;
                        }
                    case Keys.K: {
                            FonctionsNatives.changerLumieresActives(false, true, false);
                            break;
                        }
                    case Keys.L: {
                            FonctionsNatives.changerLumieresActives(false, false, true);
                            break;
                        }

                    default: break;
                }
            }
            //dans le mode test
            else if(estEnModeTest == true && estEnModePartie == false)
            {
                switch (e.KeyCode)
                {
                    case Keys.Escape:// pause
                        {
                            afficherBarreMenu(); break;
                        }
                    case Keys.T://revenir au menu edition
                        {
                            //afficher fenetre edition
                            passerModeTest(false);
                            break;
                        }
                    case Keys.Space: //reinitialiser la partie
                        {
                            FonctionsNatives.reinitialiserPartieCourante();
                            break;
                        }
                    case Keys.V:    // Activer le joueur Virtuelle
                        {
                            if (estEnModeTest && !estEnModePartie)
                            {
                                estjoueurvirtuel = true;
                                DemarerJoueurVirtuel(10, 1);
                            }
                            break;
                        }
                    case Keys.B:    // Deactiver le joueur Virtuelle
                        {
                            if (estEnModeTest && !estEnModePartie)
                            {
                                estjoueurvirtuel = false;
                                ArreterJoueurVirtuel();
                            }
                            break;
                        }

                    default: break;

                }

            }
            else if (estEnModeTest == false && estEnModePartie == true)
            {
                switch (e.KeyCode)
                {
                    case Keys.Escape:// pause
                        {
                            afficherBarreMenu(); break;
                        }
                    case Keys.Space: //reinitialiser la partie
                        {
                            resetPartie();
                            FonctionsNatives.reinitialiserPartieCourante();
                            break;
                        }
                    case Keys.V:    // Activer le joueur Virtuelle
                        {
                            DemarerJoueurVirtuel(1, 0.5);
                            break;
                        }
                    case Keys.B:    // Deactiver le joueur Virtuelle
                        {
                            ArreterJoueurVirtuel();
                            break;
                        }

                    default: break;  

                }
            }
        } 


        public enum Etats { SELECTION = 0, LOUPE, DEPLACEMENT, ROTATION, DUPLICATION, AJOUT_ACCELERATEUR, AJOUT_MUR, AJOUT_PORTAIL, MISEAECHELLE, POINTSDECONTROLE, REDIMENSIONNEMENT, NBETATS, TEST };

        private Etats EtatSouris = Etats.SELECTION;

        private Boolean mousePressed = false;

        private int x, y;

        /////////////////////////////////////////////////////////////////////////
        ///  @fn  public void changerMode(Etats nouvelEtat)
        /// 
        ///  @brief Machine a etat pour gerer les differents scenarios d'edtions 
        ///  
        /// @param[in] Etats nouvelEtat
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void changerMode(Etats nouvelEtat)
        {
            if (EtatSouris != nouvelEtat)
            {
                string text = "";
                switch (EtatSouris)
                {
                    case Etats.SELECTION: { text = "selection"; break; }
                    case Etats.LOUPE: { text = "loupe"; break; }
                    case Etats.DEPLACEMENT: { text = "deplacement"; break; }
                    case Etats.ROTATION: { text = "rotation"; break; }
                    case Etats.DUPLICATION: { text = "duplication"; break; }
                    case Etats.AJOUT_ACCELERATEUR: { text = "ajout bonus"; break; }
                    case Etats.AJOUT_MUR: { text = "ajout mur"; break; }
                    case Etats.AJOUT_PORTAIL: { text = "ajout portail"; break; }
                    case Etats.MISEAECHELLE: { text = "mise a echelle"; break; }
                    case Etats.POINTSDECONTROLE: { text = "points de controle"; break; }
                    default: break;
                }
                System.Console.WriteLine(text);
                EtatSouris = nouvelEtat;
                FonctionsNatives.etatDelaSouris((int)EtatSouris);
            }
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn   public void panel1_MouseDown(object sender, MouseEventArgs e)
        /// 
        ///  @brief gerer les modes de clics sur la souris (DOWN)
        ///  
        /// @param[in] object sender, MouseEventArgs e)
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right) FonctionsNatives.rightClick(true);
            else if (EtatSouris == Etats.SELECTION || EtatSouris == Etats.LOUPE)
            {
                Program.peutAfficher = false;
            }
            FonctionsNatives.clickStart(e.X, e.Y);
            mousePressed = true;
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn   public void panel1_MouseUp(object sender, MouseEventArgs e)
        /// 
        ///  @brief gerer les modes de clics sur la souris (UP)
        ///  
        /// @param[in] object sender, MouseEventArgs e)
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            FonctionsNatives.clickEnd(e.X, e.Y);

            if (e.Button == System.Windows.Forms.MouseButtons.Right) FonctionsNatives.rightClick(false);

            Program.peutAfficher = true;
            mousePressed = false;

            mettreAjourPos();
            if (EtatSouris == Etats.SELECTION)
            {
                mettreAjourPos();
            }
        }

        bool signeInterdiction = false;
        /////////////////////////////////////////////////////////////////////////
        ///  @fn  Edition_MouseMove(object sender, MouseEventArgs e)
        /// 
        ///  @brief gerer les mouvements de la souris
        ///  
        /// @param[in] object sender, MouseEventArgs e
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void Edition_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Right) FonctionsNatives.rightClick(true);
            else FonctionsNatives.rightClick(false);

            if (mousePressed) signeInterdiction = !FonctionsNatives.clickCurrent(e.X, e.Y);
            else signeInterdiction = !FonctionsNatives.positionSouris(e.X, e.Y);

            if (signeInterdiction && (EtatSouris == Etats.AJOUT_ACCELERATEUR || EtatSouris == Etats.AJOUT_MUR || EtatSouris == Etats.AJOUT_PORTAIL))
                Cursor.Current = Cursors.No;

            else Cursor.Current = Cursors.Default;

            x = e.X; y = e.Y;


            //bouger maillet avec souris
            if (estEnModeTest || estEnModePartie )
            {
                if (estEnPause == false)
                {
                    FonctionsNatives.deplacerMailletAvecSouris(e.X, e.Y);
                    //Ali 
                    // La rondelle peut deplacer
                    FonctionsNatives.activerRondelle();
                }
                else
                    FonctionsNatives.deactiverRondelle();
            }
        }



        /////////////////////////////////////////////////////////////////////////
        ///  @fn  private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        /// 
        ///  @brief liberer l'openGl  a la fermeture de l'application
        ///  
        /// @param[in] object sender, FormClosingEventArgs e
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Exemple_FormClosing(object sender, FormClosingEventArgs e)
        {
            lock (Program.unLock)
            {
                FonctionsNatives.libererOpenGL();
                Program.peutAfficher = false;
            }

            //e.Cancel = true;
            //menuPrincipal_.Show();
            //this.Hide();
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn  public void setMenuPrincipal(MenuPrincipal menuPrincipal)
        /// 
        ///  @brief associer le menu principal a cette fenetre
        ///  
        /// @param[in] object sender, FormClosingEventArgs e
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void setMenuPrincipal(MenuPrincipal menuPrincipal)
        {
            menuPrincipal_ = menuPrincipal;
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn  private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief retourner au menu principal
        ///  
        /// @param[in] object sender, EventArgs e
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void menuPrincipalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            menuPrincipal_.Show();
            estEnModeTest = false;
            this.Hide();
            //this.Close();
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn  private void propriétésToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief afficher la boite de proprietes
        ///  
        /// @param[in] object sender, EventArgs e
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void propriétésToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //afficher la boite de configuration
            BoitePropriete boiteProp = new BoitePropriete();
            boiteProp.Show();
        }
        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void toolStripButtonSelection_Click(object sender, EventArgs e) 
        ///
        ///  @brief Change le mode pour sélection
        ///  
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état selection sont appelée.
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonSelection_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonSelection.Checked = true;
            this.changerMode(Etats.SELECTION);
        }
        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void toolStripButtonDeplacement_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour Deplacement
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état déplacement sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonDeplacement_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDeplacement.Checked = true;
            this.changerMode(Etats.DEPLACEMENT);

        }
        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void toolStripButtonRotation_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour Rotation
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état de rotation sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonRotation_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonRotation.Checked = true;
            this.changerMode(Etats.ROTATION);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  
        ///  @fn  private void toolStripButtonMiseAEchelle_Click(object sender, EventArgs e)
        ///  
        ///  @brief Change le mode pour Mise à l'échelle
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état mise à l'échelle sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonMiseAEchelle_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMiseAEchelle.Checked = true;
            this.changerMode(Etats.MISEAECHELLE);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void toolStripButtonDuplication_Click(object sender, EventArgs e)
        ///  @brief Change le mode pour Duplication
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état duplication sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonDuplication_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDuplication.Checked = true;
            this.changerMode(Etats.DUPLICATION);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void toolStripButtonZoom_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour Zoom
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état Zoom sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonZoom_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonZoom.Checked = true;
            this.changerMode(Etats.LOUPE);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fnprivate void toolStripButtonAccelerateur_Click(object sender, EventArgs e)
        ///  @brief Change le mode pour l'ajout d'un portail
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état l'ajout d'un portail sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonAccelerateur_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonAccelerateur.Checked = true;
            this.changerMode(Etats.AJOUT_ACCELERATEUR);

        }
        /////////////////////////////////////////////////////////////////////////
        /// 
        ///  @fn private void toolStripButtonPortail_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour ajouter un accelerateur
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état de l'ajout d'un accelerateur sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonPortail_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonPortail.Checked = true;
            this.changerMode(Etats.AJOUT_PORTAIL);
        }
        /////////////////////////////////////////////////////////////////////////
        /// 
        ///  @fn private void toolStripButtonMuret_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour l'ajout d'un muret 
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état de l'ajout d'un muret  sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButtonMuret_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMuret.Checked = true;
            this.changerMode(Etats.AJOUT_MUR);
        }
        /////////////////////////////////////////////////////////////////////////
        ///  
        ///  @fn private void toolStripButton1_Click(object sender, EventArgs e)
        /// 
        ///  @brief Changer a l'etat Point de Controle
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButton1.Checked = true;
            this.changerMode(Etats.POINTSDECONTROLE);

        }

        /////////////////////////////////////////////////////////////////////////
        //  private void desactiverAutresBoutons()
        ///
        /// ette fonction désactive tous les boutons de la barre d'outil dans la form edition
        ///
        /// @param[in] valeur   : La valeur à vérifier.
        /// @param[in] borneMin : La borne inférieure de l'intervalle.
        /// @param[in] borneMax : La borne supérieure de l'intervalle.
        ///
        /// @return Vrai si la valeur est dans l'intervalle, faux autrement.
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
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
        /// @fn bool Dans_Intervalle( double valeur, double borneMin, double borneMax ) 
        ///
        /// @brief Cette fonction vérifie si une valeur est dans un intervalle.
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


        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void éditionToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// @brief afficher le menu Edition, verifie aussi si un objet est selectionné
        /// pour activer ou desactiver le boutton "supprimer"
        ///
        /// @param[in] Sender   
        /// @param[in] e : l'evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void éditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int nbreObSelectionnes = FonctionsNatives.nombreObjetSelectionne();
            if (nbreObSelectionnes >= 1)
            {
                supprimerToolStripMenuItem.Enabled = true;   
            }
            else
            {  
                supprimerToolStripMenuItem.Enabled = false;
            }
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn   public void Edition_MouseWheel(object sender, MouseEventArgs e)
        ///
        /// @brief permet d'appeller les methodes zoomIn() ou zoomOut() selon la valeur de delta
        ///
        /// @param[in] Sender   
        /// @param[in] e : l'evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void Edition_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            { FonctionsNatives.zoomIn(); }
            if (e.Delta < 0)
            { FonctionsNatives.zoomOut(); }

        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn   private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// @brief permet d'appeller la methode supprimerObjet() afin d'enlever les objets selectionnés 
        ///
        /// @param[in] Sender   
        /// @param[in] e : l'evenement
        ///
        ///
        /// @return Vrai si la valeur est dans l'intervalle, faux autrement.
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void supprimerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.supprimerObjet();
        }



        ///////////////////////////////////////////////////////////////////////
        /// @fn    private void mettreAjourPos()
        ///
        /// @brief Data biding , permet d'afficher les informations d'un objet 
        /// dans la barre de configuration 
        ///
        /// @param[in] rien
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void mettreAjourPos()
        {
            if (FonctionsNatives.nombreObjetSelectionne() == 1)
            {
                textBox1.Enabled = true;
                textBox2.Enabled = true;
                textBox3.Enabled = true;
                //textBox4.Enabled = true;

                numericUpDown1.Enabled = true;
                button1.Enabled = true;

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
                float scale = (float)(FonctionsNatives.getScale());
                scale = (float)Math.Round(scale, 3);
                // textBox4.Text = scale.ToString();
                numericUpDown1.Value = Convert.ToDecimal(scale);
            }
            else
            {
                textBox1.Text = " ";
                textBox2.Text = " ";
                textBox3.Text = " ";
                // textBox4.Text = " ";
                numericUpDown1.ResetText();

                textBox1.Enabled = false;
                textBox2.Enabled = false;
                textBox3.Enabled = false;
                // textBox4.Enabled = false;
                numericUpDown1.Enabled = false;
                button1.Enabled = false;

                label6.Show();

            }
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void sélectionToolStripMenuItem_Click(object sender, EventArgs e) 
        ///
        ///  @brief Change le mode pour sélection
        ///  
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état selection sont appelée.
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void sélectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonSelection.Checked = true;
            this.changerMode(Etats.SELECTION);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour Deplacement
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état déplacement sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void déplacementToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDeplacement.Checked = true;
            this.changerMode(Etats.DEPLACEMENT);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour Rotation
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état de rotation sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void rotationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonRotation.Checked = true;
            this.changerMode(Etats.ROTATION);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  
        ///  @fn  private void miseÀLéchelleToolStripMenuItem_Click(object sender, EventArgs e)
        ///  
        ///  @brief Change le mode pour Mise à l'échelle
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état mise à l'échelle sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void miseÀLéchelleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMiseAEchelle.Checked = true;
            this.changerMode(Etats.MISEAECHELLE);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  @fn private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        ///  @brief Change le mode pour Duplication
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état duplication sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void duplicationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonDuplication.Checked = true;
            this.changerMode(Etats.DUPLICATION);
        }

        /////////////////////////////////////////////////////////////////////////
        /// 
        ///  @fn private void ToolStripMenuItemAccelerateur_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour ajouter un accelerateur
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état de l'ajout d'un accelerateur sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void ToolStripMenuItemAccelerateur_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonAccelerateur.Checked = true;
            this.changerMode(Etats.AJOUT_ACCELERATEUR);

        }

        /////////////////////////////////////////////////////////////////////////
        /// 
        ///  @fn private void portailToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour ajouter un accelerateur
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état de l'ajout d'un accelerateur sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void portailToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonPortail.Checked = true;
            this.changerMode(Etats.AJOUT_PORTAIL);
        }

        /////////////////////////////////////////////////////////////////////////
        /// 
        ///  @fn private void muretToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief Change le mode pour l'ajout d'un muret 
        /// Quand on clique sur ce bouton, la méthode qui désactive tous les boutons,desactiverAutresBoutons(), 
        /// et qui active l'état de l'ajout d'un muret  sont appelée.
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void muretToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonMuret.Checked = true;
            this.changerMode(Etats.AJOUT_MUR);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  
        ///  @fn private void gestionDesPointsDeContrôleToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief Changer a l'etat Point de Controle
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void gestionDesPointsDeContrôleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButton1.Checked = true;
            this.changerMode(Etats.POINTSDECONTROLE);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  
        ///  @fn private void  button1_Click(object sender, EventArgs e)
        /// 
        ///  @brief gere l'evenement du clic sur le  bouton ok de la barre de configuration 
        ///  et appliquer les changement sur l'objet
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void button1_Click(object sender, EventArgs e)
        {

            double myX;
            double myY;
            double myAngle;
            double myScale = Convert.ToDouble(numericUpDown1.Value);


            if (!double.TryParse(textBox1.Text, out myX) || !double.TryParse(textBox2.Text, out myY)
                || !double.TryParse(textBox3.Text, out myAngle))// || !double.TryParse(textBox4.Text, out myScale))
            {
                MessageBox.Show("Veuillez vérifier les valeurs entrées", "Barre de proprietés",
                 MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            else
            {
                FonctionsNatives.configurerObjet(myX, myY, myAngle, myScale);
                if (FonctionsNatives.objetEstDansLaTable() == false)
                {
                    MessageBox.Show("Les coordonnées saisies sont à l'éxterieur de la table ", "Position invalide!",
                                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }


        /////////////////////////////////////////////////////////////////////////
        ///  
        ///  @fn private void  zoomToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief permet de passer a l'état de zoom
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        {
            desactiverAutresBoutons();
            toolStripButtonZoom.Checked = true;
            this.changerMode(Etats.LOUPE);
        }

        /////////////////////////////////////////////////////////////////////////
        ///  
        ///  @fn private void  aideToolStripMenuItem_Click(object sender, EventArgs e)
        /// 
        ///  @brief afficher le help box
        /// 
        /// @param[in] sender : Le bouton
        /// @param[in]  e  :Contenant les informations sur l' évènement 
        ///
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void aideToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BoiteAide helpbox = new BoiteAide();
            helpbox.ShowDialog();
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn private void panel1_Resize(object sender, EventArgs e)
        ///
        /// @brief Cette fonction appelle la méthode redimensionnement.
        ///
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void panel1_Resize(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel1.Width, panel1.Height);
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn private  void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// @brief afficher la fenetre de sauvegarde
        ///
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void enregistrerSousToolStripMenuItem_Click(object sender, EventArgs e)
        {

            fenetreSauvegarde_.Show();
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn private  void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// @brief sauvegarder directement si le fichier existe deja sinon afficher la fenetre de sauvegarde
        ///
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void enregistrerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (getCurrentFile() == "")
                fenetreSauvegarde_.Show();
            else
                fenetreSauvegarde_.saveLastFile();
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn private void nouveauToolStripMenuItem_Click_1
        ///
        /// @brief afficher la fenetre nouveau 
        ///
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void nouveauToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            boiteNouv.ShowDialog();
            //FonctionsNatives.initialiserScene();
        }



        ///////////////////////////////////////////////////////////////////////
        /// @fn private void panel1_MouseOut(object sender, EventArgs e)
        ///
        /// @brief permet de changer la forme du cursor
        ///
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void panel1_MouseOut(object sender, EventArgs e)
        {
            Cursor = Cursors.Default;
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// @brief permet d'ouvrir la fenetre de chargement d'un fichier
        ///
        /// @param[in] sender : Le bouton
        /// @param[in et out ]  e  :Contenant les informations sur l' évènement 
        ///
        /// @return aucun
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void ouvrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fenetreChargement_.Show();
        }

        private string currentFile_;
        public static string SAVE_FILEPATH = "zones";
        public static string DEFAULT_FILENAME = "defaut";

        ///////////////////////////////////////////////////////////////////////
        /// @fn string getCurrentFile()
        ///
        /// @brief permet d'obtenir le nom du fichier 
        ///
        /// @param[in] rien
        ///
        ///
        /// @return le nom du fichier
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public string getCurrentFile()
        {
            return currentFile_;
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn public void setCurrentFile()
        ///
        /// @brief permet d'assigner un nom du fichier 
        ///
        /// @param[in] value: le nom du fichier
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void setCurrentFile(string value)
        {
            if (value != DEFAULT_FILENAME)
                currentFile_ = value;
            else
                currentFile_ = "";
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn public void passerModeTest(bool mode)
        ///
        /// @brief permet de faire le passage du mode edition au mode Test et vice versa 
        /// selon la valeur du booleen
        ///
        /// @param[in] mode: bool qui determine le mode 
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void passerModeTest(bool mode)
        {
            //si mode jeu ou test , masquer les menus a cotés + barre des menus
            if (mode == true)
            {

                panel1.Location = new Point (0,0);
                panel1.Dock = DockStyle.Fill;

                this.Text = "Mode Test";
                estEnModeTest = true;
                estEnModePartie = false;

                this.changerMode(Etats.TEST);
                //Permet d'ajouter les maillets et la rondelle dans la table
                FonctionsNatives.ajouterMailletEtRondelle();
                //effacer les points de controle
                FonctionsNatives.effacerPointControle();

                estEnPause = false;


                toolStrip1.Hide();
                menuStrip1.Hide();

                //masquer les boutons
                éditionToolStripMenuItem.Visible = false;
                outilsToolStripMenuItemPoints.Visible = false;
                informationsToolStripMenuItem.Visible = false;
                ouvrirToolStripMenuItem.Visible = false;
                nouveauToolStripMenuItem.Visible = false;
                enregistrerToolStripMenuItem.Visible = false;
                enregistrerSousToolStripMenuItem.Visible = false;
                modeTestToolStripMenuItem.Visible = false;
                propriétésToolStripMenuItem.Visible = false;



                //afficher mode editon , menu principal et vues
                fichierToolStripMenuItem.Visible = true;
                modeEditionToolStripMenuItem.Visible = true;
                menuPrincipalToolStripMenuItem.Visible = true;
                vuesToolStripMenuItem.Visible = true;

                splitContainer1.Hide();
                //panel score
                // splitContainer1.Panel1.Hide();
                //splitContainer1.Panel2.Hide();

                panel2.Hide();

            }
            //si mode edition , afficher les menus a cotés + barre des menus
            else
            {
                if (estEnModePartie) { FonctionsNatives.initialiserScene(); }

                panel1.Location = new Point(ancienPosX, ancienPosY);

                this.Text = "Mode Edition";
                this.changerMode(Etats.SELECTION);

                estEnModePartie = false;
                estEnModeTest = false;

                estEnPause = false;

                //retirer les maillets
                FonctionsNatives.retirerMailletEtRondelle();
                //afficher les points de controle
                FonctionsNatives.afficherPointControle();

                toolStrip1.Show();
                menuStrip1.Show();
                //afficher les boutons
                fichierToolStripMenuItem.Visible = true;
                éditionToolStripMenuItem.Visible = true;
                outilsToolStripMenuItemPoints.Visible = true;
                informationsToolStripMenuItem.Visible = true;
                vuesToolStripMenuItem.Visible = true;

                ouvrirToolStripMenuItem.Visible = true;
                nouveauToolStripMenuItem.Visible = true;
                enregistrerToolStripMenuItem.Visible = true;
                enregistrerSousToolStripMenuItem.Visible = true;
                modeTestToolStripMenuItem.Visible = true;
                propriétésToolStripMenuItem.Visible = true;


                //masquer le bouton mode edition
                modeEditionToolStripMenuItem.Visible = false;

                //panel score afficher - panel proprietes desactiver
                splitContainer1.Show();

                panel2.Hide();

            }
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn public void afficherBarreMenu()
        ///
        /// @brief permet d'afficher/ masquer la barre de menu selon le mode edition/test  
        ///
        /// @param[in] rien
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void afficherBarreMenu()
        { //En mode Test, si on clique sur Echapp
            if (estEnModeTest == true || estEnModePartie == true)
            {
                if (menuStrip1.Visible == false)
                {    //si le menu est masqué, on l'Affiche + pause
                    estEnPause = true;
                    menuStrip1.Show();
                }
                else
                {     //si non le masque et on retourne dans le jeu
                    estEnPause = false;
                    menuStrip1.Hide();
                }
            }
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn public void modeEditionToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// @brief afficher la fenetre d'edition
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void modeEditionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //afficher fenetre edition
            passerModeTest(false);
            //Permet de retirer les maillets et la rondelle dans la table
            //FonctionsNatives.retirerMailletEtRondelle();
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn public void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        ///
        /// @brief afficher la fenetre de Test
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void modeTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //afficher fenetre test 
            passerModeTest(true);
            //Permet d'ajouter les maillets et la rondelle dans la table
            //FonctionsNatives.ajouterMailletEtRondelle();
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn public void passerModePartie(bool mode)
        ///
        /// @brief permet de faire le passage au mode partie rapide
        /// @param[in] mode: bool qui determine le mode 
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void passerModePartie(bool mode)
        {
            //si mode jeu , masquer les menus a cotés + barre des menus
            if (mode == true)
            {
                this.Text = "Partie Rapide";

                panel1.Location = new Point(0, 0);
                panel1.Dock = DockStyle.Fill;

                estEnModePartie = true;
                estEnModeTest = false;
               
                this.changerMode(Etats.TEST);

                //Permet d'ajouter les maillets et la rondelle dans la table
                FonctionsNatives.ajouterMailletEtRondelle();
                //effacer les points de controle
                FonctionsNatives.effacerPointControle();

                estEnPause = false;


                toolStrip1.Hide();
                menuStrip1.Hide();

                //masquer les boutons
                éditionToolStripMenuItem.Visible = false;
                outilsToolStripMenuItemPoints.Visible = false;
                informationsToolStripMenuItem.Visible = false;
                ouvrirToolStripMenuItem.Visible = false;
                nouveauToolStripMenuItem.Visible = false;
                enregistrerToolStripMenuItem.Visible = false;
                enregistrerSousToolStripMenuItem.Visible = false;
                modeTestToolStripMenuItem.Visible = false;
                propriétésToolStripMenuItem.Visible = false;
                modeEditionToolStripMenuItem.Visible = false;


                //afficher mode editon , menu principal et vues
                fichierToolStripMenuItem.Visible = true;

                menuPrincipalToolStripMenuItem.Visible = true;
                vuesToolStripMenuItem.Visible = true;

                //panel parametres
                splitContainer1.Hide();

                //score
                panel2.Show();

            }

        }
        ///////////////////////////////////////////////////////////////////////
        /// @fn public void DemarerJoueurVirtuel(double vitesse, double probabilite)
        /// Author : Ali
        /// @brief permet d'activer le joueur virtuel
        ///param[in]
        ///         double vitesse : la vitesse du maillet virtuel 
        //          double probabilite : probabilite d'etre passif (rien faire ) entre 0 et 1
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void DemarerJoueurVirtuel(double vitesse, double probabilite)
        {
            Console.WriteLine("+++ Joueur Virtuel Active' +++");
            FonctionsNatives.setjoueurVirtuel(true);
            // on passe la vitesse
            FonctionsNatives.setVitesseVirtuel(vitesse);
            // on passe la probabilite
            FonctionsNatives.setProbabiliteVirtuel(probabilite);
        }
        ///////////////////////////////////////////////////////////////////////
        /// @fn public void DemarerJoueurVirtuel()
        /// Author : Ali
        /// @brief permet de deactiver le joueur virtuel
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void ArreterJoueurVirtuel()
        {
            Console.WriteLine("--- Joueur Virtuel Desactive' ---");
            FonctionsNatives.setjoueurVirtuel(false);
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn public void DemarrerPartie()
        /// Author : Ali
        /// @brief permet de demarer une partie du jeu
        /// 
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void DemarrerPartie()
        {
            if (FonctionsNatives.estButDroite())
            {
                //MessageBox.Show("Player 2 SCORES !","AirHockey", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                nbButsJoueur2++;
                textBox4.Text = nbButsJoueur2.ToString();
                FonctionsNatives.setButDroite(false);
                FonctionsNatives.reinitialiserPartieCourante();
                //Console.WriteLine("But Droite !!");
            }
            if (FonctionsNatives.estButGauche())
            {
                //MessageBox.Show("Player 1 SCORES !", "AirHockey" , MessageBoxButtons.OK, MessageBoxIcon.Information);
                nbButsJoueur1++;
                textBox5.Text = nbButsJoueur1.ToString();
                FonctionsNatives.setButGauche(false);
                FonctionsNatives.reinitialiserPartieCourante();
                //Console.WriteLine("But Gauche !!");
            }

            int nbButsMax = Program.configuration.nbButMax;
            //int  nbButsMax = FonctionsNatives.getNombreButs();
            if ((nbButsJoueur1 == nbButsMax) || (nbButsJoueur2 == nbButsMax))
            {
                DialogResult dialog = MessageBox.Show("La partie est finie, vous voulez rejouer encore ? ",
                        "Rejouer ou revenir au menu principal", MessageBoxButtons.YesNo);
                 
                if (dialog == DialogResult.Yes)
                {
                    nbButsJoueur1 = 0;
                    nbButsJoueur2 = 0;
                    textBox4.Text = "0"; textBox5.Text = "0";
                    FonctionsNatives.reinitialiserPartieCourante();

                }

                else if (dialog == DialogResult.No) //revenir menu principal
                {
                    estEnModePartie = false;
                    this.Hide();
                    menuPrincipal_.Show();
                    FonctionsNatives.reinitialiserPartieCourante();
                }
            }

            /* if (nbButsJoueur1 == nbButsMax)
             {
                 MessageBox.Show("** Congratulations! Player 1 wins ! **", "AirHockey", MessageBoxButtons.OK, MessageBoxIcon.Hand,
                 MessageBoxDefaultButton.Button1, MessageBoxOptions.ServiceNotification);
             }
             else
             {
                 MessageBox.Show("** Congratulations! Player 2 wins ! **", "AirHockey", MessageBoxButtons.OK, MessageBoxIcon.Information,
                 MessageBoxDefaultButton.Button1, MessageBoxOptions.ServiceNotification);¸*/

            //menuPrincipal_.Show();
            //this.Hide();

        }

        private void Edition_Load(object sender, EventArgs e)
        {
            resetPartie();
        }



        ///////////////////////////////////////////////////////////////////////
        /// @fn public void resetPartie()
        /// Author : Ali
        /// @brief permet de reinitialiser les scores quand
        /// une partie est termine ou on quite la partie
        /// 
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void resetPartie()
        {
            nbButsJoueur1 = 0;
            nbButsJoueur2 = 0;
            FonctionsNatives.setButDroite(false);
            FonctionsNatives.setButGauche(false);
            textBox4.Text = "0";
            textBox5.Text = "0";
        }


        //////////////////////////////////////////////////////////////////////////////////////////
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
        public static extern bool clickCurrent(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void clickEnd(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool positionSouris(int x, int y);

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
        
        // Redimensionnement de la fenêtre

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)] // pour utiliser une fonction qui se trouve dans le fichier Noyau.dll
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        /*
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)] // pour utiliser une fonction qui se trouve dans le fichier Noyau.dll
        public static extern void passerLargeur( int largeur);
        */

        // Sauvegarde et chargement de la zone de jeu

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void enregistrerZoneJeu(char[] fichierZoneJeu);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerZoneJeu(char[] fichierZoneJeu);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)] // pour utiliser une fonction qui se trouve dans le fichier Noyau.dll
        public static extern bool objetEstDansLaTable();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserScene();

        //wajdi
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajouterMailletEtRondelle();
        //wajdi
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void retirerMailletEtRondelle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerMailletAvecClavier(double x, double y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void reinitialiserPartieCourante();
        
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerMailletAvecSouris(double x, double y);

        // Ali
        // afficher ou effacer les points de controle
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void afficherPointControle();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void effacerPointControle();
        // joueur virtuel
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerJoueurVirtuel(double vitesse, double probabilite);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setjoueurVirtuel(bool activer);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getjoueurVirtuel();
        // vitesse joueur virtuel
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setVitesseVirtuel(double vitesse);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getVitesseVirtuel();
        // probabilite d'etre passif
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setProbabiliteVirtuel(double probabilite);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getProbabiliteVirtuel();
        // savoir s'il ya un but
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool estButDroite();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool estButGauche();
        // set la variable but -- pour reinialiser la partie
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setButDroite(bool etat);
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setButGauche(bool etat);
        // get/set le nb de buts pour gagner la partie
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getNombreButs();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setNombreButs(int nombre);
        // fonctions mode partie rapide
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool estPartieRapide();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setPartieRapide(bool activer);
        // fonctions rondelle en pause 
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerRondelle();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deactiverRondelle();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool estEnPauseRondelle();
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerLumieresActives(bool jLumiereAmbiente, bool kLumiereDirectionnelle, bool jLumiereSpots );
        //Ali

    }
}

