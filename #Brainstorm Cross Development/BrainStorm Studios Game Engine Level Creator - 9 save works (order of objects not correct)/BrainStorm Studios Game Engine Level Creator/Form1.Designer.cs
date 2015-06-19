namespace BrainStorm_Studios_Game_Engine_Level_Creator
{
    partial class Form1
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
            this.lblLevelName = new System.Windows.Forms.Label();
            this.tvObjects = new System.Windows.Forms.TreeView();
            this.btnSetNewObject = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.tbAnimationName = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.tbUserName = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.tbHeight = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.tbWidth = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.tbYCoordinate = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.tbXCoordinate = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.tbActionOverPlayer = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.tbTexturePath = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.tbBodyType = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tbScaleSize = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tbHasScript = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.tbBoundaryRight = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tbBoundaryUp = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.tbBoundaryDown = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.tbBoundaryLeft = new System.Windows.Forms.TextBox();
            this.btnUpdate = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panelGame = new BrainStorm_Studios_Game_Engine_Level_Creator.BSPanel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuNewLevel = new System.Windows.Forms.ToolStripMenuItem();
            this.menuLoadLevel = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSave = new System.Windows.Forms.ToolStripMenuItem();
            this.menuExit = new System.Windows.Forms.ToolStripMenuItem();
            this.richTextBoxLevel = new System.Windows.Forms.RichTextBox();
            this.tbLevelName = new System.Windows.Forms.TextBox();
            this.btnSave = new System.Windows.Forms.Button();
            this.pbSave = new System.Windows.Forms.PictureBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.lblLevelUpdated = new System.Windows.Forms.ToolStripStatusLabel();
            this.btnRemoveObject = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSave)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblLevelName
            // 
            this.lblLevelName.AutoSize = true;
            this.lblLevelName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLevelName.Location = new System.Drawing.Point(8, 38);
            this.lblLevelName.Name = "lblLevelName";
            this.lblLevelName.Size = new System.Drawing.Size(103, 20);
            this.lblLevelName.TabIndex = 3;
            this.lblLevelName.Text = "Level Name:";
            // 
            // tvObjects
            // 
            this.tvObjects.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tvObjects.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tvObjects.Location = new System.Drawing.Point(12, 155);
            this.tvObjects.Name = "tvObjects";
            this.tvObjects.Size = new System.Drawing.Size(270, 537);
            this.tvObjects.TabIndex = 4;
            this.tvObjects.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvObjects_AfterSelect);
            // 
            // btnSetNewObject
            // 
            this.btnSetNewObject.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnSetNewObject.BackColor = System.Drawing.Color.LightSteelBlue;
            this.btnSetNewObject.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSetNewObject.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSetNewObject.Location = new System.Drawing.Point(811, 952);
            this.btnSetNewObject.Name = "btnSetNewObject";
            this.btnSetNewObject.Size = new System.Drawing.Size(209, 45);
            this.btnSetNewObject.TabIndex = 5;
            this.btnSetNewObject.Text = "Set New Object";
            this.btnSetNewObject.UseVisualStyleBackColor = false;
            this.btnSetNewObject.Click += new System.EventHandler(this.btnNewObject_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(8, 132);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(112, 20);
            this.label1.TabIndex = 6;
            this.label1.Text = "Level Objects";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.White;
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.tbAnimationName);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.tbUserName);
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Controls.Add(this.tbHeight);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.tbWidth);
            this.groupBox1.Controls.Add(this.label15);
            this.groupBox1.Controls.Add(this.tbYCoordinate);
            this.groupBox1.Controls.Add(this.label16);
            this.groupBox1.Controls.Add(this.tbXCoordinate);
            this.groupBox1.Controls.Add(this.label17);
            this.groupBox1.Controls.Add(this.tbActionOverPlayer);
            this.groupBox1.Controls.Add(this.label18);
            this.groupBox1.Controls.Add(this.tbTexturePath);
            this.groupBox1.Controls.Add(this.label19);
            this.groupBox1.Controls.Add(this.tbBodyType);
            this.groupBox1.Location = new System.Drawing.Point(12, 708);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(577, 340);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Object Properties";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(29, 296);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(132, 20);
            this.label11.TabIndex = 38;
            this.label11.Text = "Animation Name";
            // 
            // tbAnimationName
            // 
            this.tbAnimationName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbAnimationName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbAnimationName.Location = new System.Drawing.Point(186, 294);
            this.tbAnimationName.Name = "tbAnimationName";
            this.tbAnimationName.Size = new System.Drawing.Size(361, 27);
            this.tbAnimationName.TabIndex = 37;
            this.tbAnimationName.Text = "textureAnimation";
            this.tbAnimationName.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(29, 263);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(89, 20);
            this.label12.TabIndex = 36;
            this.label12.Text = "UserName";
            // 
            // tbUserName
            // 
            this.tbUserName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbUserName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbUserName.Location = new System.Drawing.Point(186, 261);
            this.tbUserName.Name = "tbUserName";
            this.tbUserName.Size = new System.Drawing.Size(361, 27);
            this.tbUserName.TabIndex = 35;
            this.tbUserName.Text = "object";
            this.tbUserName.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(29, 230);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(58, 20);
            this.label13.TabIndex = 34;
            this.label13.Text = "Height";
            // 
            // tbHeight
            // 
            this.tbHeight.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbHeight.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbHeight.Location = new System.Drawing.Point(186, 228);
            this.tbHeight.Name = "tbHeight";
            this.tbHeight.Size = new System.Drawing.Size(361, 27);
            this.tbHeight.TabIndex = 33;
            this.tbHeight.Text = "1";
            this.tbHeight.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(29, 197);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(52, 20);
            this.label14.TabIndex = 32;
            this.label14.Text = "Width";
            // 
            // tbWidth
            // 
            this.tbWidth.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbWidth.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbWidth.Location = new System.Drawing.Point(186, 195);
            this.tbWidth.Name = "tbWidth";
            this.tbWidth.Size = new System.Drawing.Size(361, 27);
            this.tbWidth.TabIndex = 31;
            this.tbWidth.Text = "1";
            this.tbWidth.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label15.Location = new System.Drawing.Point(29, 164);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(105, 20);
            this.label15.TabIndex = 30;
            this.label15.Text = "Y Coordinate";
            // 
            // tbYCoordinate
            // 
            this.tbYCoordinate.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbYCoordinate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbYCoordinate.Location = new System.Drawing.Point(186, 162);
            this.tbYCoordinate.Name = "tbYCoordinate";
            this.tbYCoordinate.Size = new System.Drawing.Size(361, 27);
            this.tbYCoordinate.TabIndex = 29;
            this.tbYCoordinate.Text = "3";
            this.tbYCoordinate.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label16.Location = new System.Drawing.Point(29, 131);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(106, 20);
            this.label16.TabIndex = 28;
            this.label16.Text = "X Coordinate";
            // 
            // tbXCoordinate
            // 
            this.tbXCoordinate.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbXCoordinate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbXCoordinate.Location = new System.Drawing.Point(186, 129);
            this.tbXCoordinate.Name = "tbXCoordinate";
            this.tbXCoordinate.Size = new System.Drawing.Size(361, 27);
            this.tbXCoordinate.TabIndex = 27;
            this.tbXCoordinate.Text = "3";
            this.tbXCoordinate.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label17.Location = new System.Drawing.Point(29, 98);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(149, 20);
            this.label17.TabIndex = 26;
            this.label17.Text = "Action Over Player";
            // 
            // tbActionOverPlayer
            // 
            this.tbActionOverPlayer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbActionOverPlayer.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbActionOverPlayer.Location = new System.Drawing.Point(186, 96);
            this.tbActionOverPlayer.Name = "tbActionOverPlayer";
            this.tbActionOverPlayer.Size = new System.Drawing.Size(361, 27);
            this.tbActionOverPlayer.TabIndex = 25;
            this.tbActionOverPlayer.Text = "0";
            this.tbActionOverPlayer.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label18.Location = new System.Drawing.Point(29, 65);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(104, 20);
            this.label18.TabIndex = 24;
            this.label18.Text = "Texture Path";
            // 
            // tbTexturePath
            // 
            this.tbTexturePath.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbTexturePath.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbTexturePath.Location = new System.Drawing.Point(186, 63);
            this.tbTexturePath.Name = "tbTexturePath";
            this.tbTexturePath.Size = new System.Drawing.Size(361, 27);
            this.tbTexturePath.TabIndex = 23;
            this.tbTexturePath.Text = "Animations/texture.png";
            this.tbTexturePath.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label19.Location = new System.Drawing.Point(29, 32);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(88, 20);
            this.label19.TabIndex = 22;
            this.label19.Text = "Body Type";
            // 
            // tbBodyType
            // 
            this.tbBodyType.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbBodyType.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbBodyType.Location = new System.Drawing.Point(186, 30);
            this.tbBodyType.Name = "tbBodyType";
            this.tbBodyType.Size = new System.Drawing.Size(361, 27);
            this.tbBodyType.TabIndex = 21;
            this.tbBodyType.Text = "0";
            this.tbBodyType.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.White;
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.tbScaleSize);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.tbHasScript);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.tbBoundaryRight);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.tbBoundaryUp);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.tbBoundaryDown);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.tbBoundaryLeft);
            this.groupBox2.Location = new System.Drawing.Point(595, 708);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(425, 238);
            this.groupBox2.TabIndex = 39;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Level Properties";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(25, 201);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(84, 20);
            this.label2.TabIndex = 34;
            this.label2.Text = "ScaleSize";
            // 
            // tbScaleSize
            // 
            this.tbScaleSize.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbScaleSize.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbScaleSize.Location = new System.Drawing.Point(182, 199);
            this.tbScaleSize.Name = "tbScaleSize";
            this.tbScaleSize.Size = new System.Drawing.Size(210, 27);
            this.tbScaleSize.TabIndex = 33;
            this.tbScaleSize.Text = "32";
            this.tbScaleSize.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(25, 166);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(89, 20);
            this.label5.TabIndex = 32;
            this.label5.Text = "Has Script";
            // 
            // tbHasScript
            // 
            this.tbHasScript.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbHasScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbHasScript.Location = new System.Drawing.Point(182, 164);
            this.tbHasScript.Name = "tbHasScript";
            this.tbHasScript.Size = new System.Drawing.Size(210, 27);
            this.tbHasScript.TabIndex = 31;
            this.tbHasScript.Text = "0";
            this.tbHasScript.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(25, 133);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(124, 20);
            this.label6.TabIndex = 30;
            this.label6.Text = "Boundary Right";
            // 
            // tbBoundaryRight
            // 
            this.tbBoundaryRight.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbBoundaryRight.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbBoundaryRight.Location = new System.Drawing.Point(182, 131);
            this.tbBoundaryRight.Name = "tbBoundaryRight";
            this.tbBoundaryRight.Size = new System.Drawing.Size(210, 27);
            this.tbBoundaryRight.TabIndex = 29;
            this.tbBoundaryRight.Text = "30";
            this.tbBoundaryRight.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(25, 100);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(106, 20);
            this.label7.TabIndex = 28;
            this.label7.Text = "Boundary Up";
            // 
            // tbBoundaryUp
            // 
            this.tbBoundaryUp.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbBoundaryUp.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbBoundaryUp.Location = new System.Drawing.Point(182, 98);
            this.tbBoundaryUp.Name = "tbBoundaryUp";
            this.tbBoundaryUp.Size = new System.Drawing.Size(210, 27);
            this.tbBoundaryUp.TabIndex = 27;
            this.tbBoundaryUp.Text = "20";
            this.tbBoundaryUp.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(25, 67);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(128, 20);
            this.label8.TabIndex = 26;
            this.label8.Text = "Boundary Down";
            // 
            // tbBoundaryDown
            // 
            this.tbBoundaryDown.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbBoundaryDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbBoundaryDown.Location = new System.Drawing.Point(182, 65);
            this.tbBoundaryDown.Name = "tbBoundaryDown";
            this.tbBoundaryDown.Size = new System.Drawing.Size(210, 27);
            this.tbBoundaryDown.TabIndex = 25;
            this.tbBoundaryDown.Text = "0";
            this.tbBoundaryDown.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(25, 34);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(114, 20);
            this.label9.TabIndex = 24;
            this.label9.Text = "Boundary Left";
            // 
            // tbBoundaryLeft
            // 
            this.tbBoundaryLeft.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbBoundaryLeft.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbBoundaryLeft.Location = new System.Drawing.Point(182, 32);
            this.tbBoundaryLeft.Name = "tbBoundaryLeft";
            this.tbBoundaryLeft.Size = new System.Drawing.Size(210, 27);
            this.tbBoundaryLeft.TabIndex = 23;
            this.tbBoundaryLeft.Text = "0";
            this.tbBoundaryLeft.TextChanged += new System.EventHandler(this.tbBodyType_TextChanged);
            // 
            // btnUpdate
            // 
            this.btnUpdate.BackColor = System.Drawing.Color.YellowGreen;
            this.btnUpdate.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnUpdate.Font = new System.Drawing.Font("Microsoft Sans Serif", 28.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnUpdate.Location = new System.Drawing.Point(595, 952);
            this.btnUpdate.Name = "btnUpdate";
            this.btnUpdate.Size = new System.Drawing.Size(210, 96);
            this.btnUpdate.TabIndex = 39;
            this.btnUpdate.Text = "Update";
            this.btnUpdate.UseVisualStyleBackColor = false;
            this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.BackColor = System.Drawing.SystemColors.Control;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.panelGame);
            this.panel1.Location = new System.Drawing.Point(287, 154);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(783, 539);
            this.panel1.TabIndex = 41;
            // 
            // panelGame
            // 
            this.panelGame.BackColor = System.Drawing.Color.White;
            this.panelGame.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelGame.Location = new System.Drawing.Point(0, 0);
            this.panelGame.Name = "panelGame";
            this.panelGame.Size = new System.Drawing.Size(781, 537);
            this.panelGame.TabIndex = 40;
            this.panelGame.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panelGame_MouseClick);
            this.panelGame.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panelGame_MouseMove);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1111, 28);
            this.menuStrip1.TabIndex = 45;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuNewLevel,
            this.menuLoadLevel,
            this.menuSave,
            this.menuExit});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // menuNewLevel
            // 
            this.menuNewLevel.Name = "menuNewLevel";
            this.menuNewLevel.Size = new System.Drawing.Size(149, 24);
            this.menuNewLevel.Text = "New Level";
            this.menuNewLevel.Click += new System.EventHandler(this.menuNewLevel_Click);
            // 
            // menuLoadLevel
            // 
            this.menuLoadLevel.Name = "menuLoadLevel";
            this.menuLoadLevel.Size = new System.Drawing.Size(149, 24);
            this.menuLoadLevel.Text = "Load Level";
            this.menuLoadLevel.Click += new System.EventHandler(this.menuLoadLevel_Click);
            // 
            // menuSave
            // 
            this.menuSave.Name = "menuSave";
            this.menuSave.Size = new System.Drawing.Size(149, 24);
            this.menuSave.Text = "Save";
            this.menuSave.Click += new System.EventHandler(this.menuSave_Click);
            // 
            // menuExit
            // 
            this.menuExit.Name = "menuExit";
            this.menuExit.Size = new System.Drawing.Size(149, 24);
            this.menuExit.Text = "Exit";
            this.menuExit.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // richTextBoxLevel
            // 
            this.richTextBoxLevel.Location = new System.Drawing.Point(32, -34);
            this.richTextBoxLevel.Name = "richTextBoxLevel";
            this.richTextBoxLevel.Size = new System.Drawing.Size(32, 32);
            this.richTextBoxLevel.TabIndex = 46;
            this.richTextBoxLevel.Text = "";
            // 
            // tbLevelName
            // 
            this.tbLevelName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbLevelName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbLevelName.Location = new System.Drawing.Point(117, 36);
            this.tbLevelName.Name = "tbLevelName";
            this.tbLevelName.Size = new System.Drawing.Size(99, 27);
            this.tbLevelName.TabIndex = 47;
            this.tbLevelName.Text = "Level1";
            // 
            // btnSave
            // 
            this.btnSave.AutoSize = true;
            this.btnSave.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSave.Location = new System.Drawing.Point(12, 73);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(56, 30);
            this.btnSave.TabIndex = 48;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // pbSave
            // 
            this.pbSave.Image = global::BrainStorm_Studios_Game_Engine_Level_Creator.Properties.Resources.bullet_accept;
            this.pbSave.Location = new System.Drawing.Point(74, 73);
            this.pbSave.Name = "pbSave";
            this.pbSave.Size = new System.Drawing.Size(30, 30);
            this.pbSave.TabIndex = 49;
            this.pbSave.TabStop = false;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Font = new System.Drawing.Font("Segoe UI", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lblLevelUpdated});
            this.statusStrip1.Location = new System.Drawing.Point(0, 1048);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1111, 28);
            this.statusStrip1.TabIndex = 50;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // lblLevelUpdated
            // 
            this.lblLevelUpdated.Font = new System.Drawing.Font("Segoe UI", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLevelUpdated.Name = "lblLevelUpdated";
            this.lblLevelUpdated.Size = new System.Drawing.Size(128, 23);
            this.lblLevelUpdated.Text = "Level Updated: ";
            // 
            // btnRemoveObject
            // 
            this.btnRemoveObject.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnRemoveObject.BackColor = System.Drawing.Color.LightSalmon;
            this.btnRemoveObject.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnRemoveObject.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRemoveObject.Location = new System.Drawing.Point(811, 1001);
            this.btnRemoveObject.Name = "btnRemoveObject";
            this.btnRemoveObject.Size = new System.Drawing.Size(209, 45);
            this.btnRemoveObject.TabIndex = 51;
            this.btnRemoveObject.Text = "Remove Object";
            this.btnRemoveObject.UseVisualStyleBackColor = false;
            this.btnRemoveObject.Click += new System.EventHandler(this.btnRemoveObject_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(1132, 674);
            this.Controls.Add(this.btnRemoveObject);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.pbSave);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.tbLevelName);
            this.Controls.Add(this.richTextBoxLevel);
            this.Controls.Add(this.btnSetNewObject);
            this.Controls.Add(this.btnUpdate);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tvObjects);
            this.Controls.Add(this.lblLevelName);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Click += new System.EventHandler(this.btnNewLevel_Click);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbSave)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblLevelName;
        private System.Windows.Forms.TreeView tvObjects;
        private System.Windows.Forms.Button btnSetNewObject;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox tbAnimationName;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox tbUserName;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox tbHeight;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox tbWidth;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox tbYCoordinate;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox tbXCoordinate;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox tbActionOverPlayer;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox tbTexturePath;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox tbBodyType;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tbHasScript;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tbBoundaryRight;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox tbBoundaryUp;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox tbBoundaryDown;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox tbBoundaryLeft;
        private System.Windows.Forms.Button btnUpdate;
        private BSPanel panelGame;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbScaleSize;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuNewLevel;
        private System.Windows.Forms.ToolStripMenuItem menuLoadLevel;
        private System.Windows.Forms.ToolStripMenuItem menuSave;
        private System.Windows.Forms.ToolStripMenuItem menuExit;
        private System.Windows.Forms.RichTextBox richTextBoxLevel;
        private System.Windows.Forms.TextBox tbLevelName;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.PictureBox pbSave;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel lblLevelUpdated;
        private System.Windows.Forms.Button btnRemoveObject;
    }
}

