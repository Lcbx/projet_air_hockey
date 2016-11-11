namespace InterfaceGraphique
{
    partial class MatchJoueur
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
            this.nomJoueur = new System.Windows.Forms.Label();
            this.scoreJoueur = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // nomJoueur
            // 
            this.nomJoueur.AutoSize = true;
            this.nomJoueur.Dock = System.Windows.Forms.DockStyle.Right;
            this.nomJoueur.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nomJoueur.Location = new System.Drawing.Point(50, 0);
            this.nomJoueur.Margin = new System.Windows.Forms.Padding(0);
            this.nomJoueur.Name = "nomJoueur";
            this.nomJoueur.Size = new System.Drawing.Size(100, 20);
            this.nomJoueur.TabIndex = 0;
            this.nomJoueur.Text = "Nom joueur";
            // 
            // scoreJoueur
            // 
            this.scoreJoueur.AutoSize = true;
            this.scoreJoueur.BackColor = System.Drawing.Color.Black;
            this.scoreJoueur.Dock = System.Windows.Forms.DockStyle.Left;
            this.scoreJoueur.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.scoreJoueur.ForeColor = System.Drawing.Color.White;
            this.scoreJoueur.Location = new System.Drawing.Point(0, 0);
            this.scoreJoueur.Margin = new System.Windows.Forms.Padding(0);
            this.scoreJoueur.Name = "scoreJoueur";
            this.scoreJoueur.Padding = new System.Windows.Forms.Padding(2);
            this.scoreJoueur.Size = new System.Drawing.Size(23, 24);
            this.scoreJoueur.TabIndex = 1;
            this.scoreJoueur.Text = "0";
            // 
            // MatchJoueur
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.Controls.Add(this.scoreJoueur);
            this.Controls.Add(this.nomJoueur);
            this.Name = "MatchJoueur";
            this.Size = new System.Drawing.Size(150, 23);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label nomJoueur;
        private System.Windows.Forms.Label scoreJoueur;
    }
}
