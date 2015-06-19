using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace BrainStorm_Animation_Creator
{
    public partial class Form1 : Form
    {
        public List<BSTexture> listOfTextures = new List<BSTexture>();
        public List<int> indexesOfSelectedTextures = new List<int>();

        int lastIndex = 0, lastTextureX = 10, lastTextureY = 10, selectedIndex = 0;

        public Form1()
        {
            InitializeComponent();
            moveControlsAfterAnimationResize();
            InitializeOpenFileDialog();
        }


        public void moveControlsAfterAnimationResize()
        {
            btnSetTexture.Location = new Point(pbAnimation.Location.X + pbAnimation.Width + 30, btnSetTexture.Location.Y);
            tbSetTexture.Location = new Point(btnSetTexture.Location.X + btnSetTexture.Width + 10, tbSetTexture.Location.Y);

            lblTUNT.Location = new Point(btnSetTexture.Location.X, lblTUNT.Location.Y);
            tbTUNT.Location = new Point(lblTUNT.Location.X + lblTUNT.Width + 10, tbTUNT.Location.Y);

            btnMTB.Location = new Point(btnSetTexture.Location.X, btnMTB.Location.Y);
            btnMTF.Location = new Point(btnMTB.Location.X + btnMTB.Width + 10, btnMTF.Location.Y);

            btnDeleteTexture.Location = new Point(btnSetTexture.Location.X, btnDeleteTexture.Location.Y);
        }

        private void btnAddTextures_Click(object sender, EventArgs e)
        {
            DialogResult result = BSOpenFileDialog.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                setEnableWhenAddtextures(true);

                // Read the files 
                foreach (String file in BSOpenFileDialog.FileNames)
                {
                    try
                    {
                        BSTexture newTexture = new BSTexture();
                        
                        newTexture.texture = new PictureBox();
                        newTexture.texture.Image = Image.FromFile(file);
                        newTexture.texture.BorderStyle = BorderStyle.FixedSingle;
                        newTexture.texture.Size = new System.Drawing.Size(int.Parse(tbWoA.Text), int.Parse(tbHoA.Text));
                        newTexture.texture.SizeMode = PictureBoxSizeMode.Zoom;
                        newTexture.index = lastIndex;
                        newTexture.timeUntilNextTexture = 40;
                        newTexture.texture.Location = new Point(lastTextureX, lastTextureY);
                        newTexture.texture.Click += new EventHandler(onTextureClick);

                        newTexture.blackTexture = new PictureBox();
                        newTexture.blackTexture.BackColor = Color.Black;
                        newTexture.blackTexture.Visible = false;

                        lastTextureX += int.Parse(tbWoA.Text) + 20;

                        panelOfTexture.Controls.Add(newTexture.texture);
                        panelOfTexture.Controls.Add(newTexture.blackTexture);
                        listOfTextures.Add(newTexture);
                        
                        lastIndex++;
                    }
                    catch (Exception ex)
                    {
                        // Could not load the image - probably related to Windows file system permissions.
                        MessageBox.Show("Cannot display the image: " + file.Substring(file.LastIndexOf('\\'))
                            + ". You may not have permission to read the file, or " +
                            "it may be corrupt.\n\nReported error: " + ex.Message);
                    }
                }
            }
        }

        private void InitializeOpenFileDialog()
        {
            // Set the file dialog to filter for graphics files. 
            BSOpenFileDialog.Filter = "Images (*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|" +
                                        "All files (*.*)|*.*";

            // Allow the user to select multiple images. 
            BSOpenFileDialog.Multiselect = true;
            BSOpenFileDialog.Title = "BS Texture Selector";
        }


        private void btnSetTexture_Click(object sender, EventArgs e)
        {

        }

        private void btnSetDefaults_Click(object sender, EventArgs e)
        {
            ///set the animation size to 140x140
            tbWoA.Text = "140";
            tbHoA.Text = "140";

            ///set the time between textures at 40 ms
            for (int i = 0; i < listOfTextures.Count; i++)
            {
                listOfTextures[i].timeUntilNextTexture = 40;
            }
        }

        public void setEnableWhenAddtextures(bool state)
        {
            btnPlayIt.Enabled = state;
            btnStopIt.Enabled = state;
            btnSetDefaults.Enabled = state;

            lblWoA.Enabled = state;
            lblHoA.Enabled = state;

            tbWoA.Enabled = state;
            tbHoA.Enabled = state;
        }

        public void setEnableWhenClickTexture(bool state)
        {
            btnSetTexture.Enabled = state;
            tbSetTexture.Enabled = state;
            lblTUNT.Enabled = state;
            tbTUNT.Enabled = state;
            btnMTB.Enabled = state;
            btnMTF.Enabled = state;
            btnDeleteTexture.Enabled = state;
        }


        private void onTextureClick(object sender, EventArgs e)
        {
            for (int i = 0; i < listOfTextures.Count; i++)
            {
                if (sender.Equals(listOfTextures[i].texture))
                {
                    int alreadySelected = checkIfTextureIsAlreadySelected(i);
                    ///if we already had textures selected and we don't hold "ctrl" and the current texture is selected, then we set the rest as unselected
                    if ((ModifierKeys & Keys.Control) != Keys.Control)
                    {
                        ///diff will tell us if there were more selected, and if we selected a texture that is already selected then we leave it selected
                        int diff = -1;
                        if (indexesOfSelectedTextures.Count > 1)
                        {
                            diff = alreadySelected;
                        }
                        for (int j = 0; j < indexesOfSelectedTextures.Count; j++)
                        {
                            if (diff != j)
                            {
                                listOfTextures[indexesOfSelectedTextures[j]].isSelected = false;
                                listOfTextures[indexesOfSelectedTextures[j]].blackTexture.Visible = false;
                            }
                        }
                        indexesOfSelectedTextures.Clear();

                        ///if we selected a texture that is already selected we left it selected and now we have to reintroduce it in the list
                        if (diff != -1)
                        {
                            indexesOfSelectedTextures.Add(i);
                        }

                        if(alreadySelected == -1)
                        {
                            listOfTextures[i].isSelected = true;
                            listOfTextures[i].blackTexture.Visible = true;
                            indexesOfSelectedTextures.Add(i);
                        }
                        
                        ///indexesOfSelectedTextures.Remove(indexesOfSelectedTextures[selectedIndex]);
                    }
                    else
                    {
                        if (alreadySelected != -1)
                        {
                            listOfTextures[i].isSelected = false;
                            listOfTextures[i].blackTexture.Visible = false;
                            indexesOfSelectedTextures.Remove(indexesOfSelectedTextures[alreadySelected]);
                        }
                        else
                        {
                            listOfTextures[i].isSelected = true;
                            listOfTextures[i].blackTexture.Visible = true;
                            indexesOfSelectedTextures.Add(i);
                        }
                    }
                    ///if we already had textures selected and we don't hold "ctrl" and the current texture is unselected, 
                    ///then we set th rest as unselected and the current one as selected
                    //else
                        //if(

                    ///if we already selected this texture, then we unselect it
                    /*if (listOfTextures[i].isSelected)
                    {
                        listOfTextures[i].blackTexture.Visible = false;
                        listOfTextures[i].isSelected = false;
                    }
                    else
                    {
                        listOfTextures[i].blackTexture.Visible = true;
                        listOfTextures[i].isSelected = true;
                    }
                    selectedIndex = i;
                    */
                    ///enable or disable the controls of texture
                    if (indexesOfSelectedTextures.Count == 0)
                    {
                        setEnableWhenClickTexture(false);
                    }
                    else
                    {
                        setEnableWhenClickTexture(true);
                    }
                    ///set the location of the frame for selected texture
                    listOfTextures[i].blackTexture.Location = new Point(listOfTextures[i].texture.Location.X - 3, listOfTextures[i].texture.Location.Y - 3);
                    listOfTextures[i].blackTexture.Size = new Size(int.Parse(tbWoA.Text) + 6, int.Parse(tbHoA.Text) + 6);
                    listOfTextures[i].blackTexture.SendToBack();

                    break;
                }
            }
        }

        public int checkIfTextureIsAlreadySelected(int currentIndex)
        {
            for (int i = 0; i < indexesOfSelectedTextures.Count; i++)
            {
                if (indexesOfSelectedTextures[i] == currentIndex)
                {
                    return i;
                }
            }
            return -1;
        }

    }


    public class BSTexture/// : System.Windows.Forms.Control
    {
        public PictureBox texture, blackTexture;
        public long timeUntilNextTexture;
        public int index;
        public bool isSelected = false;
    }

    public class BSPanel : System.Windows.Forms.Panel
    {
        public BSPanel()
        {
            this.SetStyle(System.Windows.Forms.ControlStyles.UserPaint | System.Windows.Forms.ControlStyles.AllPaintingInWmPaint | System.Windows.Forms.ControlStyles.OptimizedDoubleBuffer, true);
        }
    }

}
