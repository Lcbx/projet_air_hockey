namespace InterfaceGraphique
{
    partial class FenetreProfilVirtuel
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
            this.chargerProfil = new System.Windows.Forms.Button();
            this.listDeProfils = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.profil = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // chargerProfil
            // 
            this.chargerProfil.Location = new System.Drawing.Point(177, 213);
            this.chargerProfil.Name = "chargerProfil";
            this.chargerProfil.Size = new System.Drawing.Size(95, 41);
            this.chargerProfil.TabIndex = 0;
            this.chargerProfil.Text = "Charger";
            this.chargerProfil.UseVisualStyleBackColor = true;
            this.chargerProfil.Click += new System.EventHandler(this.chargerProfil_Click);
            // 
            // listDeProfils
            // 
            this.listDeProfils.FormattingEnabled = true;
            this.listDeProfils.Location = new System.Drawing.Point(15, 12);
            this.listDeProfils.Name = "listDeProfils";
            this.listDeProfils.Size = new System.Drawing.Size(254, 186);
            this.listDeProfils.TabIndex = 7;
            this.listDeProfils.SelectedIndexChanged += new System.EventHandler(this.listDeProfils_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 213);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Profil Choisi";
            // 
            // profil
            // 
            this.profil.Location = new System.Drawing.Point(12, 229);
            this.profil.Name = "profil";
            this.profil.ReadOnly = true;
            this.profil.Size = new System.Drawing.Size(112, 20);
            this.profil.TabIndex = 5;
            // 
            // FenetreProfilVirtuel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.listDeProfils);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.profil);
            this.Controls.Add(this.chargerProfil);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FenetreProfilVirtuel";
            this.Text = "FenetreProfilVirtuel";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button chargerProfil;
        private System.Windows.Forms.ListBox listDeProfils;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox profil;
    }
}