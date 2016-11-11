namespace InterfaceGraphique
{
    partial class CreationTournoi
    {
        /// <summary> 
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur de composants

        /// <summary> 
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas 
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.title = new System.Windows.Forms.Label();
            this.createButton = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.cbmZoneDeJeu = new InterfaceGraphique.Tournoi.ZoneDeJeu();
            this.SuspendLayout();
            // 
            // title
            // 
            this.title.AutoSize = true;
            this.title.Enabled = false;
            this.title.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold);
            this.title.Location = new System.Drawing.Point(3, 0);
            this.title.Name = "title";
            this.title.Size = new System.Drawing.Size(213, 25);
            this.title.TabIndex = 9;
            this.title.Text = "Création d\'un tournoi";
            // 
            // createButton
            // 
            this.createButton.Location = new System.Drawing.Point(8, 54);
            this.createButton.Name = "createButton";
            this.createButton.Size = new System.Drawing.Size(150, 23);
            this.createButton.TabIndex = 10;
            this.createButton.Text = "Créer le tournoi";
            this.createButton.UseVisualStyleBackColor = true;
            this.createButton.Click += new System.EventHandler(this.creerTournoi);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // cbmZoneDeJeu
            // 
            this.cbmZoneDeJeu.AutoSize = true;
            this.cbmZoneDeJeu.Location = new System.Drawing.Point(8, 28);
            this.cbmZoneDeJeu.Name = "cbmZoneDeJeu";
            this.cbmZoneDeJeu.Size = new System.Drawing.Size(203, 24);
            this.cbmZoneDeJeu.TabIndex = 11;
            // 
            // CreationTournoi
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.cbmZoneDeJeu);
            this.Controls.Add(this.createButton);
            this.Controls.Add(this.title);
            this.Name = "CreationTournoi";
            this.Size = new System.Drawing.Size(219, 80);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label title;
        private System.Windows.Forms.Button createButton;
        private System.Windows.Forms.Timer timer1;
        private Tournoi.ZoneDeJeu cbmZoneDeJeu;
    }
}
