namespace InterfaceGraphique
{
    partial class MenuPrincipal
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MenuPrincipal));
            this.btnPartieRapide = new System.Windows.Forms.Button();
            this.btnTournoi = new System.Windows.Forms.Button();
            this.btnEditeur = new System.Windows.Forms.Button();
            this.btnConfiguration = new System.Windows.Forms.Button();
            this.btnQuitter = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnPartieRapide
            // 
            this.btnPartieRapide.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnPartieRapide.Image = ((System.Drawing.Image)(resources.GetObject("btnPartieRapide.Image")));
            this.btnPartieRapide.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnPartieRapide.Location = new System.Drawing.Point(175, 39);
            this.btnPartieRapide.Name = "btnPartieRapide";
            this.btnPartieRapide.Size = new System.Drawing.Size(250, 40);
            this.btnPartieRapide.TabIndex = 0;
            this.btnPartieRapide.Text = "Partie rapide";
            this.btnPartieRapide.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnPartieRapide.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnPartieRapide.UseVisualStyleBackColor = true;
            this.btnPartieRapide.Click += new System.EventHandler(this.partieRapide_Click);
            // 
            // btnTournoi
            // 
            this.btnTournoi.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnTournoi.Image = ((System.Drawing.Image)(resources.GetObject("btnTournoi.Image")));
            this.btnTournoi.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnTournoi.Location = new System.Drawing.Point(175, 85);
            this.btnTournoi.Name = "btnTournoi";
            this.btnTournoi.Size = new System.Drawing.Size(250, 40);
            this.btnTournoi.TabIndex = 1;
            this.btnTournoi.Text = "Tournoi";
            this.btnTournoi.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnTournoi.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnTournoi.UseVisualStyleBackColor = true;
            this.btnTournoi.Click += new System.EventHandler(this.modeTournoiClick);
            // 
            // btnEditeur
            // 
            this.btnEditeur.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnEditeur.Image = ((System.Drawing.Image)(resources.GetObject("btnEditeur.Image")));
            this.btnEditeur.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnEditeur.Location = new System.Drawing.Point(175, 131);
            this.btnEditeur.Margin = new System.Windows.Forms.Padding(3, 3, 3, 9);
            this.btnEditeur.Name = "btnEditeur";
            this.btnEditeur.Size = new System.Drawing.Size(250, 40);
            this.btnEditeur.TabIndex = 2;
            this.btnEditeur.Text = "Édition de table";
            this.btnEditeur.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnEditeur.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnEditeur.UseVisualStyleBackColor = true;
            this.btnEditeur.Click += new System.EventHandler(this.editeur_Click);
            // 
            // btnConfiguration
            // 
            this.btnConfiguration.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnConfiguration.Image = ((System.Drawing.Image)(resources.GetObject("btnConfiguration.Image")));
            this.btnConfiguration.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnConfiguration.Location = new System.Drawing.Point(175, 189);
            this.btnConfiguration.Margin = new System.Windows.Forms.Padding(3, 9, 3, 9);
            this.btnConfiguration.Name = "btnConfiguration";
            this.btnConfiguration.Size = new System.Drawing.Size(250, 40);
            this.btnConfiguration.TabIndex = 3;
            this.btnConfiguration.Text = "Configuration";
            this.btnConfiguration.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnConfiguration.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnConfiguration.UseVisualStyleBackColor = true;
            this.btnConfiguration.Click += new System.EventHandler(this.configuration_Click);
            // 
            // btnQuitter
            // 
            this.btnQuitter.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnQuitter.Image = ((System.Drawing.Image)(resources.GetObject("btnQuitter.Image")));
            this.btnQuitter.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnQuitter.Location = new System.Drawing.Point(175, 247);
            this.btnQuitter.Margin = new System.Windows.Forms.Padding(3, 9, 3, 3);
            this.btnQuitter.Name = "btnQuitter";
            this.btnQuitter.Size = new System.Drawing.Size(250, 40);
            this.btnQuitter.TabIndex = 4;
            this.btnQuitter.Text = "Quitter";
            this.btnQuitter.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnQuitter.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnQuitter.UseVisualStyleBackColor = true;
            this.btnQuitter.Click += new System.EventHandler(this.quitter_Click);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(249, 339);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(323, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Icons designed by Lucy G and Freepik and from Flaticon";
            // 
            // MenuPrincipal
            // 
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(584, 361);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnQuitter);
            this.Controls.Add(this.btnConfiguration);
            this.Controls.Add(this.btnEditeur);
            this.Controls.Add(this.btnTournoi);
            this.Controls.Add(this.btnPartieRapide);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Tahoma", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(600, 400);
            this.Name = "MenuPrincipal";
            this.Text = "Menu Principal";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnPartieRapide;
        private System.Windows.Forms.Button btnTournoi;
        private System.Windows.Forms.Button btnEditeur;
        private System.Windows.Forms.Button btnConfiguration;
        private System.Windows.Forms.Button btnQuitter;
        private System.Windows.Forms.Label label1;
    }
}