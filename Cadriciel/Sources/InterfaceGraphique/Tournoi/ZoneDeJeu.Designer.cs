namespace InterfaceGraphique.Tournoi
{
    partial class ZoneDeJeu
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
            this.lblZoneDeJeu = new System.Windows.Forms.Label();
            this.cbmZonesDeJeu = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // lblZoneDeJeu
            // 
            this.lblZoneDeJeu.AutoSize = true;
            this.lblZoneDeJeu.Location = new System.Drawing.Point(3, 3);
            this.lblZoneDeJeu.Name = "lblZoneDeJeu";
            this.lblZoneDeJeu.Size = new System.Drawing.Size(70, 13);
            this.lblZoneDeJeu.TabIndex = 0;
            this.lblZoneDeJeu.Text = "Zone de jeu: ";
            // 
            // cbmZonesDeJeu
            // 
            this.cbmZonesDeJeu.FormattingEnabled = true;
            this.cbmZonesDeJeu.Location = new System.Drawing.Point(79, 0);
            this.cbmZonesDeJeu.Name = "cbmZonesDeJeu";
            this.cbmZonesDeJeu.Size = new System.Drawing.Size(121, 21);
            this.cbmZonesDeJeu.TabIndex = 1;
            // 
            // ZoneDeJeu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.cbmZonesDeJeu);
            this.Controls.Add(this.lblZoneDeJeu);
            this.Name = "ZoneDeJeu";
            this.Size = new System.Drawing.Size(203, 24);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblZoneDeJeu;
        private System.Windows.Forms.ComboBox cbmZonesDeJeu;
    }
}
