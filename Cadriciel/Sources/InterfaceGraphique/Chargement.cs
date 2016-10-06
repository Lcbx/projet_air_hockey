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
        string path;

        public Chargement()
        {

            InitializeComponent();
            this.MinimizeBox = false;
            this.MaximizeBox = false;
        }

        private void Sauvegarde_Load(object sender, EventArgs e)
        {
            path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "inf2990-10", "saves");
            if (!Directory.Exists(path))
                Directory.CreateDirectory(path);

            string[] loadFiles = Directory.GetFiles(path, "*.xml");

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
                FonctionsNatives.chargerZoneJeu(Path.Combine(path, filename.Text + ".xml").ToCharArray());
                this.Hide();
            } else {

            }
        }
        
        private void label1_Click(object sender, EventArgs e)
        {

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
