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
        string path;
        string lastSaveFile = "";
        static string DEFAULT_FILENAME = "defaut";

        public string getLastSaveFile() {
            return lastSaveFile;
        }

        public Sauvegarde()
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

            string[] saveFiles = Directory.GetFiles(path, "*.xml");

            files = saveFiles.Select(filepath => Path.GetFileNameWithoutExtension(filepath)).Where(x => x != DEFAULT_FILENAME).ToArray();

            listBox1.BeginUpdate();
            listBox1.Items.Clear();
            foreach(string file in files) {
                listBox1.Items.Add(file);
            }
            listBox1.EndUpdate();

            filename.Text = lastSaveFile;
        }

        private void button1_Click(object sender, EventArgs e) {
            lastSaveFile = filename.Text;
            this.saveLastFile();
            this.Hide();
        }

        public void saveLastFile() {
            if(lastSaveFile != "" && lastSaveFile != DEFAULT_FILENAME)
                FonctionsNatives.enregistrerZoneJeu(Path.Combine(path, lastSaveFile + ".xml").ToCharArray());
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

        private void filename_TextChanged(object sender, EventArgs e) {
            if(filename.Text == DEFAULT_FILENAME) {
                filename.ForeColor = Color.Red;
            } else {
                filename.ForeColor = Color.Black;
            }

        }
    }
}
