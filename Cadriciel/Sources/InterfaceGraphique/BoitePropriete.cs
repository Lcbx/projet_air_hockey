﻿using System;
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
    public partial class BoitePropriete : Form
    {
        public BoitePropriete()
        {
            InitializeComponent();
            this.ControlBox = false;
            this.MinimizeBox = false;
            this.MaximizeBox = false;
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void BoitePropriete_Load(object sender, EventArgs e)
        {

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            double x = Convert.ToDouble(textBox1.Text);
            double y = Convert.ToDouble(textBox2.Text);
            System.Console.WriteLine("mon x esti: "+ x);
            System.Console.WriteLine("mon y tbk: "+ y);
            FonctionsNatives.deplacerObjet(x,y);
        }
    }
}