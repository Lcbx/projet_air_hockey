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

        public Chargement(Edition edition)        {
            InitializeComponent();
            this.MinimizeBox = false;
            this.MaximizeBox = false;

            this.edition_ = edition;
        }

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

        private void button1_Click(object sender, EventArgs e) {
            if (filename.Text != "") {
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

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            filename.Text = files[listBox1.SelectedIndex];
        }

        private void Sauvegarde_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }
    }
}
