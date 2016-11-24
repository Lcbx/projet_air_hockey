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
            this.SuspendLayout();
            // 
            // btnPartieRapide
            // 
            this.btnPartieRapide.Location = new System.Drawing.Point(0, 0);
            this.btnPartieRapide.Name = "btnPartieRapide";
            this.btnPartieRapide.Size = new System.Drawing.Size(139, 23);
            this.btnPartieRapide.TabIndex = 0;
            this.btnPartieRapide.Text = "Partie rapide";
            this.btnPartieRapide.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnPartieRapide.UseVisualStyleBackColor = true;
            // 
            // btnTournoi
            // 
            this.btnTournoi.Location = new System.Drawing.Point(0, 29);
            this.btnTournoi.Name = "btnTournoi";
            this.btnTournoi.Size = new System.Drawing.Size(139, 23);
            this.btnTournoi.TabIndex = 1;
            this.btnTournoi.Text = "Tournoi";
            this.btnTournoi.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnTournoi.UseVisualStyleBackColor = true;
            // 
            // btnEditeur
            // 
            this.btnEditeur.Location = new System.Drawing.Point(0, 58);
            this.btnEditeur.Name = "btnEditeur";
            this.btnEditeur.Size = new System.Drawing.Size(139, 23);
            this.btnEditeur.TabIndex = 2;
            this.btnEditeur.Text = "Édition de table";
            this.btnEditeur.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnEditeur.UseVisualStyleBackColor = true;
            // 
            // btnConfiguration
            // 
            this.btnConfiguration.Location = new System.Drawing.Point(0, 87);
            this.btnConfiguration.Name = "btnConfiguration";
            this.btnConfiguration.Size = new System.Drawing.Size(139, 23);
            this.btnConfiguration.TabIndex = 3;
            this.btnConfiguration.Text = "Configuration";
            this.btnConfiguration.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnConfiguration.UseVisualStyleBackColor = true;
            // 
            // btnQuitter
            // 
            this.btnQuitter.Location = new System.Drawing.Point(0, 116);
            this.btnQuitter.Name = "btnQuitter";
            this.btnQuitter.Size = new System.Drawing.Size(139, 23);
            this.btnQuitter.TabIndex = 4;
            this.btnQuitter.Text = "Quitter";
            this.btnQuitter.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.btnQuitter.UseVisualStyleBackColor = true;
            // 
            // MenuPrincipal
            // 
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.btnQuitter);
            this.Controls.Add(this.btnConfiguration);
            this.Controls.Add(this.btnEditeur);
            this.Controls.Add(this.btnTournoi);
            this.Controls.Add(this.btnPartieRapide);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MenuPrincipal";
            this.Text = "Menu Principal";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnPartieRapide;
        private System.Windows.Forms.Button btnTournoi;
        private System.Windows.Forms.Button btnEditeur;
        private System.Windows.Forms.Button btnConfiguration;
        private System.Windows.Forms.Button btnQuitter;
    }
}