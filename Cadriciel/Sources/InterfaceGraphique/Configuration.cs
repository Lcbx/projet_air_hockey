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
        Profil joueurVirtuelDefault_ = new Profil();
        Profil joueurVirtuelCourant_;
        List<Profil> profils =new List<Profil>();
        private string nom_ = "";
        private double vitesse_ = 0;
        private double ProbDePassivite_ = 0;
        
        


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
            profils.Add(joueurVirtuelDefault_);
            joueurVirtuelCourant_ = joueurVirtuelDefault_;
            textBox1.Text=(joueurVirtuelCourant_.getNomProfil());
            textBox2.Text=(Convert.ToString(joueurVirtuelCourant_.getVitesseProfil()));
            textBox3.Text=(Convert.ToString(joueurVirtuelCourant_.getProbProfil()));
            listDeProfils.Items.Add(joueurVirtuelCourant_.getNomProfil());

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
            if (toucheDeplaceADroite_ == e.KeyValue)
            {
                toucheDeplaceADroite_ = toucheDeplaceAGauche_;
                this.droite.Text =this.gauche.Text;
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
            {
                debogageActif_ = true;
                console.Enabled = true;
                groupBox3.Enabled = true;
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

       
        private void ajouter_Click(object sender, EventArgs e)
        {
            creationProfil.Enabled = true;
            ajouterActif = true;
            

           
        }

        private void listDeProfils_SelectedIndexChanged(object sender, EventArgs e)
        {
            for (int i = 0; i < profils.Count; i++)
               
                if (i ==listDeProfils.SelectedIndex)
                {
                    joueurVirtuelCourant_ = profils[i];
                    nom_ = joueurVirtuelCourant_.getNomProfil();
                    vitesse_= joueurVirtuelCourant_.getVitesseProfil();
                    ProbDePassivite_= joueurVirtuelCourant_.getProbProfil();
                    textBox1.Text = (joueurVirtuelCourant_.getNomProfil());
                    textBox2.Text = (Convert.ToString(joueurVirtuelCourant_.getVitesseProfil()));
                    textBox3.Text = (Convert.ToString(joueurVirtuelCourant_.getProbProfil()));
                }
                    
        }

        private void modifierProfil_Click(object sender, EventArgs e)
        {
            creationProfil.Enabled = true;
            modifierActif = true;
          

        }

        private void button2_Click(object sender, EventArgs e)
        {
            for (int i = 1; i < profils.Count; i++)

                if (i == listDeProfils.SelectedIndex)
                {
                    profils.Remove(profils[i]);
                    listDeProfils.Items.Remove(textBox1.Text);
                    textBox1.Text = "";
                    textBox2.Text = "";
                    textBox3.Text = "";
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
                    textBox1.Text = "";
                    textBox2.Text = "";
                    textBox3.Text = "";
                    ajouterActif = false;
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
                        modifierActif = false;
                        listDeProfils.Items.RemoveAt(i);
                        listDeProfils.Items.Add(textBox1.Text);
                       
                    }
                creationProfil.Enabled = false;
            }

            }

        private void fermer3_Click(object sender, EventArgs e)
        {
            this.Hide();
            menuPrincipal_.Show();
        }

        private void Configuration_Load(object sender, EventArgs e)
        {
            this.Hide();
            menuPrincipal_.Show();
        }

        private void fermerDebogage_Click(object sender, EventArgs e)
        {
            this.Hide();
            menuPrincipal_.Show();
        }
    }
    static partial class FonctionsNatives
    {
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void touches(int toucheDeplacementAGauche_, int toucheDeplacementADroite_, int toucheDeplacementEnHaut_, int toucheDeplacementEnBas_);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void profilCourant(string nom, double vitesse_, double ProbDePassivite_);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void affichageDebog(bool debogageActif_, bool debogCollision_, bool debogVitesse_, bool eclairageActif_, bool effetVisuelActif);
    }
}
