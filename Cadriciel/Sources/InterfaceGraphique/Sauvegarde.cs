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
    public partial class Sauvegarde : Form
    {
        string[] files;

        Edition edition_;

        public Sauvegarde(Edition edition)
        {
            InitializeComponent();
            this.MinimizeBox = false;
            this.MaximizeBox = false;

            edition_ = edition;
        }

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

        private void button1_Click(object sender, EventArgs e) {
            edition_.setCurrentFile(filename.Text);
            this.saveLastFile();
            this.Hide();
        }

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

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            filename.Text = files[listBox1.SelectedIndex];
        }

        private void Sauvegarde_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

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
