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
            this.fermer = new System.Windows.Forms.Button();
            this.typeJoueur = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.type = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.scoreGangant = new System.Windows.Forms.GroupBox();
            this.scorePourGagner = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.fermerDebogage = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.checkBox5 = new System.Windows.Forms.CheckBox();
            this.console = new System.Windows.Forms.GroupBox();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.creationProfil = new System.Windows.Forms.GroupBox();
            this.Proba = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.vitesse = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.nomProfil = new System.Windows.Forms.Label();
            this.listDeProfil = new System.Windows.Forms.GroupBox();
            this.listDeProfils = new System.Windows.Forms.ListBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.typeJoueur.SuspendLayout();
            this.scoreGangant.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.tabPage3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.console.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.creationProfil.SuspendLayout();
            this.listDeProfil.SuspendLayout();
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
            // fermer
            // 
            resources.ApplyResources(this.fermer, "fermer");
            this.fermer.Name = "fermer";
            this.fermer.UseVisualStyleBackColor = true;
            this.fermer.Click += new System.EventHandler(this.fermer_Click);
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
            // label8
            // 
            resources.ApplyResources(this.label8, "label8");
            this.label8.Name = "label8";
            // 
            // type
            // 
            resources.ApplyResources(this.type, "type");
            this.type.Name = "type";
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
            // scoreGangant
            // 
            this.scoreGangant.Controls.Add(this.scorePourGagner);
            this.scoreGangant.Controls.Add(this.numericUpDown1);
            this.scoreGangant.Controls.Add(this.label7);
            resources.ApplyResources(this.scoreGangant, "scoreGangant");
            this.scoreGangant.Name = "scoreGangant";
            this.scoreGangant.TabStop = false;
            // 
            // scorePourGagner
            // 
            resources.ApplyResources(this.scorePourGagner, "scorePourGagner");
            this.scorePourGagner.Name = "scorePourGagner";
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
            // label7
            // 
            resources.ApplyResources(this.label7, "label7");
            this.label7.Name = "label7";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.fermerDebogage);
            this.tabPage3.Controls.Add(this.groupBox2);
            resources.ApplyResources(this.tabPage3, "tabPage3");
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // fermerDebogage
            // 
            resources.ApplyResources(this.fermerDebogage, "fermerDebogage");
            this.fermerDebogage.Name = "fermerDebogage";
            this.fermerDebogage.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.console);
            this.groupBox2.Controls.Add(this.checkBox1);
            resources.ApplyResources(this.groupBox2, "groupBox2");
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.checkBox5);
            resources.ApplyResources(this.groupBox3, "groupBox3");
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.TabStop = false;
            // 
            // checkBox5
            // 
            resources.ApplyResources(this.checkBox5, "checkBox5");
            this.checkBox5.Name = "checkBox5";
            this.checkBox5.UseVisualStyleBackColor = true;
            this.checkBox5.CheckedChanged += new System.EventHandler(this.checkBox5_CheckedChanged);
            // 
            // console
            // 
            this.console.Controls.Add(this.checkBox4);
            this.console.Controls.Add(this.checkBox3);
            this.console.Controls.Add(this.checkBox2);
            resources.ApplyResources(this.console, "console");
            this.console.Name = "console";
            this.console.TabStop = false;
            // 
            // checkBox4
            // 
            resources.ApplyResources(this.checkBox4, "checkBox4");
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.UseVisualStyleBackColor = true;
            this.checkBox4.CheckedChanged += new System.EventHandler(this.checkBox4_CheckedChanged);
            // 
            // checkBox3
            // 
            resources.ApplyResources(this.checkBox3, "checkBox3");
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.UseVisualStyleBackColor = true;
            this.checkBox3.CheckedChanged += new System.EventHandler(this.checkBox3_CheckedChanged);
            // 
            // checkBox2
            // 
            resources.ApplyResources(this.checkBox2, "checkBox2");
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.UseVisualStyleBackColor = true;
            this.checkBox2.CheckedChanged += new System.EventHandler(this.checkBox2_CheckedChanged);
            // 
            // checkBox1
            // 
            resources.ApplyResources(this.checkBox1, "checkBox1");
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.creationProfil);
            this.tabPage4.Controls.Add(this.listDeProfil);
            resources.ApplyResources(this.tabPage4, "tabPage4");
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // creationProfil
            // 
            this.creationProfil.Controls.Add(this.Proba);
            this.creationProfil.Controls.Add(this.textBox3);
            this.creationProfil.Controls.Add(this.textBox2);
            this.creationProfil.Controls.Add(this.vitesse);
            this.creationProfil.Controls.Add(this.textBox1);
            this.creationProfil.Controls.Add(this.nomProfil);
            resources.ApplyResources(this.creationProfil, "creationProfil");
            this.creationProfil.Name = "creationProfil";
            this.creationProfil.TabStop = false;
            // 
            // Proba
            // 
            resources.ApplyResources(this.Proba, "Proba");
            this.Proba.Name = "Proba";
            // 
            // textBox3
            // 
            resources.ApplyResources(this.textBox3, "textBox3");
            this.textBox3.Name = "textBox3";
            // 
            // textBox2
            // 
            resources.ApplyResources(this.textBox2, "textBox2");
            this.textBox2.Name = "textBox2";
            // 
            // vitesse
            // 
            resources.ApplyResources(this.vitesse, "vitesse");
            this.vitesse.Name = "vitesse";
            // 
            // textBox1
            // 
            resources.ApplyResources(this.textBox1, "textBox1");
            this.textBox1.Name = "textBox1";
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // nomProfil
            // 
            resources.ApplyResources(this.nomProfil, "nomProfil");
            this.nomProfil.Name = "nomProfil";
            // 
            // listDeProfil
            // 
            this.listDeProfil.Controls.Add(this.listDeProfils);
            this.listDeProfil.Controls.Add(this.button2);
            this.listDeProfil.Controls.Add(this.button1);
            resources.ApplyResources(this.listDeProfil, "listDeProfil");
            this.listDeProfil.Name = "listDeProfil";
            this.listDeProfil.TabStop = false;
            // 
            // listDeProfils
            // 
            this.listDeProfils.FormattingEnabled = true;
            resources.ApplyResources(this.listDeProfils, "listDeProfils");
            this.listDeProfils.Items.AddRange(new object[] {
            resources.GetString("listDeProfils.Items")});
            this.listDeProfils.Name = "listDeProfils";
            this.listDeProfils.SelectedIndexChanged += new System.EventHandler(this.listDeProfils_SelectedIndexChanged);
            // 
            // button2
            // 
            resources.ApplyResources(this.button2, "button2");
            this.button2.Name = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            resources.ApplyResources(this.button1, "button1");
            this.button1.Name = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
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
            this.typeJoueur.ResumeLayout(false);
            this.typeJoueur.PerformLayout();
            this.scoreGangant.ResumeLayout(false);
            this.scoreGangant.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.tabPage3.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.console.ResumeLayout(false);
            this.console.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.creationProfil.ResumeLayout(false);
            this.creationProfil.PerformLayout();
            this.listDeProfil.ResumeLayout(false);
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
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox console;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Button fermerDebogage;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.CheckBox checkBox5;
        private System.Windows.Forms.CheckBox checkBox4;
        private System.Windows.Forms.CheckBox checkBox3;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.Label nomProfil;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox creationProfil;
        private System.Windows.Forms.GroupBox listDeProfil;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label vitesse;
        private System.Windows.Forms.Label Proba;
        public System.Windows.Forms.ListBox listDeProfils;
    }
}