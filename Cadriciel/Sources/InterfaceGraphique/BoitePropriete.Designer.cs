namespace InterfaceGraphique
{
    partial class BoitePropriete
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
            this.uniteAccelelration = new System.Windows.Forms.Label();
            this.labelAccélération = new System.Windows.Forms.Label();
            this.labelRebond = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.labelFriction = new System.Windows.Forms.Label();
            this.numericUpDown3 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // uniteAccelelration
            // 
            this.uniteAccelelration.AutoSize = true;
            this.uniteAccelelration.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.875F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.uniteAccelelration.Location = new System.Drawing.Point(12, 99);
            this.uniteAccelelration.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.uniteAccelelration.Name = "uniteAccelelration";
            this.uniteAccelelration.Size = new System.Drawing.Size(43, 13);
            this.uniteAccelelration.TabIndex = 7;
            this.uniteAccelelration.Text = "(m/s2  )";
            // 
            // labelAccélération
            // 
            this.labelAccélération.AutoSize = true;
            this.labelAccélération.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.labelAccélération.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.labelAccélération.Location = new System.Drawing.Point(12, 83);
            this.labelAccélération.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelAccélération.Name = "labelAccélération";
            this.labelAccélération.Size = new System.Drawing.Size(74, 15);
            this.labelAccélération.TabIndex = 6;
            this.labelAccélération.Text = "Accélération";
            // 
            // labelRebond
            // 
            this.labelRebond.AutoSize = true;
            this.labelRebond.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.labelRebond.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.labelRebond.Location = new System.Drawing.Point(12, 57);
            this.labelRebond.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelRebond.Name = "labelRebond";
            this.labelRebond.Size = new System.Drawing.Size(51, 15);
            this.labelRebond.TabIndex = 5;
            this.labelRebond.Text = "Rebond";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.label1.Location = new System.Drawing.Point(23, 53);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 13);
            this.label1.TabIndex = 4;
            // 
            // labelFriction
            // 
            this.labelFriction.AutoSize = true;
            this.labelFriction.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.labelFriction.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.labelFriction.Location = new System.Drawing.Point(12, 32);
            this.labelFriction.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelFriction.Name = "labelFriction";
            this.labelFriction.Size = new System.Drawing.Size(47, 15);
            this.labelFriction.TabIndex = 3;
            this.labelFriction.Text = "Friction";
            // 
            // numericUpDown3
            // 
            this.numericUpDown3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.numericUpDown3.Location = new System.Drawing.Point(85, 80);
            this.numericUpDown3.Margin = new System.Windows.Forms.Padding(2);
            this.numericUpDown3.Name = "numericUpDown3";
            this.numericUpDown3.Size = new System.Drawing.Size(60, 21);
            this.numericUpDown3.TabIndex = 2;
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.numericUpDown2.Location = new System.Drawing.Point(85, 53);
            this.numericUpDown2.Margin = new System.Windows.Forms.Padding(2);
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(60, 21);
            this.numericUpDown2.TabIndex = 1;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.numericUpDown1.Location = new System.Drawing.Point(85, 28);
            this.numericUpDown1.Margin = new System.Windows.Forms.Padding(2);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(60, 21);
            this.numericUpDown1.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.numericUpDown3);
            this.groupBox1.Controls.Add(this.uniteAccelelration);
            this.groupBox1.Controls.Add(this.labelFriction);
            this.groupBox1.Controls.Add(this.numericUpDown1);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.labelAccélération);
            this.groupBox1.Controls.Add(this.labelRebond);
            this.groupBox1.Controls.Add(this.numericUpDown2);
            this.groupBox1.Location = new System.Drawing.Point(147, 37);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(175, 155);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Configurations";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(129, 219);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 11;
            this.button2.Text = "Annuler";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(247, 219);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 12;
            this.button3.Text = "Modifier";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // BoitePropriete
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(476, 254);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.groupBox1);
            this.Name = "BoitePropriete";
            this.Text = "boitePropriete";
            this.Load += new System.EventHandler(this.BoitePropriete_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label uniteAccelelration;
        private System.Windows.Forms.Label labelAccélération;
        private System.Windows.Forms.Label labelRebond;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelFriction;
        private System.Windows.Forms.NumericUpDown numericUpDown3;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
    }
}