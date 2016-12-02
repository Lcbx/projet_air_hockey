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

            ToolTip Friction = new ToolTip();
            Friction.ToolTipIcon = ToolTipIcon.Info;
            Friction.IsBalloon = true;
            Friction.ShowAlways = true;
            Friction.SetToolTip(labelFriction, "Plus le coefficient de friction est élevé, plus la rondelle décélère rapidement. Situé entre 0 et 100.");
            Friction.SetToolTip(txtFriction, "Plus le coefficient de friction est élevé, plus la rondelle décélère rapidement. Situé entre 0 et 100.");

            ToolTip Rebond = new ToolTip();
            Rebond.ToolTipIcon = ToolTipIcon.Info;
            Rebond.IsBalloon = true;
            Rebond.ShowAlways = true;
            Rebond.SetToolTip(labelRebond, "Plus le coefficient de rebond est élevé, plus la rondelle rebondit sur les murs et murets. Situé entre 0 et 1 où 1 conserve la vitesse et 0 arrête la rondelle.");
            Rebond.SetToolTip(txtRebond, "Plus le coefficient de rebond est élevé, plus la rondelle rebondit sur les murs et murets. Situé entre 0 et 1 où 1 conserve la vitesse et 0 arrête la rondelle.");

            ToolTip Acceleration = new ToolTip();
            Acceleration.ToolTipIcon = ToolTipIcon.Info;
            Acceleration.IsBalloon = true;
            Acceleration.ShowAlways = true;
            Acceleration.SetToolTip(labelAccélération, "Plus l'accélération est élevé, plus la rondelle est accélérée lorsqu'elle passe sur un bonus de vitesse. Situé entre 0,1 et 10m/(s*s)");
            Acceleration.SetToolTip(txtAcceleration, "Plus l'accélération est élevé, plus la rondelle est accélérée lorsqu'elle passe sur un bonus de vitesse. Situé entre 0,1 et 10m/(s*s)");
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
            txtFriction.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientFriction());
            txtRebond.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientRebond());
            txtAcceleration.Value = Convert.ToDecimal(FonctionsNatives.getCoefficientAcceleration());
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
                Convert.ToDouble(txtFriction.Value),
                Convert.ToDouble(txtRebond.Value),
                Convert.ToDouble(txtAcceleration.Value)
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
