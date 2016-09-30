namespace InterfaceGraphique
{
    partial class Edition
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

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Edition));
            this.panel1 = new System.Windows.Forms.Panel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.nouveauToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ouvrirToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.enregistrerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.enregistrerSousToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.propriétésToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.modeTestToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuPrincipalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.éditionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.supprimerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.outilsToolStripMenuItemPoints = new System.Windows.Forms.ToolStripMenuItem();
            this.sélectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.déplacementToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rotationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.miseÀLéchelleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.duplicationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.créationDobjetsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItemAccelerateur = new System.Windows.Forms.ToolStripMenuItem();
            this.portailToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.muretToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.zoomToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gestionDesPointsDeContrôleToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vuesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.informationsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aideToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButtonSelection = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonDeplacement = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonRotation = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonMiseAEchelle = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonDuplication = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonZoom = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox2 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButtonAccelerateur = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonPortail = new System.Windows.Forms.ToolStripButton();
            this.toolStripButtonMuret = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripTextBox3 = new System.Windows.Forms.ToolStripLabel();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Location = new System.Drawing.Point(72, 27);
            this.panel1.Margin = new System.Windows.Forms.Padding(6);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(638, 458);
            this.panel1.TabIndex = 0;
            this.panel1.TabStop = true;
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Edition_MouseMove);
            this.panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseUp);

            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.éditionToolStripMenuItem,
            this.outilsToolStripMenuItemPoints,
            this.vuesToolStripMenuItem,
            this.informationsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(3, 1, 0, 1);
            this.menuStrip1.Size = new System.Drawing.Size(710, 24);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nouveauToolStripMenuItem,
            this.ouvrirToolStripMenuItem,
            this.enregistrerToolStripMenuItem,
            this.enregistrerSousToolStripMenuItem,
            this.propriétésToolStripMenuItem,
            this.modeTestToolStripMenuItem,
            this.menuPrincipalToolStripMenuItem});
            this.fichierToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.Transparent;
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(54, 22);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // nouveauToolStripMenuItem
            // 
            this.nouveauToolStripMenuItem.Name = "nouveauToolStripMenuItem";
            this.nouveauToolStripMenuItem.Size = new System.Drawing.Size(197, 22);
            this.nouveauToolStripMenuItem.Text = "Nouveau";
            // 
            // ouvrirToolStripMenuItem
            // 
            this.ouvrirToolStripMenuItem.Name = "ouvrirToolStripMenuItem";
            this.ouvrirToolStripMenuItem.Size = new System.Drawing.Size(197, 22);
            this.ouvrirToolStripMenuItem.Text = "Ouvrir";
            // 
            // enregistrerToolStripMenuItem
            // 
            this.enregistrerToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("enregistrerToolStripMenuItem.Image")));
            this.enregistrerToolStripMenuItem.Name = "enregistrerToolStripMenuItem";
            this.enregistrerToolStripMenuItem.Size = new System.Drawing.Size(197, 22);
            this.enregistrerToolStripMenuItem.Text = "Enregistrer";
            // 
            // enregistrerSousToolStripMenuItem
            // 
            this.enregistrerSousToolStripMenuItem.Name = "enregistrerSousToolStripMenuItem";
            this.enregistrerSousToolStripMenuItem.Size = new System.Drawing.Size(197, 22);
            this.enregistrerSousToolStripMenuItem.Text = "Enregistrer sous";
            // 
            // propriétésToolStripMenuItem
            // 
            this.propriétésToolStripMenuItem.Name = "propriétésToolStripMenuItem";
            this.propriétésToolStripMenuItem.Size = new System.Drawing.Size(197, 22);
            this.propriétésToolStripMenuItem.Text = "Propriétés";
            this.propriétésToolStripMenuItem.Click += new System.EventHandler(this.propriétésToolStripMenuItem_Click);
            // 
            // modeTestToolStripMenuItem
            // 
            this.modeTestToolStripMenuItem.Name = "modeTestToolStripMenuItem";
            this.modeTestToolStripMenuItem.Size = new System.Drawing.Size(197, 22);
            this.modeTestToolStripMenuItem.Text = "Mode test";
            // 
            // menuPrincipalToolStripMenuItem
            // 
            this.menuPrincipalToolStripMenuItem.Name = "menuPrincipalToolStripMenuItem";
            this.menuPrincipalToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.menuPrincipalToolStripMenuItem.Size = new System.Drawing.Size(197, 22);
            this.menuPrincipalToolStripMenuItem.Text = "Menu principal";
            this.menuPrincipalToolStripMenuItem.Click += new System.EventHandler(this.menuPrincipalToolStripMenuItem_Click);
            // 
            // éditionToolStripMenuItem
            // 
            this.éditionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.supprimerToolStripMenuItem});
            this.éditionToolStripMenuItem.Name = "éditionToolStripMenuItem";
            this.éditionToolStripMenuItem.Size = new System.Drawing.Size(56, 22);
            this.éditionToolStripMenuItem.Text = "Édition";
            this.éditionToolStripMenuItem.Click += new System.EventHandler(this.éditionToolStripMenuItem_Click);
            // 
            // supprimerToolStripMenuItem
            // 
            this.supprimerToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("supprimerToolStripMenuItem.Image")));
            this.supprimerToolStripMenuItem.Name = "supprimerToolStripMenuItem";
            this.supprimerToolStripMenuItem.Size = new System.Drawing.Size(168, 38);
            this.supprimerToolStripMenuItem.Text = "Supprimer";
            this.supprimerToolStripMenuItem.Click += new System.EventHandler(this.supprimerToolStripMenuItem_Click);
            // 
            // outilsToolStripMenuItemPoints
            // 
            this.outilsToolStripMenuItemPoints.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sélectionToolStripMenuItem,
            this.déplacementToolStripMenuItem,
            this.rotationToolStripMenuItem,
            this.miseÀLéchelleToolStripMenuItem,
            this.duplicationToolStripMenuItem,
            this.créationDobjetsToolStripMenuItem,
            this.zoomToolStripMenuItem,
            this.gestionDesPointsDeContrôleToolStripMenuItem});
            this.outilsToolStripMenuItemPoints.Name = "outilsToolStripMenuItemPoints";
            this.outilsToolStripMenuItemPoints.Size = new System.Drawing.Size(50, 22);
            this.outilsToolStripMenuItemPoints.Text = "Outils";
            this.outilsToolStripMenuItemPoints.ToolTipText = "Gestion des points de contrôle";
            // 
            // sélectionToolStripMenuItem
            // 
            this.sélectionToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("sélectionToolStripMenuItem.Image")));
            this.sélectionToolStripMenuItem.Name = "sélectionToolStripMenuItem";
            this.sélectionToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.sélectionToolStripMenuItem.Text = "Sélection";
            // 
            // déplacementToolStripMenuItem
            // 
            this.déplacementToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("déplacementToolStripMenuItem.Image")));
            this.déplacementToolStripMenuItem.Name = "déplacementToolStripMenuItem";
            this.déplacementToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.déplacementToolStripMenuItem.Text = "Déplacement";
            // 
            // rotationToolStripMenuItem
            // 
            this.rotationToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("rotationToolStripMenuItem.Image")));
            this.rotationToolStripMenuItem.Name = "rotationToolStripMenuItem";
            this.rotationToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.rotationToolStripMenuItem.Text = "Rotation";
            // 
            // miseÀLéchelleToolStripMenuItem
            // 
            this.miseÀLéchelleToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("miseÀLéchelleToolStripMenuItem.Image")));
            this.miseÀLéchelleToolStripMenuItem.Name = "miseÀLéchelleToolStripMenuItem";
            this.miseÀLéchelleToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.miseÀLéchelleToolStripMenuItem.Text = "Mise à l\'échelle";
            // 
            // duplicationToolStripMenuItem
            // 
            this.duplicationToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("duplicationToolStripMenuItem.Image")));
            this.duplicationToolStripMenuItem.Name = "duplicationToolStripMenuItem";
            this.duplicationToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.duplicationToolStripMenuItem.Text = "Duplication";
            // 
            // créationDobjetsToolStripMenuItem
            // 
            this.créationDobjetsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItemAccelerateur,
            this.portailToolStripMenuItem,
            this.muretToolStripMenuItem});
            this.créationDobjetsToolStripMenuItem.Name = "créationDobjetsToolStripMenuItem";
            this.créationDobjetsToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.créationDobjetsToolStripMenuItem.Text = "Création d\'objets";
            // 
            // ToolStripMenuItemAccelerateur
            // 
            this.ToolStripMenuItemAccelerateur.CheckOnClick = true;
            this.ToolStripMenuItemAccelerateur.Image = ((System.Drawing.Image)(resources.GetObject("ToolStripMenuItemAccelerateur.Image")));
            this.ToolStripMenuItemAccelerateur.Name = "ToolStripMenuItemAccelerateur";
            this.ToolStripMenuItemAccelerateur.Size = new System.Drawing.Size(174, 22);
            this.ToolStripMenuItemAccelerateur.Text = "Bonus accélérateur";
            this.ToolStripMenuItemAccelerateur.ToolTipText = "Bonus accélérateur";
            // 
            // portailToolStripMenuItem
            // 
            this.portailToolStripMenuItem.Name = "portailToolStripMenuItem";
            this.portailToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.portailToolStripMenuItem.Text = "Portail";
            // 
            // muretToolStripMenuItem
            // 
            this.muretToolStripMenuItem.Name = "muretToolStripMenuItem";
            this.muretToolStripMenuItem.Size = new System.Drawing.Size(174, 22);
            this.muretToolStripMenuItem.Text = "Muret";
            // 
            // zoomToolStripMenuItem
            // 
            this.zoomToolStripMenuItem.Image = ((System.Drawing.Image)(resources.GetObject("zoomToolStripMenuItem.Image")));
            this.zoomToolStripMenuItem.Name = "zoomToolStripMenuItem";
            this.zoomToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.zoomToolStripMenuItem.Text = "Zoom";
            // 
            // gestionDesPointsDeContrôleToolStripMenuItem
            // 
            this.gestionDesPointsDeContrôleToolStripMenuItem.Name = "gestionDesPointsDeContrôleToolStripMenuItem";
            this.gestionDesPointsDeContrôleToolStripMenuItem.Size = new System.Drawing.Size(234, 22);
            this.gestionDesPointsDeContrôleToolStripMenuItem.Text = "Gestion des points de contrôle";
            // 
            // vuesToolStripMenuItem
            // 
            this.vuesToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueToolStripMenuItem,
            this.orbiteToolStripMenuItem});
            this.vuesToolStripMenuItem.Name = "vuesToolStripMenuItem";
            this.vuesToolStripMenuItem.Size = new System.Drawing.Size(44, 22);
            this.vuesToolStripMenuItem.Text = "Vues";
            // 
            // orthographiqueToolStripMenuItem
            // 
            this.orthographiqueToolStripMenuItem.Name = "orthographiqueToolStripMenuItem";
            this.orthographiqueToolStripMenuItem.Size = new System.Drawing.Size(159, 22);
            this.orthographiqueToolStripMenuItem.Text = "Orthographique";
            // 
            // orbiteToolStripMenuItem
            // 
            this.orbiteToolStripMenuItem.Name = "orbiteToolStripMenuItem";
            this.orbiteToolStripMenuItem.Size = new System.Drawing.Size(159, 22);
            this.orbiteToolStripMenuItem.Text = "Orbite";
            // 
            // informationsToolStripMenuItem
            // 
            this.informationsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aideToolStripMenuItem});
            this.informationsToolStripMenuItem.Name = "informationsToolStripMenuItem";
            this.informationsToolStripMenuItem.Size = new System.Drawing.Size(87, 22);
            this.informationsToolStripMenuItem.Text = "Informations";
            // 
            // aideToolStripMenuItem
            // 
            this.aideToolStripMenuItem.Name = "aideToolStripMenuItem";
            this.aideToolStripMenuItem.Size = new System.Drawing.Size(98, 22);
            this.aideToolStripMenuItem.Text = "Aide";
            // 
            // toolStrip1
            // 
            this.toolStrip1.AutoSize = false;
            this.toolStrip1.CanOverflow = false;
            this.toolStrip1.Dock = System.Windows.Forms.DockStyle.Left;
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(25, 25);
            this.toolStrip1.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripTextBox1,
            this.toolStripSeparator1,
            this.toolStripButtonSelection,
            this.toolStripButtonDeplacement,
            this.toolStripButtonRotation,
            this.toolStripButtonMiseAEchelle,
            this.toolStripButtonDuplication,
            this.toolStripButtonZoom,
            this.toolStripSeparator3,
            this.toolStripTextBox2,
            this.toolStripButtonAccelerateur,
            this.toolStripButtonPortail,
            this.toolStripButtonMuret,
            this.toolStripSeparator4,
            this.toolStripTextBox3,
            this.toolStripButton1});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Padding = new System.Windows.Forms.Padding(0);
            this.toolStrip1.Size = new System.Drawing.Size(54, 401);
            this.toolStrip1.TabIndex = 3;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(53, 15);
            this.toolStripTextBox1.Text = "Outils";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(53, 6);
            // 
            // toolStripButtonSelection
            // 
            this.toolStripButtonSelection.CheckOnClick = true;
            this.toolStripButtonSelection.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonSelection.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonSelection.Image")));
            this.toolStripButtonSelection.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonSelection.Name = "toolStripButtonSelection";
            this.toolStripButtonSelection.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonSelection.Text = "toolStripButtonSelection";
            this.toolStripButtonSelection.ToolTipText = "Sélection";
            this.toolStripButtonSelection.Click += new System.EventHandler(this.toolStripButtonSelection_Click);
            // 
            // toolStripButtonDeplacement
            // 
            this.toolStripButtonDeplacement.CheckOnClick = true;
            this.toolStripButtonDeplacement.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonDeplacement.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonDeplacement.Image")));
            this.toolStripButtonDeplacement.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonDeplacement.Name = "toolStripButtonDeplacement";
            this.toolStripButtonDeplacement.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonDeplacement.Text = "toolStripButtonDeplacement";
            this.toolStripButtonDeplacement.ToolTipText = "Déplacement";
            this.toolStripButtonDeplacement.Click += new System.EventHandler(this.toolStripButtonDeplacement_Click);
            // 
            // toolStripButtonRotation
            // 
            this.toolStripButtonRotation.CheckOnClick = true;
            this.toolStripButtonRotation.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonRotation.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonRotation.Image")));
            this.toolStripButtonRotation.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonRotation.Name = "toolStripButtonRotation";
            this.toolStripButtonRotation.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonRotation.Text = "toolStripButtonRotation";
            this.toolStripButtonRotation.ToolTipText = "Rotation";
            this.toolStripButtonRotation.Click += new System.EventHandler(this.toolStripButtonRotation_Click);
            // 
            // toolStripButtonMiseAEchelle
            // 
            this.toolStripButtonMiseAEchelle.CheckOnClick = true;
            this.toolStripButtonMiseAEchelle.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonMiseAEchelle.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonMiseAEchelle.Image")));
            this.toolStripButtonMiseAEchelle.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonMiseAEchelle.Name = "toolStripButtonMiseAEchelle";
            this.toolStripButtonMiseAEchelle.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonMiseAEchelle.Text = "toolStripButtonMiseAEchelle";
            this.toolStripButtonMiseAEchelle.ToolTipText = "Mise à échelle";
            this.toolStripButtonMiseAEchelle.Click += new System.EventHandler(this.toolStripButtonMiseAEchelle_Click);
            // 
            // toolStripButtonDuplication
            // 
            this.toolStripButtonDuplication.CheckOnClick = true;
            this.toolStripButtonDuplication.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonDuplication.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonDuplication.Image")));
            this.toolStripButtonDuplication.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonDuplication.Name = "toolStripButtonDuplication";
            this.toolStripButtonDuplication.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonDuplication.Text = "toolStripButtonDuplication";
            this.toolStripButtonDuplication.ToolTipText = "Duplication";
            this.toolStripButtonDuplication.Click += new System.EventHandler(this.toolStripButtonDuplication_Click);
            // 
            // toolStripButtonZoom
            // 
            this.toolStripButtonZoom.CheckOnClick = true;
            this.toolStripButtonZoom.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonZoom.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonZoom.Image")));
            this.toolStripButtonZoom.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonZoom.Name = "toolStripButtonZoom";
            this.toolStripButtonZoom.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonZoom.Text = "toolStripButtonZoom";
            this.toolStripButtonZoom.ToolTipText = "Zoom";
            this.toolStripButtonZoom.Click += new System.EventHandler(this.toolStripButtonZoom_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(53, 6);
            // 
            // toolStripTextBox2
            // 
            this.toolStripTextBox2.Name = "toolStripTextBox2";
            this.toolStripTextBox2.Size = new System.Drawing.Size(53, 15);
            this.toolStripTextBox2.Text = "Objets";
            // 
            // toolStripButtonAccelerateur
            // 
            this.toolStripButtonAccelerateur.CheckOnClick = true;
            this.toolStripButtonAccelerateur.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonAccelerateur.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonAccelerateur.Image")));
            this.toolStripButtonAccelerateur.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonAccelerateur.Name = "toolStripButtonAccelerateur";
            this.toolStripButtonAccelerateur.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonAccelerateur.Text = "toolStripButtonAccelerateur";
            this.toolStripButtonAccelerateur.ToolTipText = "Bonus Accelerateur";
            this.toolStripButtonAccelerateur.Click += new System.EventHandler(this.toolStripButtonAccelerateur_Click);
            // 
            // toolStripButtonPortail
            // 
            this.toolStripButtonPortail.CheckOnClick = true;
            this.toolStripButtonPortail.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonPortail.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonPortail.Image")));
            this.toolStripButtonPortail.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonPortail.Name = "toolStripButtonPortail";
            this.toolStripButtonPortail.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonPortail.Text = "toolStripButtonPortail";
            this.toolStripButtonPortail.ToolTipText = "Portail";
            this.toolStripButtonPortail.Click += new System.EventHandler(this.toolStripButtonPortail_Click);
            // 
            // toolStripButtonMuret
            // 
            this.toolStripButtonMuret.CheckOnClick = true;
            this.toolStripButtonMuret.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButtonMuret.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonMuret.Image")));
            this.toolStripButtonMuret.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonMuret.Name = "toolStripButtonMuret";
            this.toolStripButtonMuret.Size = new System.Drawing.Size(53, 29);
            this.toolStripButtonMuret.Text = "toolStripButtonMuret";
            this.toolStripButtonMuret.ToolTipText = "Muret";
            this.toolStripButtonMuret.Click += new System.EventHandler(this.toolStripButtonMuret_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(53, 6);
            // 
            // toolStripTextBox3
            // 
            this.toolStripTextBox3.Name = "toolStripTextBox3";
            this.toolStripTextBox3.Size = new System.Drawing.Size(53, 15);
            this.toolStripTextBox3.Text = "Contrôle";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.CheckOnClick = true;
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(53, 29);
            this.toolStripButton1.Text = "toolStripButtonControleDePoints";
            this.toolStripButton1.ToolTipText = "Gestion de Contrôle DePoints";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // Edition
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ClientSize = new System.Drawing.Size(710, 425);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Edition";
            this.Text = "Edition";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Exemple_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

            this.MouseWheel += new System.Windows.Forms.MouseEventHandler(Edition_MouseWheel);
        }
        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem nouveauToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ouvrirToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem enregistrerToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem enregistrerSousToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem propriétésToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem modeTestToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuPrincipalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem éditionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem outilsToolStripMenuItemPoints;
        private System.Windows.Forms.ToolStripMenuItem vuesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem informationsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem supprimerToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem sélectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem déplacementToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem rotationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem miseÀLéchelleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem duplicationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem créationDobjetsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItemAccelerateur;
        private System.Windows.Forms.ToolStripMenuItem portailToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem muretToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem zoomToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem gestionDesPointsDeContrôleToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orbiteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aideToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton toolStripButtonSelection;
        private System.Windows.Forms.ToolStripButton toolStripButtonDeplacement;
        private System.Windows.Forms.ToolStripButton toolStripButtonRotation;
        private System.Windows.Forms.ToolStripButton toolStripButtonMiseAEchelle;
        private System.Windows.Forms.ToolStripButton toolStripButtonDuplication;
        private System.Windows.Forms.ToolStripButton toolStripButtonAccelerateur;
        private System.Windows.Forms.ToolStripButton toolStripButtonPortail;
        private System.Windows.Forms.ToolStripButton toolStripButtonMuret;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripButton toolStripButtonZoom;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripLabel toolStripTextBox1;
        private System.Windows.Forms.ToolStripLabel toolStripTextBox2;
        private System.Windows.Forms.ToolStripLabel toolStripTextBox3;
    }
   
}

