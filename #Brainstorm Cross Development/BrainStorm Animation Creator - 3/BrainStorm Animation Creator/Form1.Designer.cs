namespace BrainStorm_Animation_Creator
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
            this.components = new System.ComponentModel.Container();
            this.timer3 = new System.Windows.Forms.Timer(this.components);
            this.timer4 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.btnStopIt = new System.Windows.Forms.Button();
            this.tbTUNT = new System.Windows.Forms.TextBox();
            this.lblTUNT = new System.Windows.Forms.Label();
            this.AnimationPanel1 = new System.Windows.Forms.Panel();
            this.panelOfTexture = new System.Windows.Forms.Panel();
            this.btnDeleteTexture = new System.Windows.Forms.Button();
            this.btnMTF = new System.Windows.Forms.Button();
            this.btnMTB = new System.Windows.Forms.Button();
            this.btnSetDefaults = new System.Windows.Forms.Button();
            this.tbSetTexture = new System.Windows.Forms.TextBox();
            this.btnSetTexture = new System.Windows.Forms.Button();
            this.tbHoA = new System.Windows.Forms.TextBox();
            this.tbWoA = new System.Windows.Forms.TextBox();
            this.pbAnimation = new System.Windows.Forms.PictureBox();
            this.btnPlayIt = new System.Windows.Forms.Button();
            this.lblHoA = new System.Windows.Forms.Label();
            this.lblWoA = new System.Windows.Forms.Label();
            this.btnAddTextures = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.BSOpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.AnimationPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbAnimation)).BeginInit();
            this.SuspendLayout();
            // 
            // timer3
            // 
            this.timer3.Interval = 1;
            // 
            // timer4
            // 
            this.timer4.Interval = 1;
            // 
            // timer2
            // 
            this.timer2.Interval = 1;
            // 
            // btnStopIt
            // 
            this.btnStopIt.AutoSize = true;
            this.btnStopIt.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnStopIt.BackColor = System.Drawing.Color.LightGreen;
            this.btnStopIt.Enabled = false;
            this.btnStopIt.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnStopIt.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnStopIt.Location = new System.Drawing.Point(222, 25);
            this.btnStopIt.Margin = new System.Windows.Forms.Padding(4);
            this.btnStopIt.Name = "btnStopIt";
            this.btnStopIt.Size = new System.Drawing.Size(69, 32);
            this.btnStopIt.TabIndex = 15;
            this.btnStopIt.Text = "Stop it";
            this.btnStopIt.UseVisualStyleBackColor = false;
            // 
            // tbTUNT
            // 
            this.tbTUNT.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbTUNT.Enabled = false;
            this.tbTUNT.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbTUNT.Location = new System.Drawing.Point(894, 69);
            this.tbTUNT.Margin = new System.Windows.Forms.Padding(4);
            this.tbTUNT.Name = "tbTUNT";
            this.tbTUNT.Size = new System.Drawing.Size(70, 26);
            this.tbTUNT.TabIndex = 8;
            this.tbTUNT.Text = "40";
            // 
            // lblTUNT
            // 
            this.lblTUNT.AutoSize = true;
            this.lblTUNT.Enabled = false;
            this.lblTUNT.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTUNT.Location = new System.Drawing.Point(667, 71);
            this.lblTUNT.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTUNT.Name = "lblTUNT";
            this.lblTUNT.Size = new System.Drawing.Size(219, 20);
            this.lblTUNT.TabIndex = 7;
            this.lblTUNT.Text = "Time until next texture (ms):";
            // 
            // AnimationPanel1
            // 
            this.AnimationPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.AnimationPanel1.AutoScroll = true;
            this.AnimationPanel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AnimationPanel1.Controls.Add(this.panelOfTexture);
            this.AnimationPanel1.Controls.Add(this.btnDeleteTexture);
            this.AnimationPanel1.Controls.Add(this.btnMTF);
            this.AnimationPanel1.Controls.Add(this.btnMTB);
            this.AnimationPanel1.Controls.Add(this.btnSetDefaults);
            this.AnimationPanel1.Controls.Add(this.tbSetTexture);
            this.AnimationPanel1.Controls.Add(this.btnSetTexture);
            this.AnimationPanel1.Controls.Add(this.btnStopIt);
            this.AnimationPanel1.Controls.Add(this.tbTUNT);
            this.AnimationPanel1.Controls.Add(this.lblTUNT);
            this.AnimationPanel1.Controls.Add(this.tbHoA);
            this.AnimationPanel1.Controls.Add(this.tbWoA);
            this.AnimationPanel1.Controls.Add(this.pbAnimation);
            this.AnimationPanel1.Controls.Add(this.btnPlayIt);
            this.AnimationPanel1.Controls.Add(this.lblHoA);
            this.AnimationPanel1.Controls.Add(this.lblWoA);
            this.AnimationPanel1.Controls.Add(this.btnAddTextures);
            this.AnimationPanel1.Location = new System.Drawing.Point(36, 30);
            this.AnimationPanel1.Margin = new System.Windows.Forms.Padding(4);
            this.AnimationPanel1.Name = "AnimationPanel1";
            this.AnimationPanel1.Size = new System.Drawing.Size(1281, 626);
            this.AnimationPanel1.TabIndex = 13;
            // 
            // panelOfTexture
            // 
            this.panelOfTexture.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.panelOfTexture.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelOfTexture.Location = new System.Drawing.Point(19, 225);
            this.panelOfTexture.Name = "panelOfTexture";
            this.panelOfTexture.Size = new System.Drawing.Size(1238, 378);
            this.panelOfTexture.TabIndex = 22;
            // 
            // btnDeleteTexture
            // 
            this.btnDeleteTexture.AutoSize = true;
            this.btnDeleteTexture.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnDeleteTexture.BackColor = System.Drawing.Color.LightSalmon;
            this.btnDeleteTexture.Enabled = false;
            this.btnDeleteTexture.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnDeleteTexture.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDeleteTexture.Location = new System.Drawing.Point(671, 155);
            this.btnDeleteTexture.Margin = new System.Windows.Forms.Padding(4);
            this.btnDeleteTexture.Name = "btnDeleteTexture";
            this.btnDeleteTexture.Size = new System.Drawing.Size(152, 32);
            this.btnDeleteTexture.TabIndex = 21;
            this.btnDeleteTexture.Text = "Delete Texture(s)";
            this.btnDeleteTexture.UseVisualStyleBackColor = false;
            // 
            // btnMTF
            // 
            this.btnMTF.AutoSize = true;
            this.btnMTF.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnMTF.BackColor = System.Drawing.Color.LightGreen;
            this.btnMTF.Enabled = false;
            this.btnMTF.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMTF.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnMTF.Location = new System.Drawing.Point(909, 105);
            this.btnMTF.Margin = new System.Windows.Forms.Padding(4);
            this.btnMTF.Name = "btnMTF";
            this.btnMTF.Size = new System.Drawing.Size(209, 32);
            this.btnMTF.TabIndex = 20;
            this.btnMTF.Text = "Move Texture(s) Forward";
            this.btnMTF.UseVisualStyleBackColor = false;
            // 
            // btnMTB
            // 
            this.btnMTB.AutoSize = true;
            this.btnMTB.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnMTB.BackColor = System.Drawing.Color.LightGreen;
            this.btnMTB.Enabled = false;
            this.btnMTB.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnMTB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnMTB.Location = new System.Drawing.Point(671, 105);
            this.btnMTB.Margin = new System.Windows.Forms.Padding(4);
            this.btnMTB.Name = "btnMTB";
            this.btnMTB.Size = new System.Drawing.Size(222, 32);
            this.btnMTB.TabIndex = 19;
            this.btnMTB.Text = "Move Texture(s) Backward";
            this.btnMTB.UseVisualStyleBackColor = false;
            // 
            // btnSetDefaults
            // 
            this.btnSetDefaults.AutoSize = true;
            this.btnSetDefaults.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnSetDefaults.BackColor = System.Drawing.Color.LightGreen;
            this.btnSetDefaults.Enabled = false;
            this.btnSetDefaults.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSetDefaults.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSetDefaults.Location = new System.Drawing.Point(299, 25);
            this.btnSetDefaults.Margin = new System.Windows.Forms.Padding(4);
            this.btnSetDefaults.Name = "btnSetDefaults";
            this.btnSetDefaults.Size = new System.Drawing.Size(114, 32);
            this.btnSetDefaults.TabIndex = 18;
            this.btnSetDefaults.Text = "Set Defaults";
            this.btnSetDefaults.UseVisualStyleBackColor = false;
            this.btnSetDefaults.Click += new System.EventHandler(this.btnSetDefaults_Click);
            // 
            // tbSetTexture
            // 
            this.tbSetTexture.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbSetTexture.Enabled = false;
            this.tbSetTexture.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbSetTexture.Location = new System.Drawing.Point(786, 29);
            this.tbSetTexture.Margin = new System.Windows.Forms.Padding(4);
            this.tbSetTexture.Name = "tbSetTexture";
            this.tbSetTexture.Size = new System.Drawing.Size(489, 26);
            this.tbSetTexture.TabIndex = 17;
            // 
            // btnSetTexture
            // 
            this.btnSetTexture.AutoSize = true;
            this.btnSetTexture.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnSetTexture.BackColor = System.Drawing.Color.LightGreen;
            this.btnSetTexture.Enabled = false;
            this.btnSetTexture.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSetTexture.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSetTexture.Location = new System.Drawing.Point(671, 25);
            this.btnSetTexture.Margin = new System.Windows.Forms.Padding(4);
            this.btnSetTexture.Name = "btnSetTexture";
            this.btnSetTexture.Size = new System.Drawing.Size(107, 32);
            this.btnSetTexture.TabIndex = 16;
            this.btnSetTexture.Text = "Set Texture";
            this.btnSetTexture.UseVisualStyleBackColor = false;
            this.btnSetTexture.Click += new System.EventHandler(this.btnSetTexture_Click);
            // 
            // tbHoA
            // 
            this.tbHoA.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbHoA.Enabled = false;
            this.tbHoA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbHoA.Location = new System.Drawing.Point(171, 114);
            this.tbHoA.Margin = new System.Windows.Forms.Padding(4);
            this.tbHoA.Name = "tbHoA";
            this.tbHoA.Size = new System.Drawing.Size(70, 26);
            this.tbHoA.TabIndex = 6;
            this.tbHoA.Text = "140";
            // 
            // tbWoA
            // 
            this.tbWoA.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tbWoA.Enabled = false;
            this.tbWoA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbWoA.Location = new System.Drawing.Point(171, 80);
            this.tbWoA.Margin = new System.Windows.Forms.Padding(4);
            this.tbWoA.Name = "tbWoA";
            this.tbWoA.Size = new System.Drawing.Size(70, 26);
            this.tbWoA.TabIndex = 5;
            this.tbWoA.Text = "140";
            // 
            // pbAnimation
            // 
            this.pbAnimation.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbAnimation.Location = new System.Drawing.Point(436, 15);
            this.pbAnimation.Margin = new System.Windows.Forms.Padding(4);
            this.pbAnimation.Name = "pbAnimation";
            this.pbAnimation.Size = new System.Drawing.Size(186, 172);
            this.pbAnimation.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pbAnimation.TabIndex = 4;
            this.pbAnimation.TabStop = false;
            // 
            // btnPlayIt
            // 
            this.btnPlayIt.AutoSize = true;
            this.btnPlayIt.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnPlayIt.BackColor = System.Drawing.Color.LightGreen;
            this.btnPlayIt.Enabled = false;
            this.btnPlayIt.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPlayIt.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnPlayIt.Location = new System.Drawing.Point(147, 25);
            this.btnPlayIt.Margin = new System.Windows.Forms.Padding(4);
            this.btnPlayIt.Name = "btnPlayIt";
            this.btnPlayIt.Size = new System.Drawing.Size(67, 32);
            this.btnPlayIt.TabIndex = 3;
            this.btnPlayIt.Text = "Play it";
            this.btnPlayIt.UseVisualStyleBackColor = false;
            // 
            // lblHoA
            // 
            this.lblHoA.AutoSize = true;
            this.lblHoA.Enabled = false;
            this.lblHoA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblHoA.Location = new System.Drawing.Point(8, 117);
            this.lblHoA.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblHoA.Name = "lblHoA";
            this.lblHoA.Size = new System.Drawing.Size(161, 20);
            this.lblHoA.TabIndex = 2;
            this.lblHoA.Text = "Height of Animation:";
            // 
            // lblWoA
            // 
            this.lblWoA.AutoSize = true;
            this.lblWoA.Enabled = false;
            this.lblWoA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblWoA.Location = new System.Drawing.Point(8, 82);
            this.lblWoA.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblWoA.Name = "lblWoA";
            this.lblWoA.Size = new System.Drawing.Size(155, 20);
            this.lblWoA.TabIndex = 1;
            this.lblWoA.Text = "Width of Animation:";
            // 
            // btnAddTextures
            // 
            this.btnAddTextures.AutoSize = true;
            this.btnAddTextures.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnAddTextures.BackColor = System.Drawing.Color.LightGreen;
            this.btnAddTextures.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnAddTextures.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnAddTextures.Location = new System.Drawing.Point(19, 25);
            this.btnAddTextures.Margin = new System.Windows.Forms.Padding(4);
            this.btnAddTextures.Name = "btnAddTextures";
            this.btnAddTextures.Size = new System.Drawing.Size(120, 32);
            this.btnAddTextures.TabIndex = 0;
            this.btnAddTextures.Text = "Add Textures";
            this.btnAddTextures.UseVisualStyleBackColor = false;
            this.btnAddTextures.Click += new System.EventHandler(this.btnAddTextures_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 1;
            // 
            // BSOpenFileDialog
            // 
            this.BSOpenFileDialog.FileName = "BSOpenFileDialog";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(1342, 721);
            this.Controls.Add(this.AnimationPanel1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.AnimationPanel1.ResumeLayout(false);
            this.AnimationPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbAnimation)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer3;
        private System.Windows.Forms.Timer timer4;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Button btnStopIt;
        private System.Windows.Forms.TextBox tbTUNT;
        private System.Windows.Forms.Label lblTUNT;
        private System.Windows.Forms.Panel AnimationPanel1;
        private System.Windows.Forms.TextBox tbHoA;
        private System.Windows.Forms.TextBox tbWoA;
        private System.Windows.Forms.PictureBox pbAnimation;
        private System.Windows.Forms.Button btnPlayIt;
        private System.Windows.Forms.Label lblHoA;
        private System.Windows.Forms.Label lblWoA;
        private System.Windows.Forms.Button btnAddTextures;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox tbSetTexture;
        private System.Windows.Forms.Button btnSetTexture;
        private System.Windows.Forms.Button btnSetDefaults;
        private System.Windows.Forms.Button btnMTF;
        private System.Windows.Forms.Button btnMTB;
        private System.Windows.Forms.Button btnDeleteTexture;
        private System.Windows.Forms.OpenFileDialog BSOpenFileDialog;
        private System.Windows.Forms.Panel panelOfTexture;


    }
}

