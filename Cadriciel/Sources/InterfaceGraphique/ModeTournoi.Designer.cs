namespace InterfaceGraphique
{
    partial class ModeTournoi
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
            this.button1 = new System.Windows.Forms.Button();
            this.creationTournoi1 = new InterfaceGraphique.CreationTournoi();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(161, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Revenir au menu principal";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // creationTournoi1
            // 
            this.creationTournoi1.AutoSize = true;
            this.creationTournoi1.Location = new System.Drawing.Point(12, 41);
            this.creationTournoi1.Name = "creationTournoi1";
            this.creationTournoi1.Size = new System.Drawing.Size(631, 168);
            this.creationTournoi1.TabIndex = 0;
            // 
            // ModeTournoi
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(654, 248);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.creationTournoi1);
            this.Name = "ModeTournoi";
            this.Text = "ModeTournoi";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private CreationTournoi creationTournoi1;
        private System.Windows.Forms.Button button1;
    }
}