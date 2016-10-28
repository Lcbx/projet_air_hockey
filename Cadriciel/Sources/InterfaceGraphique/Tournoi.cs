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
    public partial class Tournoi : Form
    {
        /// <summary>
        /// Permet d'initialiser l'affichage du tournoi
        /// </summary>
        public Tournoi() {
            InitializeComponent();

            testTournoi();
        }

        /// <summary>
        /// TODO: Retirer pour la remise, n'est présent que pour le test
        /// </summary>
        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void testTournoi();
    }
}
