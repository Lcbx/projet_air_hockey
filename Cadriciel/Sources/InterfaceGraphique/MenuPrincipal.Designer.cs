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
            this.partieRapide = new System.Windows.Forms.Button();
            this.tournoi = new System.Windows.Forms.Button();
            this.configuration = new System.Windows.Forms.Button();
            this.editeur = new System.Windows.Forms.Button();
            this.quitter = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // partieRapide
            // 
            this.partieRapide.Cursor = System.Windows.Forms.Cursors.Hand;
            this.partieRapide.FlatAppearance.BorderColor = System.Drawing.Color.Blue;
            this.partieRapide.FlatAppearance.BorderSize = 3;
            this.partieRapide.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.partieRapide.Font = new System.Drawing.Font("Elephant", 16.125F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.partieRapide.Image = global::InterfaceGraphique.Properties.Resources.Partie_rapide;
            this.partieRapide.Location = new System.Drawing.Point(338, 27);
            this.partieRapide.Margin = new System.Windows.Forms.Padding(9, 6, 9, 6);
            this.partieRapide.Name = "partieRapide";
            this.partieRapide.Size = new System.Drawing.Size(480, 60);
            this.partieRapide.TabIndex = 0;
            this.partieRapide.Text = "Partie rapide";
            this.partieRapide.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.partieRapide.UseVisualStyleBackColor = true;
            // 
            // tournoi
            // 
            this.tournoi.Cursor = System.Windows.Forms.Cursors.Hand;
            this.tournoi.FlatAppearance.BorderColor = System.Drawing.Color.Blue;
            this.tournoi.FlatAppearance.BorderSize = 3;
            this.tournoi.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.tournoi.ForeColor = System.Drawing.Color.SeaGreen;
            this.tournoi.Image = global::InterfaceGraphique.Properties.Resources.tournoi1;
            this.tournoi.Location = new System.Drawing.Point(338, 93);
            this.tournoi.Margin = new System.Windows.Forms.Padding(9, 6, 9, 6);
            this.tournoi.Name = "tournoi";
            this.tournoi.Size = new System.Drawing.Size(480, 60);
            this.tournoi.TabIndex = 1;
            this.tournoi.Text = "Tournoi";
            this.tournoi.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.tournoi.UseVisualStyleBackColor = true;
            // 
            // configuration
            // 
            this.configuration.Cursor = System.Windows.Forms.Cursors.Hand;
            this.configuration.FlatAppearance.BorderColor = System.Drawing.Color.Blue;
            this.configuration.FlatAppearance.BorderSize = 3;
            this.configuration.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.configuration.Image = global::InterfaceGraphique.Properties.Resources.setting;
            this.configuration.Location = new System.Drawing.Point(338, 159);
            this.configuration.Margin = new System.Windows.Forms.Padding(9, 6, 9, 6);
            this.configuration.Name = "configuration";
            this.configuration.Size = new System.Drawing.Size(480, 60);
            this.configuration.TabIndex = 2;
            this.configuration.Text = "Configuration";
            this.configuration.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.configuration.UseVisualStyleBackColor = true;
            this.configuration.Click += new System.EventHandler(this.configuration_Click);
            // 
            // editeur
            // 
            this.editeur.Cursor = System.Windows.Forms.Cursors.Hand;
            this.editeur.FlatAppearance.BorderColor = System.Drawing.Color.Blue;
            this.editeur.FlatAppearance.BorderSize = 3;
            this.editeur.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.editeur.Image = global::InterfaceGraphique.Properties.Resources.Éditeur;
            this.editeur.Location = new System.Drawing.Point(338, 225);
            this.editeur.Margin = new System.Windows.Forms.Padding(9, 6, 9, 6);
            this.editeur.Name = "editeur";
            this.editeur.Size = new System.Drawing.Size(480, 60);
            this.editeur.TabIndex = 3;
            this.editeur.Text = "Éditeur";
            this.editeur.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
            this.editeur.UseVisualStyleBackColor = true;
            this.editeur.Click += new System.EventHandler(this.editeur_Click);
            // 
            // quitter
            // 
            this.quitter.Cursor = System.Windows.Forms.Cursors.Hand;
            this.quitter.FlatAppearance.BorderColor = System.Drawing.Color.Blue;
            this.quitter.FlatAppearance.BorderSize = 3;
            this.quitter.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.quitter.Image = global::InterfaceGraphique.Properties.Resources.Exit;
            this.quitter.Location = new System.Drawing.Point(939, 597);
            this.quitter.Margin = new System.Windows.Forms.Padding(9, 6, 9, 6);
            this.quitter.Name = "quitter";
            this.quitter.Size = new System.Drawing.Size(217, 117);
            this.quitter.TabIndex = 4;
            this.quitter.Text = "Quitter";
            this.quitter.TextImageRelation = System.Windows.Forms.TextImageRelation.TextAboveImage;
            this.quitter.UseVisualStyleBackColor = true;
            this.quitter.Click += new System.EventHandler(this.quitter_Click);
            // 
            // MenuPrincipal
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(31F, 55F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1174, 729);
            this.Controls.Add(this.quitter);
            this.Controls.Add(this.editeur);
            this.Controls.Add(this.configuration);
            this.Controls.Add(this.tournoi);
            this.Controls.Add(this.partieRapide);
            this.Font = new System.Drawing.Font("Elephant", 16.125F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.SeaGreen;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(9, 6, 9, 6);
            this.Name = "MenuPrincipal";
            this.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.RightToLeftLayout = true;
            this.Text = "MenuPrincipal";
            this.ResumeLayout(false);

        }

        #endregion

      


        private System.Windows.Forms.Button partieRapide;
        private System.Windows.Forms.Button tournoi;
        private System.Windows.Forms.Button configuration;
        private System.Windows.Forms.Button editeur;
        private System.Windows.Forms.Button quitter;
    }
}