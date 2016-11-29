using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace InterfaceGraphique
{

    public partial class FenetreProfilVirtuel : Form
    {
        public Edition edition_;

        // Profil actuellement selectionne
        string nomJoueurVirtuelCourant_;
        // Liste des noms des profils
        List<string> nomsProfils = new List<string>();
        //les attributs de Profil
        private double vitesse_ = 0;
        private string nom = "";
        private double probabilite_ = 0;


        MenuPrincipal menu_;

        /////////////////////////////////////////////////////////////////////////
        /// @fn public FenetreProfilVirtuel(Edition edition)
        /// 
        /// @brief Constructeur par defaut de la classe FenetreProfilVirtuel
        /// 
        /// @param[in] aucun
        ///
        /// @return aucune
        //
        ////////////////////////////////////////////////////////////////////////////////////////// 
        public FenetreProfilVirtuel(Edition edition, MenuPrincipal menu)
        {
            InitializeComponent();
            edition_ = edition;
            menu_ = menu;
            // Chargement des profils

            int nbrChar = FonctionsNatives.obtenirNombreProfils();
            string temp = "";
            List<string> liste = new List<string>();
            int[] noms = new int[nbrChar];
            FonctionsNatives.obtenirListeProfils(noms);

            for (int i = 0; i < nbrChar; i++)
            {
                if ((char)noms[i] != '#' || (char)noms[i + 1] != '?' || (char)noms[i + 2] != '&')
                {
                    temp += (char)noms[i];
                }
                else
                {
                    liste.Add(temp);
                    i += 2;
                    temp = "";
                }
            }
            foreach (string st in liste)
            {
                nomsProfils.Add(st);
                listDeProfils.Items.Add(st);
            }

            nomJoueurVirtuelCourant_ = liste[0];

            //textBox1.Text = (nomJoueurVirtuelCourant_);

            char[] cNom = nomJoueurVirtuelCourant_.ToCharArray();
            char[] nt_cNom = new char[nomJoueurVirtuelCourant_.Length + 1];
            for (int i = 0; i < nomJoueurVirtuelCourant_.Length; i++)
                nt_cNom[i] = cNom[i];
            nt_cNom[nomJoueurVirtuelCourant_.Length] = '\0';

            //vitesse_ = (double) Convert.ToDecimal(FonctionsNatives.obtenirVitesseProfil(nt_cNom));
            //probaDAgirPassivemnt = (double) Convert.ToDecimal(FonctionsNatives.obtenirProbabiliteProfil(nt_cNom));

            //creationProfil.Enabled = false;

            vitesse_ = FonctionsNatives.obtenirVitesseProfil(nomJoueurVirtuelCourant_.ToCharArray());
            nom = nomJoueurVirtuelCourant_;
            probabilite_ = FonctionsNatives.obtenirProbabiliteProfil(nomJoueurVirtuelCourant_.ToCharArray());


        }


        private void chargerProfil_Click(object sender, EventArgs e)
        {
            Chargement zoneChar = new Chargement(edition_);
            this.Hide();
            zoneChar.ShowDialog();
            if (zoneChar.estclique == true)
            {
                edition_.Show();
                //edition_.BringToFront();
                
                edition_.passerModePartie(true);
                // demarer le joueur virtuel
                edition_.estjoueurvirtuel = true;

                // il faut passer les parametres du joueur virtuel ici
                // TODO recuper vitesse et prob du joueur 
                char[] cNom = nomJoueurVirtuelCourant_.ToCharArray();
                char[] nt_cNom = new char[nomJoueurVirtuelCourant_.Length + 1];
                for (int i = 0; i < nomJoueurVirtuelCourant_.Length; i++)
                    nt_cNom[i] = cNom[i];
                nt_cNom[nomJoueurVirtuelCourant_.Length] = '\0';




                // test afficher les vitesses et les probabilites a la console - yay! ca marche
                //vitesse_ = FonctionsNatives.obtenirVitesseProfil(nt_cNom);
                //probabilite_ = FonctionsNatives.obtenirProbabiliteProfil(nt_cNom);
                edition_.DemarerJoueurVirtuel(FonctionsNatives.obtenirVitesseProfil(nt_cNom), FonctionsNatives.obtenirProbabiliteProfil(nt_cNom));
                //edition_.DemarerJoueurVirtuel(1, 0.5);

                // Livrable 3 
                // changer le nom du joueur virtuelle courant
                FonctionsNatives.setNomJoueurCourant(nt_cNom, 2);
                edition_.resetPartie();

                menu_.Hide();
            }
        }

        private void listDeProfils_SelectedIndexChanged(object sender, EventArgs e)
        {

            if (listDeProfils.SelectedIndex >= 0)
            {
                nomJoueurVirtuelCourant_ = nomsProfils[listDeProfils.SelectedIndex];
                profil.Text = (nomJoueurVirtuelCourant_);

                char[] cNom = nomJoueurVirtuelCourant_.ToCharArray();
                char[] nt_cNom = new char[nomJoueurVirtuelCourant_.Length + 1];
                for (int i = 0; i < nomJoueurVirtuelCourant_.Length; i++)
                    nt_cNom[i] = cNom[i];
                nt_cNom[nomJoueurVirtuelCourant_.Length] = '\0';




                // test afficher les vitesses et les probabilites a la console - yay! ca marche
                vitesse_ = FonctionsNatives.obtenirVitesseProfil(nt_cNom);
                probabilite_ = FonctionsNatives.obtenirProbabiliteProfil(nt_cNom);
                
                //Console.WriteLine("vitesse = " + Convert.ToDecimal(vitesse_) + "prob = " + Convert.ToDecimal(probabilite_));
                
            }
        }
    }
}
