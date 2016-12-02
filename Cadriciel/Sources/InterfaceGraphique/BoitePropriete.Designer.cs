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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BoitePropriete));
            this.labelAccélération = new System.Windows.Forms.Label();
            this.labelRebond = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.labelFriction = new System.Windows.Forms.Label();
            this.txtAcceleration = new System.Windows.Forms.NumericUpDown();
            this.txtRebond = new System.Windows.Forms.NumericUpDown();
            this.txtFriction = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.txtAcceleration)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtRebond)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtFriction)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // labelAccélération
            // 
            this.labelAccélération.AutoSize = true;
            this.labelAccélération.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.labelAccélération.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.labelAccélération.Location = new System.Drawing.Point(15, 85);
            this.labelAccélération.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelAccélération.Name = "labelAccélération";
            this.labelAccélération.Size = new System.Drawing.Size(212, 15);
            this.labelAccélération.TabIndex = 6;
            this.labelAccélération.Text = "Accélération des bonus vitesse(m/s²): ";
            // 
            // labelRebond
            // 
            this.labelRebond.AutoSize = true;
            this.labelRebond.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.labelRebond.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.labelRebond.Location = new System.Drawing.Point(44, 60);
            this.labelRebond.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelRebond.Name = "labelRebond";
            this.labelRebond.Size = new System.Drawing.Size(183, 15);
            this.labelRebond.TabIndex = 5;
            this.labelRebond.Text = "Coefficient de rebond des murs: ";
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
            this.labelFriction.Location = new System.Drawing.Point(68, 35);
            this.labelFriction.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelFriction.Name = "labelFriction";
            this.labelFriction.Size = new System.Drawing.Size(159, 15);
            this.labelFriction.TabIndex = 3;
            this.labelFriction.Text = "Coefficient de friction du sol:";
            // 
            // txtAcceleration
            // 
            this.txtAcceleration.DecimalPlaces = 1;
            this.txtAcceleration.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.txtAcceleration.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.txtAcceleration.Location = new System.Drawing.Point(231, 83);
            this.txtAcceleration.Margin = new System.Windows.Forms.Padding(2);
            this.txtAcceleration.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.txtAcceleration.Name = "txtAcceleration";
            this.txtAcceleration.Size = new System.Drawing.Size(59, 21);
            this.txtAcceleration.TabIndex = 2;
            // 
            // txtRebond
            // 
            this.txtRebond.DecimalPlaces = 1;
            this.txtRebond.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.txtRebond.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.txtRebond.Location = new System.Drawing.Point(231, 58);
            this.txtRebond.Margin = new System.Windows.Forms.Padding(2);
            this.txtRebond.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.txtRebond.Name = "txtRebond";
            this.txtRebond.Size = new System.Drawing.Size(59, 21);
            this.txtRebond.TabIndex = 1;
            // 
            // txtFriction
            // 
            this.txtFriction.DecimalPlaces = 1;
            this.txtFriction.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F);
            this.txtFriction.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.txtFriction.Location = new System.Drawing.Point(231, 33);
            this.txtFriction.Margin = new System.Windows.Forms.Padding(2);
            this.txtFriction.Name = "txtFriction";
            this.txtFriction.Size = new System.Drawing.Size(59, 21);
            this.txtFriction.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtAcceleration);
            this.groupBox1.Controls.Add(this.labelFriction);
            this.groupBox1.Controls.Add(this.txtFriction);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.labelAccélération);
            this.groupBox1.Controls.Add(this.labelRebond);
            this.groupBox1.Controls.Add(this.txtRebond);
            this.groupBox1.Location = new System.Drawing.Point(78, 47);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(295, 127);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Propriétés";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(129, 194);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(98, 23);
            this.button2.TabIndex = 11;
            this.button2.Text = "Annuler";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(233, 194);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(98, 23);
            this.button3.TabIndex = 12;
            this.button3.Text = "Sauvegarder";
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
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "BoitePropriete";
            this.Text = "Propriétés de la table";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.BoitePropriete_FormClosing);
            this.Load += new System.EventHandler(this.BoitePropriete_Load);
            this.Shown += new System.EventHandler(this.BoitePropriete_Load);
            ((System.ComponentModel.ISupportInitialize)(this.txtAcceleration)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtRebond)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtFriction)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Label labelAccélération;
        private System.Windows.Forms.Label labelRebond;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelFriction;
        private System.Windows.Forms.NumericUpDown txtAcceleration;
        private System.Windows.Forms.NumericUpDown txtRebond;
        private System.Windows.Forms.NumericUpDown txtFriction;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
    }
}