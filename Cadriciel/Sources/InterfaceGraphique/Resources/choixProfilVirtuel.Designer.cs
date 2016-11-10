namespace InterfaceGraphique.Resources
{
    partial class choixProfilVirtuel
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
            this.label2 = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.filename = new System.Windows.Forms.TextBox();
            this.bouttonSauvegarder = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(133, 228);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 17);
            this.label2.TabIndex = 8;
            this.label2.Text = ".xml";
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(15, 10);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(254, 186);
            this.listBox1.TabIndex = 7;
            // 
            // filename
            // 
            this.filename.Location = new System.Drawing.Point(15, 227);
            this.filename.Name = "filename";
            this.filename.ReadOnly = true;
            this.filename.Size = new System.Drawing.Size(112, 20);
            this.filename.TabIndex = 6;
            // 
            // bouttonSauvegarder
            // 
            this.bouttonSauvegarder.Location = new System.Drawing.Point(188, 221);
            this.bouttonSauvegarder.Name = "bouttonSauvegarder";
            this.bouttonSauvegarder.Size = new System.Drawing.Size(81, 30);
            this.bouttonSauvegarder.TabIndex = 5;
            this.bouttonSauvegarder.Text = "Charger";
            this.bouttonSauvegarder.UseVisualStyleBackColor = true;
            // 
            // choixProfilVirtuel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.filename);
            this.Controls.Add(this.bouttonSauvegarder);
            this.Name = "choixProfilVirtuel";
            this.Text = "choix du joueur Virtuel";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.TextBox filename;
        private System.Windows.Forms.Button bouttonSauvegarder;
    }
}