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
        ///////////////////////////////////////////////////////////////////////
        /// @fn public boitePropriete()
        ///
        /// @brief constructeur 
        ///
        /// @param[in] rien
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        public BoitePropriete()
        {
            InitializeComponent();
            //this.ControlBox = false;
            this.MinimizeBox = false;
            this.MaximizeBox = false;
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn public void BoitePropriete_Load(object sender, EventArgs e)
        ///
        /// @brief charger la boite de propriete  
        ///
        /// @param[in] sender: boutton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void BoitePropriete_Load(object sender, EventArgs e) {
            numericUpDown1.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientFriction());
            numericUpDown2.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientRebond());
            numericUpDown3.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientAcceleration());
        }


        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void button1_Click(object sender, EventArgs e)
        ///
        /// @brief masquer cette fenetre 
        ///
        /// @param[in] sender: boutton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void button3_Click(object sender, EventArgs e)
        ///
        /// @brief assigner les valeurs 
        ///
        /// @param[in] sender: boutton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
        private void button3_Click(object sender, EventArgs e) {
            FonctionsNatives.setCoefficient(
                Convert.ToDouble(numericUpDown1.Value),
                Convert.ToDouble(numericUpDown2.Value),
                Convert.ToDouble(numericUpDown3.Value)
                );
            this.Hide();
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

        ///////////////////////////////////////////////////////////////////////
        /// @fn  private void BoitePropriete_FormClosing(object sender, FormClosingEventArgs e)
        ///
        /// @brief femer la boite de propriete
        ///
        /// @param[in] sender: boutton
        /// @param[in] e: evenement
        ///
        ///
        /// @return rien
        //
        //////////////////////////////////////////////////////////////////////////////////////////
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
