namespace InterfaceGraphique
{
    partial class Configuration
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Configuration));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.haut = new System.Windows.Forms.Button();
            this.bas = new System.Windows.Forms.Button();
            this.droite = new System.Windows.Forms.Button();
            this.gauche = new System.Windows.Forms.Button();
            this.réintialisation = new System.Windows.Forms.Button();
            this.appliquer = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.scoreGangant = new System.Windows.Forms.GroupBox();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.label7 = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.scorePourGagner = new System.Windows.Forms.Label();
            this.typeJoueur = new System.Windows.Forms.GroupBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.type = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.fermer = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.scoreGangant.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.typeJoueur.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            resources.ApplyResources(this.tabControl1, "tabControl1");
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.tabPage1.Controls.Add(this.groupBox1);
            resources.ApplyResources(this.tabPage1, "tabPage1");
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.haut);
            this.groupBox1.Controls.Add(this.bas);
            this.groupBox1.Controls.Add(this.droite);
            this.groupBox1.Controls.Add(this.gauche);
            this.groupBox1.Controls.Add(this.réintialisation);
            this.groupBox1.Controls.Add(this.appliquer);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            resources.ApplyResources(this.groupBox1, "groupBox1");
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.TabStop = false;
            // 
            // label6
            // 
            resources.ApplyResources(this.label6, "label6");
            this.label6.Name = "label6";
            // 
            // haut
            // 
            resources.ApplyResources(this.haut, "haut");
            this.haut.Name = "haut";
            this.haut.UseVisualStyleBackColor = true;
            this.haut.KeyDown += new System.Windows.Forms.KeyEventHandler(this.haut_KeyDown);
            // 
            // bas
            // 
            resources.ApplyResources(this.bas, "bas");
            this.bas.Name = "bas";
            this.bas.UseVisualStyleBackColor = true;
            this.bas.KeyDown += new System.Windows.Forms.KeyEventHandler(this.bas_KeyDown);
            // 
            // droite
            // 
            resources.ApplyResources(this.droite, "droite");
            this.droite.Name = "droite";
            this.droite.UseVisualStyleBackColor = true;
            this.droite.KeyDown += new System.Windows.Forms.KeyEventHandler(this.droite_KeyDown);
            // 
            // gauche
            // 
            resources.ApplyResources(this.gauche, "gauche");
            this.gauche.Name = "gauche";
            this.gauche.UseVisualStyleBackColor = true;
            this.gauche.KeyDown += new System.Windows.Forms.KeyEventHandler(this.gauche_KeyDown);
            // 
            // réintialisation
            // 
            resources.ApplyResources(this.réintialisation, "réintialisation");
            this.réintialisation.Name = "réintialisation";
            this.réintialisation.UseVisualStyleBackColor = true;
            this.réintialisation.Click += new System.EventHandler(this.renitialisation_Click);
            // 
            // appliquer
            // 
            resources.ApplyResources(this.appliquer, "appliquer");
            this.appliquer.Name = "appliquer";
            this.appliquer.UseVisualStyleBackColor = true;
            this.appliquer.Click += new System.EventHandler(this.appliquer_Click);
            // 
            // label5
            // 
            resources.ApplyResources(this.label5, "label5");
            this.label5.Name = "label5";
            // 
            // label4
            // 
            resources.ApplyResources(this.label4, "label4");
            this.label4.Name = "label4";
            // 
            // label3
            // 
            resources.ApplyResources(this.label3, "label3");
            this.label3.Name = "label3";
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.label2.Name = "label2";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.fermer);
            this.tabPage2.Controls.Add(this.typeJoueur);
            this.tabPage2.Controls.Add(this.scoreGangant);
            resources.ApplyResources(this.tabPage2, "tabPage2");
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // scoreGangant
            // 
            this.scoreGangant.Controls.Add(this.scorePourGagner);
            this.scoreGangant.Controls.Add(this.numericUpDown1);
            this.scoreGangant.Controls.Add(this.label7);
            resources.ApplyResources(this.scoreGangant, "scoreGangant");
            this.scoreGangant.Name = "scoreGangant";
            this.scoreGangant.TabStop = false;
            // 
            // tabPage3
            // 
            resources.ApplyResources(this.tabPage3, "tabPage3");
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // tabPage4
            // 
            resources.ApplyResources(this.tabPage4, "tabPage4");
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            resources.ApplyResources(this.label7, "label7");
            this.label7.Name = "label7";
            // 
            // numericUpDown1
            // 
            resources.ApplyResources(this.numericUpDown1, "numericUpDown1");
            this.numericUpDown1.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numericUpDown1.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // scorePourGagner
            // 
            resources.ApplyResources(this.scorePourGagner, "scorePourGagner");
            this.scorePourGagner.Name = "scorePourGagner";
            // 
            // typeJoueur
            // 
            this.typeJoueur.Controls.Add(this.label8);
            this.typeJoueur.Controls.Add(this.type);
            this.typeJoueur.Controls.Add(this.comboBox1);
            resources.ApplyResources(this.typeJoueur, "typeJoueur");
            this.typeJoueur.Name = "typeJoueur";
            this.typeJoueur.TabStop = false;
            // 
            // comboBox1
            // 
            this.comboBox1.Cursor = System.Windows.Forms.Cursors.Default;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            resources.GetString("comboBox1.Items")});
            resources.ApplyResources(this.comboBox1, "comboBox1");
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // type
            // 
            resources.ApplyResources(this.type, "type");
            this.type.Name = "type";
            // 
            // label8
            // 
            resources.ApplyResources(this.label8, "label8");
            this.label8.Name = "label8";
            // 
            // fermer
            // 
            resources.ApplyResources(this.fermer, "fermer");
            this.fermer.Name = "fermer";
            this.fermer.UseVisualStyleBackColor = true;
            this.fermer.Click += new System.EventHandler(this.fermer_Click);
            // 
            // Configuration
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabControl1);
            this.Name = "Configuration";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.scoreGangant.ResumeLayout(false);
            this.scoreGangant.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.typeJoueur.ResumeLayout(false);
            this.typeJoueur.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button réintialisation;
        private System.Windows.Forms.Button appliquer;
        private System.Windows.Forms.Button haut;
        private System.Windows.Forms.Button bas;
        private System.Windows.Forms.Button droite;
        private System.Windows.Forms.Button gauche;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox scoreGangant;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label scorePourGagner;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.GroupBox typeJoueur;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label type;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button fermer;
    }
}