﻿namespace InterfaceGraphique
{
    partial class Sauvegarde
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Sauvegarde));
            this.bouttonSauvegarder = new System.Windows.Forms.Button();
            this.filename = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // bouttonSauvegarder
            // 
            this.bouttonSauvegarder.Location = new System.Drawing.Point(185, 223);
            this.bouttonSauvegarder.Name = "bouttonSauvegarder";
            this.bouttonSauvegarder.Size = new System.Drawing.Size(81, 30);
            this.bouttonSauvegarder.TabIndex = 0;
            this.bouttonSauvegarder.Text = "Sauvegarder";
            this.bouttonSauvegarder.UseVisualStyleBackColor = true;
            this.bouttonSauvegarder.Click += new System.EventHandler(this.button1_Click);
            // 
            // filename
            // 
            this.filename.Location = new System.Drawing.Point(12, 229);
            this.filename.Name = "filename";
            this.filename.Size = new System.Drawing.Size(117, 20);
            this.filename.TabIndex = 1;
            this.filename.TextChanged += new System.EventHandler(this.filename_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 213);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(78, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Nom du fichier:";
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(12, 12);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(254, 186);
            this.listBox1.TabIndex = 3;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(135, 232);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 17);
            this.label2.TabIndex = 5;
            this.label2.Text = ".xml";
            // 
            // Sauvegarde
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.filename);
            this.Controls.Add(this.bouttonSauvegarder);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Sauvegarde";
            this.Text = "Sauvegarde";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Sauvegarde_FormClosing);
            this.Load += new System.EventHandler(this.Sauvegarde_Load);
            this.Shown += new System.EventHandler(this.Sauvegarde_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bouttonSauvegarder;
        private System.Windows.Forms.TextBox filename;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label label2;
    }
}