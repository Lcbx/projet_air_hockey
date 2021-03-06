﻿using System;
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
    public partial class Sauvegarde : Form
    {
        string[] files;

        private Edition edition_;

        public string Filename {
            get { return edition_.getCurrentFile(); }
            set { edition_.setCurrentFile(value); }
        }

        public bool WipeAfter = false;

        ///////////////////////////////////////////////////////////////////////
        /// @fn public Sauvegarde(Edition edition) 
        ///
        /// @brief constructeur 
        ///
        /// @param[in] edition
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public Sauvegarde(Edition edition)
        {
            InitializeComponent();
            this.MinimizeBox = false;
            this.MaximizeBox = false;
            this.TopMost = true;

            edition_ = edition;
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn public void Sauvegarde_Load(object sender, EventArgs e) 
        ///
        /// @brief loader cette fenetre 
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gere l'evenement
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void Sauvegarde_Load(object sender, EventArgs e)
        {

            if (!Directory.Exists(Edition.SAVE_FILEPATH))
                Directory.CreateDirectory(Edition.SAVE_FILEPATH);

            string[] saveFiles = Directory.GetFiles(Edition.SAVE_FILEPATH, "*.xml");

            files = saveFiles.Select(filepath => Path.GetFileNameWithoutExtension(filepath)).Where(x => x != Edition.DEFAULT_FILENAME).ToArray();

            listBox1.BeginUpdate();
            listBox1.Items.Clear();
            foreach(string file in files) {
                listBox1.Items.Add(file);
            }
            listBox1.EndUpdate();

            filename.Text = edition_.getCurrentFile();
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn   private void button1_Click(object sender, EventArgs e)
        ///
        /// @brief sauvegarder la zone 
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gere l'evenement
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void button1_Click(object sender, EventArgs e) {
            edition_.setCurrentFile(filename.Text);
            this.saveLastFile();

            if (WipeAfter) {
                FonctionsNatives.initialiserScene();
                this.Filename = "";
            }

            WipeAfter = false;

            this.Hide();
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn  public void saveLastFile()
        ///
        /// @brief sauvegarder le dernier dans fichier
        ///
        /// @param[in] rien
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public void saveLastFile() {
            if (edition_.getCurrentFile() != "")
            {

                char[] f = Path.Combine(Edition.SAVE_FILEPATH, edition_.getCurrentFile() + ".xml").ToCharArray();
                char[] file = new char[f.Length + 1];
                for (int i = 0; i < f.Length; i++)
                    file[i] = f[i];
                file[f.Length] = '\0';

                FonctionsNatives.enregistrerZoneJeu(file);
            }
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn   private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        ///
        /// @brief charger la liste
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gere l'evenement
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(listBox1.SelectedIndex >= 0)
                filename.Text = files[listBox1.SelectedIndex];
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void Sauvegarde_FormClosing(object sender, FormClosingEventArgs e)
        ///
        /// @brief fermer la fenetre
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gere l'evenement
        ///
        /// @return rien
        //
        /////////////////////////////////////////////////////////////////////////////////////////
        private void Sauvegarde_FormClosing(object sender, FormClosingEventArgs e)
        {
            WipeAfter = false;
            e.Cancel = true;
            this.Hide();
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void filename_TextChanged(object sender, EventArgs e)
        ///
        /// @brief verifier si le nom de ficher est change
        ///
        /// @param[in] sender: bouton
        /// @param[in] e: gere l'evenement
        ///
        /// @return rien
        //
        /////////////////////////////////////////////////////////////////////////////////////////
        private void filename_TextChanged(object sender, EventArgs e) {
            if(filename.Text == Edition.DEFAULT_FILENAME) {
                filename.ForeColor = Color.Red;
                bouttonSauvegarder.Enabled = false;
            } else
            {
                bouttonSauvegarder.Enabled = true;
                filename.ForeColor = Color.Black;
            }

        }
    }
}
