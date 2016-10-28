using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    public partial class Chargement : Form
    {
        string[] files;

        Edition edition_;

       public bool estclique;
        ///////////////////////////////////////////////////////////////////////
        /// @fn public Chargement(Edition edition) 
        ///
        /// @brief constructeur 
        ///
        /// @param[in] edition
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public Chargement(Edition edition)        {
            InitializeComponent();
            this.MinimizeBox = false;
            this.MaximizeBox = false;

            this.edition_ = edition;

            estclique = false;
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void Sauvegarde_Load(object sender, EventArgs e)
        ///
        /// @brief permet de charger cette fenetre
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gerer l'evenement
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Sauvegarde_Load(object sender, EventArgs e)
        {
            if (!Directory.Exists(Edition.SAVE_FILEPATH))
                Directory.CreateDirectory(Edition.SAVE_FILEPATH);

            string[] loadFiles = Directory.GetFiles(Edition.SAVE_FILEPATH, "*.xml");

            files = loadFiles.Select(filepath => Path.GetFileNameWithoutExtension(filepath)).ToArray();

            listBox1.BeginUpdate();
            listBox1.Items.Clear();
            foreach(string file in files) {
                listBox1.Items.Add(file);
            }
            listBox1.EndUpdate();
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn   private void button1_Click(object sender, EventArgs e)
        ///
        /// @brief permet d'enregistrer la zone de jeu
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gerer l'evenement
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void button1_Click(object sender, EventArgs e) {
            if (filename.Text != "") {
                estclique = true;
                edition_.setCurrentFile(filename.Text);
                // Tentatives #1 et #2 de résoudre le crash 
                //byte[] bytes = System.Text.Encoding.Unicode.GetBytes(Path.Combine(Edition.SAVE_FILEPATH, filename.Text + ".xml") + '\0');
                //char[] file = System.Text.Encoding.Unicode.GetString(bytes).ToCharArray();

                char[] f = Path.Combine(Edition.SAVE_FILEPATH, filename.Text + ".xml").ToCharArray();
                char[] file = new char[f.Length + 1];
                for (int i = 0; i < f.Length; i++)
                    file[i] = f[i];
                file[f.Length] = '\0';
                FonctionsNatives.chargerZoneJeu(file);
                this.Hide();
            }
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        ///
        /// @brief afficher la liste de fichier 
        ///
        /// @param[in] sender: boutton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                filename.Text = files[listBox1.SelectedIndex];
            }
            catch (Exception)
            {
                filename.Text = "";
            }
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void Sauvegarde_FormClosing(object sender, FormClosingEventArgs e)
        ///
        /// @brief femer la boite de sauvegarde
        ///
        /// @param[in] sender: boutton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Sauvegarde_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }
    }
}
