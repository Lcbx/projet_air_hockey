
////////////////////////////////////////////////////////////////////////////////////
/// @file Configuration.cs
/// @author Medaoud Ikram
/// @date 2016-9-15
/// @version 1.0 
///
////////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;  
using System.Threading.Tasks;
using System.Windows.Forms;   
using System.Runtime.InteropServices;


namespace InterfaceGraphique
{    
    public partial class Configuration : Form                   
    { 
        private static MenuPrincipal menuPrincipal_;
        private static Edition edition_;

        //intilailser les touches du clavier par defaut
        public int toucheDeplaceAGauche_;
        public int toucheDeplaceEnBas_;
        public int toucheDeplaceADroite_;
        public int toucheDeplaceEnHaut_;

        //le nombre de buts nécessaires (entre 1 et 5) pour gagner une partie.
        public int nbButMax;

        public bool estHumain = false;    
        Profil joueurVirtuelDefault_ = new Profil();
        Profil joueurVirtuelCourant_;
        List<Profil> profils =new List<Profil>();
        
        //les attributs de Profil
        private double vitesse_ = 0;
        private string nom = "";
        private double probaDAgirPassivemnt = 0;


        // Volet débogage
        private bool debogageActif_ = false;
        private bool debogCollision_ = false;
        private bool debogVitesse_ = false;
        private bool eclairageActif_ = false;
        private bool effetVisuelActif_ = true;

        private bool modifierActif = false;
        private bool ajouterActif = false;


		/////////////////////////////////////////////////////////////////////////
        /// @fn public Configuration()
        /// 
        /// @brief Constructeur par defaut de la classe Configuration
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        //////////////////////////////////////////////////////////////////////////////////////////    
        public Configuration()
        {
            InitializeComponent();
            
            joueurVirtuelCourant_ = joueurVirtuelDefault_;
            profils.Add(joueurVirtuelCourant_);

            textBox1.Text=(joueurVirtuelCourant_.getNomProfil());
            numericUpDown2.Value = Convert.ToDecimal( (joueurVirtuelCourant_.getVitesseProfil()));
            numericUpDown3.Value = Convert.ToDecimal(joueurVirtuelCourant_.getProbProfil());
            listDeProfils.Items.Add(joueurVirtuelCourant_.getNomProfil());

            creationProfil.Enabled = false;

            vitesse_ = joueurVirtuelCourant_.getVitesseProfil();
            nom = joueurVirtuelCourant_.getNomProfil();
            probaDAgirPassivemnt = joueurVirtuelCourant_.getProbProfil();

            // Charge les touches du joueur 2
            int[] touches = new int[4];
            FonctionsNatives.obtenirTouches(touches);
            toucheDeplaceEnHaut_ = touches[0];
            toucheDeplaceADroite_ = touches[1];
            toucheDeplaceEnBas_ = touches[2];
            toucheDeplaceAGauche_ = touches[3];
            this.haut.Text = ((Keys)touches[0]).ToString();
            this.droite.Text = ((Keys)touches[1]).ToString();
            this.bas.Text = ((Keys)touches[2]).ToString();
            this.gauche.Text = ((Keys)touches[3]).ToString();

            // Charge les options (unsafe pour cause de pointeur)
            unsafe
            {
                // Options de jeu
                OptionsJeu* data = (OptionsJeu*)FonctionsNatives.obtenirOptionsJeu();
                
                numericUpDown1.Value = data->nbrBut;
                nbButMax = data->nbrBut;

                if (data->joueurTestEstHumain == true)
                {
                    comboBox1.Text = "Joueur humain";
                    estHumain = true;

                   
                }
                else
                {
                    comboBox1.Text = "Joueur virtuel";
                    estHumain = false;
                }

                // Options de debug
                OptionsDebug* optsDebug = (OptionsDebug*)FonctionsNatives.obtenirOptionsDebug();
                if(optsDebug->isDebugActif)
                {
                    debogageActif_ = true;
                    checkBox1.Checked = true;

                    if (optsDebug->showCollisionRondelle){
                        debogCollision_ = true;
                        checkBox2.Checked = true;}
                    else
                    {
                        debogCollision_ = false;
                        checkBox2.Checked = false; ;
                    }

                    if (optsDebug->showVitesseRondelle){
                            debogVitesse_ = true;
                            checkBox3.Checked = true;}
                    else
                    {
                        debogVitesse_ = false;
                        checkBox3.Checked = false;
                    }

                    if (optsDebug->showEclairage) {
                        eclairageActif_ = true;
                        checkBox4.Checked = true; }
                    else
                    {
                        eclairageActif_ = false;
                        checkBox4.Checked = false;
                    }

                    if (optsDebug->showAttractionPortail) {
                        effetVisuelActif_ = true;
                        checkBox5.Checked = true; }
                    else
                    {
                        effetVisuelActif_ = false;
                        checkBox5.Checked = true;
                    }

                    FonctionsNatives.debogConfig(debogageActif_, debogCollision_, debogVitesse_, eclairageActif_, effetVisuelActif_);
                }
                else
                {
                    debogageActif_ = false;
                    checkBox1.Checked = false;
                    FonctionsNatives.debogConfig(debogageActif_, debogCollision_, debogVitesse_, eclairageActif_, effetVisuelActif_);

                }

            }

            // Charge les profils
            int nbrChar = FonctionsNatives.obtenirNombreProfils();
            string temp = "";
            List<string> liste = new List<string>();
            int[] noms = new int[nbrChar];
            FonctionsNatives.obtenirListeProfils(noms);

            for (int i = 0; i < nbrChar; i++)
            {
                if ((char)noms[i] != '#' || (char)noms[i+1] != '?' || (char)noms[i+2] != '&') {
                    temp += (char)noms[i];
                }
                else {
                    liste.Add(temp);
                    i += 2;
                    temp = "";
                }
            }
            foreach (string st in liste)
               Console.WriteLine(st);
            

        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public setMenuPrincipalConfig(MenuPrincipal menuPrincipal)
        /// 
        /// @brief assigner l'instance menu principale dans menu configuration
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        public void setMenuPrincipalConfig(MenuPrincipal menuPrincipal, Edition edition)
        {
            menuPrincipal_ = menuPrincipal;
            edition_ = edition;
        }
                    
					
		/////////////////////////////////////////////////////////////////////////
        /// @fn public renitialisation_Click(object sender, EventArgs e)
        /// 
        /// @brief rénitialise les touches de jeu par défaut
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void renitialisation_Click(object sender, EventArgs e)
        {
            toucheDeplaceAGauche_ = (int)Keys.A;
            toucheDeplaceEnBas_ = (int)Keys.S;
            toucheDeplaceADroite_ = (int)Keys.D;
            toucheDeplaceEnHaut_ = (int)Keys.W;
            this.gauche.Text = "A";
            this.droite.Text = "D";
            this.bas.Text = "S";
            this.haut.Text = "W";
            FonctionsNatives.sauvegarderTouches(toucheDeplaceEnHaut_, toucheDeplaceADroite_, toucheDeplaceEnBas_, toucheDeplaceAGauche_);
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public appliquer_Click(object sender, EventArgs e)
        /// 
        /// @brief applique les changements de touches   
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void appliquer_Click(object sender, EventArgs e)
        {
            FonctionsNatives.sauvegarderTouches(toucheDeplaceEnHaut_, toucheDeplaceADroite_, toucheDeplaceEnBas_, toucheDeplaceAGauche_);
        }

		
		/////////////////////////////////////////////////////////////////////////
        /// @fn public  changerTouche(KeyEventArgs ke)
        /// 
        /// @brief cette fonction retourne le string d'une touche de clavier 
        /// 
        /// @param[in] la touche
        ///
        /// @return string
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private string changerTouche(KeyEventArgs ke)
            {
                KeysConverter kc = new KeysConverter();
                string keyChar = kc.ConvertToString(ke.KeyData);
                return keyChar;
            }


		/////////////////////////////////////////////////////////////////////////
        /// @fn public  void gauche_KeyDown(object sender, KeyEventArgs e)
        /// 
        /// @brief cette fonction assigne une touche de clavier au déplacement gauche du maillet 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void gauche_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceADroite_ == e.KeyValue)
            {
                toucheDeplaceADroite_ = toucheDeplaceAGauche_;
                this.droite.Text = this.gauche.Text;
                toucheDeplaceAGauche_ = e.KeyValue;
                this.gauche.Text = changerTouche(e);
            }
            if (toucheDeplaceEnHaut_ == e.KeyValue)
            {
                toucheDeplaceEnHaut_ = toucheDeplaceAGauche_;
                this.haut.Text = this.gauche.Text;
                toucheDeplaceAGauche_ = e.KeyValue;
                this.gauche.Text = changerTouche(e);
            }
            if (toucheDeplaceEnBas_ == e.KeyValue)
            {
                toucheDeplaceEnBas_ = toucheDeplaceAGauche_;
                this.bas.Text = this.gauche.Text;
                toucheDeplaceAGauche_ = e.KeyValue;
                this.gauche.Text = changerTouche(e);
            }

            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
            {
                toucheDeplaceAGauche_ = e.KeyValue;
                this.gauche.Text=changerTouche(e);
            }         
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public  void droite_KeyDown(object sender, KeyEventArgs e)
        /// 
        /// @brief cette fonction assigne une touche de clavier au déplacement droite du maillet 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void droite_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceAGauche_ == e.KeyValue)
            {
                toucheDeplaceAGauche_ = toucheDeplaceADroite_;
                this.gauche.Text = this.droite.Text;
                toucheDeplaceADroite_ = e.KeyValue;
                this.droite.Text = changerTouche(e);
            }
            if (toucheDeplaceEnHaut_ == e.KeyValue)
            {
                toucheDeplaceEnHaut_ = toucheDeplaceADroite_;
                this.haut.Text = this.droite.Text;
                toucheDeplaceADroite_ = e.KeyValue;
                this.droite.Text = changerTouche(e);
            }
            if (toucheDeplaceEnBas_ == e.KeyValue)
            {
                toucheDeplaceEnBas_ = toucheDeplaceADroite_;
                this.bas.Text = this.droite.Text;
                toucheDeplaceADroite_ = e.KeyValue;
                this.droite.Text = changerTouche(e);
            }
            if (toucheDeplaceAGauche_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
            {
                toucheDeplaceADroite_ = e.KeyValue;
                this.droite.Text = changerTouche(e);
            }
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public  void bas_KeyDown(object sender, KeyEventArgs e)
        /// 
        /// @brief cette fonction assigne une touche de clavier au déplacement en bas du maillet 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void bas_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceAGauche_ == e.KeyValue)
            {
                toucheDeplaceAGauche_ = toucheDeplaceEnBas_;
                this.gauche.Text = this.bas.Text;
                toucheDeplaceEnBas_ = e.KeyValue;
                this.bas.Text = changerTouche(e);
            }
            if (toucheDeplaceEnHaut_ == e.KeyValue)
            {
                toucheDeplaceEnHaut_ = toucheDeplaceEnBas_;
                this.haut.Text = this.bas.Text;
                toucheDeplaceEnBas_ = e.KeyValue;
                this.bas.Text = changerTouche(e);
            }
            if (toucheDeplaceADroite_ == e.KeyValue)
            {
                toucheDeplaceADroite_ = toucheDeplaceEnBas_;
                this.droite.Text = this.bas.Text;
                toucheDeplaceEnBas_ = e.KeyValue;
                this.bas.Text = changerTouche(e);
            }
            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceAGauche_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
            {
                    toucheDeplaceEnBas_ = e.KeyValue;
                    this.bas.Text = changerTouche(e);
            }
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public  void haut_KeyDown(object sender, KeyEventArgs e)
        /// 
        /// @brief cette fonction assigne une touche de clavier au déplacement en haut du maillet 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void haut_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceAGauche_ == e.KeyValue)
            {
                toucheDeplaceAGauche_ = toucheDeplaceEnHaut_;
                this.gauche.Text = this.haut.Text;
                toucheDeplaceEnHaut_ = e.KeyValue;
                this.haut.Text = changerTouche(e);
            }
            if (toucheDeplaceADroite_ == e.KeyValue)
            {
                toucheDeplaceADroite_ = toucheDeplaceEnHaut_;
                this.droite.Text = this.haut.Text;
                toucheDeplaceEnHaut_ = e.KeyValue;
                this.haut.Text = changerTouche(e);
            }
            if (toucheDeplaceEnBas_ == e.KeyValue)
            {
                toucheDeplaceEnBas_ = toucheDeplaceEnHaut_;
                this.bas.Text = this.haut.Text;
                toucheDeplaceEnHaut_ = e.KeyValue;
                this.haut.Text = changerTouche(e);
            }
            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceAGauche_ != e.KeyValue)
            {
                toucheDeplaceEnHaut_ = e.KeyValue;
                this.haut.Text = changerTouche(e);
            }
                
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public  void numericUpDown1_ValueChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction assigne une valeur pour le nombre de but nécessaire pour gagner une partie . Les valeurs sont entre 1 et 5
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDown1.Value >= 1 || numericUpDown1.Value <= 5)
            {
                nbButMax = Convert.ToInt32(numericUpDown1.Value);
            }

        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public  void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction indique c'est le type du joueur adversaire est humain ou virtuel;
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.Text.Equals("Joueur humain"))
            { 
                estHumain= true;
            }

            else if (comboBox1.Text.Equals("Joueur virtuel"))
            {
                estHumain = false;
            }
        }

       

		/////////////////////////////////////////////////////////////////////////
        /// @fn public void checkBox1_CheckedChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction assigne true ou false à l'affichage de débogage (l'interrupteur)
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                debogageActif_ = true;
                console.Enabled = true;
                groupBox3.Enabled = true;
            }
            else
            {
                debogageActif_ = false;
                console.Enabled = false;
                groupBox3.Enabled = false;

            }
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public void checkBox2_CheckedChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction assigne true ou false à l'affichage de débogage de collision
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
                debogCollision_ = true;
            else
                debogCollision_ = false;
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public void checkBox3_CheckedChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction assigne true ou false à l'affichage de débogage de la vitesse de la rondelle après une collision
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked)
                debogVitesse_ = true;
            else
                debogVitesse_ = false;

        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public void checkBox4_CheckedChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction assigne true ou false à l'affichage ou non de l'éclairage
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked)
                eclairageActif_ = true;
            else
                eclairageActif_ = false;
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public void checkBox5_CheckedChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction assigne true ou false à l'affichage ou non de la limite d'attraction du portail
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked)
                effetVisuelActif_ = true;
            else
                effetVisuelActif_ = false;
        }

       
		/////////////////////////////////////////////////////////////////////////
        /// @fn public void ajouter_Click(object sender, EventArgs e)
        /// 
        /// @brief cette fonction assigne true ou false à l'affichage ou non de la limite d'attraction du portail
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void ajouter_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
            numericUpDown2.ResetText();
            numericUpDown3.ResetText();

            creationProfil.Enabled = true;
            ajouterActif = true;
            modifierActif = false;

        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public void listDeProfils_SelectedIndexChanged(object sender, EventArgs e)
        /// 
        /// @brief cette fonction attribue le profil selectionné au profil courant 
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void listDeProfils_SelectedIndexChanged(object sender, EventArgs e)
        {

            for (int i = 1; i <listDeProfils.Items.Count; i++)
                if (i == listDeProfils.SelectedIndex)
                {
                    joueurVirtuelCourant_ = profils[i];
                    textBox1.Text = (joueurVirtuelCourant_.getNomProfil());
                  
                    numericUpDown2.Value = Convert.ToDecimal((joueurVirtuelCourant_.getVitesseProfil()));
                    numericUpDown3.Value = Convert.ToDecimal(joueurVirtuelCourant_.getProbProfil());
                }      
        }

		/////////////////////////////////////////////////////////////////////////
        /// @fn public void modifierProfil_Click(object sender, EventArgs e)
        /// 
        /// @brief cette fonction active le champs de création de profil pour la modification
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void modifierProfil_Click(object sender, EventArgs e)
        {
            creationProfil.Enabled = true;
            ajouterActif = false;
            modifierActif = true;
          

        }

		////////////////////////////////////////////////////////////////////////
        /// @fn public button2_Click(object sender, EventArgs e)
        /// 
        /// @brief cette fonction supprime un profil de la liste
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void button2_Click(object sender, EventArgs e)
        {
            for (int i = 1; i < profils.Count; i++)

                if ( i== listDeProfils.SelectedIndex)
                {
                    profils.Remove(profils[i]);
                    listDeProfils.Items.Remove(textBox1.Text);
                }
           
        }


		/////////////////////////////////////////////////////////////////////////
        /// @fn public void appliquer2_Click(object sender, EventArgs e)
        /// 
        /// @brief cette fonction applique l'ajout à la liste  et la modification d'un profil
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void appliquer2_Click(object sender, EventArgs e)
        {
            int v = Convert.ToInt32(numericUpDown2.Value);
            decimal prob = numericUpDown3.Value;
            float p = (float)prob;
            string nomP = textBox1.Text.ToString();
            Profil joueur = new Profil(nomP, v, p);
           

           if (ajouterActif)
           {
               if (!(listDeProfils.Items.Contains(textBox1.Text)))
               {
                    //wajdi - sauvegarder 
                    if (numericUpDown2.Text != "" && numericUpDown3.Text != "" )
                    {

                        profils.Add(joueur);
                        listDeProfils.Items.Add(nomP);

                        //initiliaser 
                        textBox1.Clear();
                        numericUpDown2.ResetText();
                        numericUpDown3.ResetText();
                        creationProfil.Enabled = false;

                        FonctionsNatives.sauvegarderProfil(nomP, v, p);
                    }
                    else
                    {
                        MessageBox.Show("Verifier les valeurs entrées", "erreur",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    } 
               }
           }

           if (modifierActif)
           {
               for (int i = 1; i < profils.Count; i++)

                   if (i==listDeProfils.SelectedIndex)
                   {
                       profils[i].setNomProfil(textBox1.Text);
                       profils[i].setVitesseProfil(Convert.ToDouble(numericUpDown2.Value));
                       profils[i].setProbProfil(Convert.ToDouble(numericUpDown3.Value));
                       listDeProfils.Items.RemoveAt(i);
                       listDeProfils.Items.Insert(i,textBox1.Text);
                       creationProfil.Enabled=false;
                   }
           }
        }


		/////////////////////////////////////////////////////////////////////////
        /// @fn private void Configuration_FormClosing(object sender, FormClosingEventArgs e)
        /// 
        /// @brief cette fonction gere l'event de fermeture 
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        private void Configuration_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
        }

        /// <summary>
        /// Sauvegarder nombre de buts max et le type de joueur
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Sauvegarder_Click(object sender, EventArgs e)
        {
            FonctionsNatives.sauvegarderTypeButMax(nbButMax, estHumain);
        }

        /// <summary>
        /// Sauvegarder les informations de debogage 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SauvegarderDebogage_Click(object sender, EventArgs e)
        {
            FonctionsNatives.debogConfig(debogageActif_, debogCollision_, debogVitesse_, eclairageActif_, effetVisuelActif_);
         }



    }

    [StructLayout(LayoutKind.Sequential)]
    public unsafe struct OptionsJeu
    {
        public int nbrBut;
        public bool joueurTestEstHumain;
    };

    [StructLayout(LayoutKind.Sequential)]
    public unsafe struct OptionsDebug
    {
        public bool isDebugActif;
        public bool showCollisionRondelle;
        public bool showVitesseRondelle;
        public bool showEclairage;
        public bool showAttractionPortail;
    };

    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void touches(int toucheDeplacementAGauche_, int toucheDeplacementADroite_, int toucheDeplacementEnHaut_, int toucheDeplacementEnBas_);

        // Configuration des touches
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarderTouches(int haut, int droite, int bas, int gauche);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obtenirTouches(int[] touches);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void profilCourant(string nom, double vitesse_, double probaDAgirPassivemnt);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void debogConfig(bool debogageActif_, bool debogCollision_, bool debogVitesse_, bool eclairageActif_,bool effetVisuelActif_);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarderTypeButMax(int nombreMax, bool estHumain);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr obtenirOptionsJeu();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr obtenirOptionsDebug();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarderProfil(string nom, double vitesse, double proba);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obtenirListeProfils(int[] noms);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreProfils();

    }

}
