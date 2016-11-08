
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

        //intilailser les touches du clavier par defaut
        public int toucheDeplaceAGauche_;
        public int toucheDeplaceEnBas_;
        public int toucheDeplaceADroite_;
        public int toucheDeplaceEnHaut_;

        //le nombre de buts nécessaires (entre 1 et 5) pour gagner une partie.
        private int nbButMax = 2 ;

        

        private bool estVirtuel = true;    
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
        public Configuration()
        {
            InitializeComponent();
            
            joueurVirtuelCourant_ = joueurVirtuelDefault_;
            profils.Add(joueurVirtuelCourant_);

            textBox1.Text=(joueurVirtuelCourant_.getNomProfil());
            textBox2.Text=(Convert.ToString(joueurVirtuelCourant_.getVitesseProfil()));
            textBox3.Text=(Convert.ToString(joueurVirtuelCourant_.getProbProfil()));
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

            
        }

        public void setMenuPrincipalConfig(MenuPrincipal menuPrincipal)
        {
            menuPrincipal_ = menuPrincipal;
        }
                    
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

        private void appliquer_Click(object sender, EventArgs e)
        {
            FonctionsNatives.sauvegarderTouches(toucheDeplaceEnHaut_, toucheDeplaceADroite_, toucheDeplaceEnBas_, toucheDeplaceAGauche_);
        }

        private string changerTouche(KeyEventArgs ke)
            {
                KeysConverter kc = new KeysConverter();
                string keyChar = kc.ConvertToString(ke.KeyData);
                return keyChar;
            }


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

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDown1.Value >= 1 || numericUpDown1.Value <= 5)
            {
                nbButMax = Convert.ToInt32(numericUpDown1.Value);
            }

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.Text.Equals("Joueur humain"))
            { 
                estVirtuel = false;
            }

            else if (comboBox1.Text.Equals("Joueur virtuel"))
            {
                estVirtuel = true;
            }
        }

       

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

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
                debogCollision_ = true;
            else
                debogCollision_ = false;
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked)
                debogVitesse_ = true;
            else
                debogVitesse_ = false;

        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked)
                eclairageActif_ = true;
            else
                eclairageActif_ = false;
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked)
                effetVisuelActif_ = true;
            else
                effetVisuelActif_ = false;
        }

       
        private void ajouter_Click(object sender, EventArgs e)
        {
            creationProfil.Enabled = true;
            ajouterActif = true;
            modifierActif = false;

        }

        private void listDeProfils_SelectedIndexChanged(object sender, EventArgs e)
        {

            for (int i = 1; i <listDeProfils.Items.Count; i++)
                if (i == listDeProfils.SelectedIndex)
                {
                    joueurVirtuelCourant_ = profils[i];
                    textBox1.Text = (joueurVirtuelCourant_.getNomProfil());
                    textBox2.Text = (Convert.ToString(joueurVirtuelCourant_.getVitesseProfil()));
                    textBox3.Text = (Convert.ToString(joueurVirtuelCourant_.getProbProfil()));
                }      
        }

        private void modifierProfil_Click(object sender, EventArgs e)
        {
            creationProfil.Enabled = true;
            ajouterActif = false;
            modifierActif = true;
          

        }

        private void button2_Click(object sender, EventArgs e)
        {
            for (int i = 1; i < profils.Count; i++)

                if ( i== listDeProfils.SelectedIndex)
                {
                    profils.Remove(profils[i]);
                    listDeProfils.Items.Remove(textBox1.Text);
                }
           
        }


        private void appliquer2_Click(object sender, EventArgs e)
        {
            double v = Convert.ToDouble(textBox2.Text);
            double p = Convert.ToDouble(textBox3.Text);
            Profil joueur = new Profil(textBox1.Text, v, p);


            if (ajouterActif)
            {
                
                if (!(listDeProfils.Items.Contains(textBox1.Text)))
                {
                    profils.Add(joueur);
                    listDeProfils.Items.Add(textBox1.Text);
                    creationProfil.Enabled = false;
                }
            }

            if (modifierActif)
            {
                for (int i = 1; i < profils.Count; i++)

                    if (i==listDeProfils.SelectedIndex)
                    {
                        profils[i].setNomProfil(textBox1.Text);
                        profils[i].setVitesseProfil(Convert.ToDouble(textBox2.Text));
                        profils[i].setProbProfil(Convert.ToDouble(textBox3.Text));
                        listDeProfils.Items.RemoveAt(i);
                        listDeProfils.Items.Insert(i,textBox1.Text);
                        creationProfil.Enabled=false;
                    }
               
            }

            }

       
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
            FonctionsNatives.sauvegarderTypeButMax(nbButMax, estVirtuel);
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
        public static extern void sauvegarderTypeButMax(int nombreMax, bool estVirtuel);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarderTypeButMax(bool collision, bool vitesse, bool eclairage, bool effetVisuel);


    }
}
