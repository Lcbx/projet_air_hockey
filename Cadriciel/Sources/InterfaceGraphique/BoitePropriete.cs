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
    public partial class BoitePropriete : Form
    {
        public BoitePropriete()
        {
            InitializeComponent();
            //this.ControlBox = false;
            this.MinimizeBox = false;
            this.MaximizeBox = false;
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void BoitePropriete_Load(object sender, EventArgs e) {
            numericUpDown1.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientFriction());
            numericUpDown2.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientRebond());
            numericUpDown3.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientAcceleration());
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void button3_Click(object sender, EventArgs e) {
            FonctionsNatives.setCoefficient(
                Convert.ToDouble(numericUpDown1.Value),
                Convert.ToDouble(numericUpDown2.Value),
                Convert.ToDouble(numericUpDown3.Value)
                );
            this.Hide();
        }

        private void label7_Click(object sender, EventArgs e) {
           
        }

        /// <summary>
        /// Événement au clic du bouton annuler. Permet de remettre les 
        /// valeurs à la valeur précédente
        /// </summary>
        /// <param name="sender">Objet d'envois</param>
        /// <param name="e">Arguments d'événement</param>
        private void button2_Click(object sender, EventArgs e) {
            this.Hide();
        }

        private void BoitePropriete_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        static partial class FonctionsNatives
        {
            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern void setCoefficient(double friction, double rebond, double acceleration);

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern double getCoefficientFriction();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern double getCoefficientRebond();

            [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern double getCoefficientAcceleration();
        }
    }
}
