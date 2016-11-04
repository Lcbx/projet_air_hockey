namespace InterfaceGraphique
{
    partial class ParticipantTournoi
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
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.typeJoueurCBO = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // nameTextBox
            // 
            this.nameTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.nameTextBox.Location = new System.Drawing.Point(0, 0);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(150, 20);
            this.nameTextBox.TabIndex = 0;
            this.nameTextBox.Text = "Nom joueur";
            this.nameTextBox.Enter += new System.EventHandler(this.nameTextBox_Enter);
            this.nameTextBox.Leave += new System.EventHandler(this.nameTextBox_Leave);
            // 
            // typeJoueurCBO
            // 
            this.typeJoueurCBO.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.typeJoueurCBO.FormattingEnabled = true;
            this.typeJoueurCBO.Location = new System.Drawing.Point(0, 24);
            this.typeJoueurCBO.Name = "typeJoueurCBO";
            this.typeJoueurCBO.Size = new System.Drawing.Size(150, 21);
            this.typeJoueurCBO.TabIndex = 1;
            this.typeJoueurCBO.Text = "Type joueur";
            // 
            // ParticipantTournoi
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.typeJoueurCBO);
            this.Controls.Add(this.nameTextBox);
            this.Name = "ParticipantTournoi";
            this.Size = new System.Drawing.Size(150, 45);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.ComboBox typeJoueurCBO;
    }
}
