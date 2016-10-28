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
        private int toucheDeplaceAGauche_ = (int)Keys.A;
        private int toucheDeplaceEnBas_ = (int)Keys.S;
        private int toucheDeplaceADroite_ = (int)Keys.D;
        private int toucheDeplaceEnHaut_ = (int)Keys.W;

        //le nombre de buts nécessaires (entre 1 et 5) pour gagner une partie.
        private int scorePourGangner = 2;

        private bool estVirtuel = true;
        Profil joueurVirtuelCourant_;
        List<Profil> profils;

        // Volet débogage
        private bool debogageActif = false;
        private bool debogCollision_ = false;
        private bool debogVitesse_ = false;
        private bool eclairageActif_ = false;
        private bool effetVisuelActif_ = true;



        public Configuration()

        {
            InitializeComponent();
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
            this.gauche.Text = "a";
            this.droite.Text = "d";
            this.bas.Text = "s";
            this.haut.Text = "w";
        }

        private void appliquer_Click(object sender, EventArgs e)
        {
            this.Hide();
            menuPrincipal_.Show();
        }

      private string changerTouche(KeyEventArgs ke)
            {
                KeysConverter kc = new KeysConverter();
                string keyChar = kc.ConvertToString(ke.KeyData);
                return keyChar;
            }
        private void gauche_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
            {
                toucheDeplaceAGauche_ = e.KeyValue;
                this.gauche.Text=changerTouche(e);
            }         
        }

        private void droite_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceAGauche_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
            {
                toucheDeplaceADroite_ = e.KeyValue;
                this.droite.Text = changerTouche(e);
            }
        }

        private void bas_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceAGauche_ != e.KeyValue && toucheDeplaceEnHaut_ != e.KeyValue)
            {
                    toucheDeplaceEnBas_ = e.KeyValue;
                    this.bas.Text = changerTouche(e);
            }
        }

        private void haut_KeyDown(object sender, KeyEventArgs e)
        {
            if (toucheDeplaceADroite_ != e.KeyValue && toucheDeplaceEnBas_ != e.KeyValue && toucheDeplaceAGauche_ != e.KeyValue)
            {
                toucheDeplaceEnHaut_ = e.KeyValue;
                this.haut.Text = changerTouche(e);
            }
                
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDown1.Value <= 2 || numericUpDown1.Value <= 5)
                scorePourGangner = Convert.ToInt32(numericUpDown1.Value);

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (e.Equals("Joueur humain"))
                estVirtuel = false;
        }

        private void fermer_Click(object sender, EventArgs e)
        {
            this.Hide();
            menuPrincipal_.Show();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
                debogageActif = true;
            else
            {
                console.Enabled = false;
            
                groupBox3.Enabled = false;
            }

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked)
                debogCollision_ = true;
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked)
                debogVitesse_ = true;
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked)
                eclairageActif_ = true;
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked)
                effetVisuelActif_ = true;
        }

       
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerMaillet(int toucheDeplacementAGauche_, int toucheDeplacementADroite_, int toucheDeplacementEnHaut_, int toucheDeplacementEnBas_);

        
    }
    }
