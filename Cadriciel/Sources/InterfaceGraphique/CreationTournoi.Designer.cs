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
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.participantTournoi4 = new InterfaceGraphique.ParticipantTournoi();
            this.participantTournoi3 = new InterfaceGraphique.ParticipantTournoi();
            this.participantTournoi2 = new InterfaceGraphique.ParticipantTournoi();
            this.participantTournoi1 = new InterfaceGraphique.ParticipantTournoi();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Enabled = false;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold);
            this.label1.Location = new System.Drawing.Point(232, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(213, 25);
            this.label1.TabIndex = 9;
            this.label1.Text = "Création d\'un tournoi";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(259, 137);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(150, 23);
            this.button1.TabIndex = 10;
            this.button1.Text = "Créer le tournoi";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // participantTournoi4
            // 
            this.participantTournoi4.Location = new System.Drawing.Point(181, 86);
            this.participantTournoi4.Name = "participantTournoi4";
            this.participantTournoi4.Size = new System.Drawing.Size(150, 45);
            this.participantTournoi4.TabIndex = 13;
            // 
            // participantTournoi3
            // 
            this.participantTournoi3.Location = new System.Drawing.Point(337, 86);
            this.participantTournoi3.Name = "participantTournoi3";
            this.participantTournoi3.Size = new System.Drawing.Size(150, 45);
            this.participantTournoi3.TabIndex = 12;
            // 
            // participantTournoi2
            // 
            this.participantTournoi2.Location = new System.Drawing.Point(337, 35);
            this.participantTournoi2.Name = "participantTournoi2";
            this.participantTournoi2.Size = new System.Drawing.Size(150, 45);
            this.participantTournoi2.TabIndex = 11;
            // 
            // participantTournoi1
            // 
            this.participantTournoi1.Location = new System.Drawing.Point(180, 35);
            this.participantTournoi1.Name = "participantTournoi1";
            this.participantTournoi1.Size = new System.Drawing.Size(150, 45);
            this.participantTournoi1.TabIndex = 0;
            // 
            // CreationTournoi
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.participantTournoi4);
            this.Controls.Add(this.participantTournoi3);
            this.Controls.Add(this.participantTournoi2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.participantTournoi1);
            this.Name = "CreationTournoi";
            this.Size = new System.Drawing.Size(630, 165);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private ParticipantTournoi participantTournoi1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private ParticipantTournoi participantTournoi2;
        private ParticipantTournoi participantTournoi3;
        private ParticipantTournoi participantTournoi4;
    }
}
