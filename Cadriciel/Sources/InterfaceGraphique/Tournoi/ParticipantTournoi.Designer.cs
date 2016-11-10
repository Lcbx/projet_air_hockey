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
            this.isHuman = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // nameTextBox
            // 
            this.nameTextBox.Location = new System.Drawing.Point(0, 0);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(168, 20);
            this.nameTextBox.TabIndex = 1;
            this.nameTextBox.Text = "Nom joueur";
            this.nameTextBox.Enter += new System.EventHandler(this.nameTextBox_Enter);
            this.nameTextBox.Leave += new System.EventHandler(this.nameTextBox_Leave);
            // 
            // typeJoueurCBO
            // 
            this.typeJoueurCBO.FormattingEnabled = true;
            this.typeJoueurCBO.Location = new System.Drawing.Point(367, 0);
            this.typeJoueurCBO.Name = "typeJoueurCBO";
            this.typeJoueurCBO.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.typeJoueurCBO.Size = new System.Drawing.Size(168, 21);
            this.typeJoueurCBO.TabIndex = 3;
            // 
            // isHuman
            // 
            this.isHuman.AutoSize = true;
            this.isHuman.Location = new System.Drawing.Point(174, 2);
            this.isHuman.Name = "isHuman";
            this.isHuman.Size = new System.Drawing.Size(84, 17);
            this.isHuman.TabIndex = 2;
            this.isHuman.Text = "Est humain?";
            this.isHuman.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.isHuman.UseVisualStyleBackColor = true;
            this.isHuman.CheckedChanged += new System.EventHandler(this.isHuman_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(264, 3);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(97, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Type joueur virtuel:";
            // 
            // ParticipantTournoi
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.isHuman);
            this.Controls.Add(this.typeJoueurCBO);
            this.Controls.Add(this.nameTextBox);
            this.Name = "ParticipantTournoi";
            this.Size = new System.Drawing.Size(538, 24);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.ComboBox typeJoueurCBO;
        private System.Windows.Forms.CheckBox isHuman;
        private System.Windows.Forms.Label label1;
    }
}
