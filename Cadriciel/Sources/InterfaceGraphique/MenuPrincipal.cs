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
    public partial class MenuPrincipal : Form
    {
        public MenuPrincipal()
        {
            InitializeComponent();
        }

        private void quitter_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void editeur_Click(object sender, EventArgs e)
        {
            Edition edition = new Edition();  // crée un objet de type Edition
            edition.Show();                   //  l'afficher 
            this.Hide();                      // fermer la fenêtre Menu principal.
        }
    }
}
