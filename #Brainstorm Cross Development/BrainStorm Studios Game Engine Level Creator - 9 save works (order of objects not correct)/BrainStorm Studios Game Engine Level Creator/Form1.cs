using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;


namespace BrainStorm_Studios_Game_Engine_Level_Creator
{
    public partial class Form1 : Form
    {
        List<BSObject> listOfObjects = new List<BSObject>();

        float boundary_left, boundary_down, boundary_up, boundary_right, ScaleSize;
        String levelName;
        int hasScript, lastBodyIndex = 0;
        bool errorParsing = false, modifiedObjectOrLevel = false;
        String savingPath = "";

        float moveShiftX, moveShiftY;
            
        BSXMLStruct newXML = new BSXMLStruct();
        List<String> secondNodes = new List<String>();
        List<String> attributes = new List<String>();

        float xCoordHover = 1, yCoordHover = 1, widthHover = 1, heightHover = 1;

        float xCoord, yCoord, width, height;
        int can_kill_or_next_level, index, body_Type, theSelectedBodyIndex = -1;
        String texture_Path, animation_Path, userName;

        public Graphics line1;
        public Pen myPen1;

        int k = 0;
        public Form1()
        {
            InitializeComponent();

            myPen1 = new Pen(Color.Black);
            //line1 = panelGame.CreateGraphics();

            panelGame.Paint += new PaintEventHandler(drawGame);
            //panelGame.Invalidate();

            ///lblLevelName.Text = "No level loaded";

            levelName = tbLevelName.Text;
            ScaleSize = float.Parse(tbScaleSize.Text);

            xCoord = float.Parse(tbXCoordinate.Text);
            yCoord = float.Parse(tbYCoordinate.Text);
            width = float.Parse(tbWidth.Text);
            height = float.Parse(tbHeight.Text);
            can_kill_or_next_level = int.Parse(tbActionOverPlayer.Text);
            body_Type = int.Parse(tbBodyType.Text);
            index = 0;
            userName = tbUserName.Text;
            texture_Path = tbTexturePath.Text;
            animation_Path = tbAnimationName.Text;

            loadLevel("level2.xml");

            tbBoundaryLeft.Text = boundary_left.ToString();
            tbBoundaryDown.Text = boundary_down.ToString();
            tbBoundaryUp.Text = boundary_up.ToString();
            tbBoundaryRight.Text = boundary_right.ToString();
            tbHasScript.Text = hasScript.ToString();

            //boundary_left = Convert.ToInt64(tbBoundaryLeft.Text);
            //boundary_down = Convert.ToInt64(tbBoundaryDown.Text);
            //boundary_up = Convert.ToInt64(tbBoundaryUp.Text);
            //boundary_right = Convert.ToInt64(tbBoundaryRight.Text);
            //hasScript = int.Parse(tbHasScript.Text);

            if (panelGame.Width < (int)(boundary_right * ScaleSize) || panel1.Width < (int)(boundary_right * ScaleSize))
            {
                panelGame.Width = (int)(boundary_right * ScaleSize);
            }
            if (panelGame.Height < (int)(boundary_up * ScaleSize) || panel1.Height < (int)(boundary_up * ScaleSize))
            {
                panelGame.Height = (int)(boundary_up * ScaleSize);
            }
            //this.SetStyle( ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.DoubleBuffer, true);
            //drawGame();
            menuStrip1.Focus();
        }

        void loadLevel(String Path)
        {
            try
            {
                newXML.secondNodes.Clear();
                newXML.headAttributes.Clear();
                secondNodes.Add("Body_Type");
                secondNodes.Add("Texture_path");
                secondNodes.Add("Kill_or_Next_Level");
                secondNodes.Add("xCoordinate");
                secondNodes.Add("yCoordinate");
                secondNodes.Add("width");
                secondNodes.Add("height");
                secondNodes.Add("userName");
                secondNodes.Add("Animation_name");
                secondNodes.Add("Index");
                attributes.Add("name");
                attributes.Add("boundary_Left");
                attributes.Add("boundary_Down");
                attributes.Add("boundary_Up");
                attributes.Add("boundary_Right");
                attributes.Add("script");
                
                newXML = readXML(Path, secondNodes, attributes, attributes, "Level", "obstacle");

                int indexMaxim = 0;

                for (int i = 0; i < newXML.secondNodes.Count; i++)
                {
                    BSObject obj = new BSObject();

                    obj.body_Type = int.Parse(newXML.secondNodes[i].nodeValue[0]);
                    obj.texture_Path = newXML.secondNodes[i].nodeValue[1];
                    obj.can_kill_or_next_level = int.Parse(newXML.secondNodes[i].nodeValue[2]);
                    obj.xCoord = float.Parse(newXML.secondNodes[i].nodeValue[3]);
                    obj.yCoord = float.Parse(newXML.secondNodes[i].nodeValue[4]);
                    obj.width = float.Parse(newXML.secondNodes[i].nodeValue[5]);
                    obj.height = float.Parse(newXML.secondNodes[i].nodeValue[6]);
                    obj.userName = newXML.secondNodes[i].nodeValue[7];
                    obj.animation_Path = newXML.secondNodes[i].nodeValue[8];
                    obj.index = int.Parse(newXML.secondNodes[i].nodeValue[9]);
                    obj.isSelected = false;
                    obj.treeNodeIndex = i;

                    tvObjects.Nodes.Add(obj.userName);
                    tvObjects.Nodes[i].Nodes.Add(obj.body_Type.ToString());
                    tvObjects.Nodes[i].Nodes.Add(obj.texture_Path);
                    tvObjects.Nodes[i].Nodes.Add(obj.can_kill_or_next_level.ToString());
                    tvObjects.Nodes[i].Nodes.Add(obj.xCoord.ToString());
                    tvObjects.Nodes[i].Nodes.Add(obj.yCoord.ToString());
                    tvObjects.Nodes[i].Nodes.Add(obj.width.ToString());
                    tvObjects.Nodes[i].Nodes.Add(obj.height.ToString());
                    tvObjects.Nodes[i].Nodes.Add(obj.animation_Path);
                    tvObjects.Nodes[i].Nodes.Add(obj.index.ToString());

                    listOfObjects.Add(obj);
                    //System.Diagnostics.Debug.WriteLine("obstacle:");
                    //for (int j = 0; j < newXML.secondNodes[i].nodeValue.Count; j++)
                    //{
                    //    System.Diagnostics.Debug.WriteLine("    "+secondNodes[j]+": "+newXML.secondNodes[i].nodeValue[j]);
                    //}
                    //System.Diagnostics.Debug.WriteLine("");

                    if (indexMaxim < listOfObjects[listOfObjects.Count - 1].index)
                    {
                        indexMaxim = listOfObjects[listOfObjects.Count - 1].index;
                    }
                }
                lastBodyIndex = indexMaxim + 1;
                
                boundary_left = float.Parse(newXML.headAttributes[1]);
                boundary_down = float.Parse(newXML.headAttributes[2]);
                boundary_up = float.Parse(newXML.headAttributes[3]);
                boundary_right = float.Parse(newXML.headAttributes[4]);
                hasScript = int.Parse(newXML.headAttributes[5]);

                errorParsing = false;
            }
            catch
            {
                MessageBox.Show("Error parsing the xml file!");
                listOfObjects.Clear();
                errorParsing = true;

                panelGame.Invalidate();

                int nrOfItems = tvObjects.Nodes.Count;

                for (int i = 0; i < nrOfItems; i++)
                {
                    tvObjects.Nodes[0].Remove();
                }
            }
        }

        public void drawGame(object sender, PaintEventArgs e)
        {
            //draw the objects
            for (int i = 0; i < listOfObjects.Count; i++)
            {
                Pen thePen = new Pen(Color.Black);
                thePen.Width = 2;
                SolidBrush brush = new SolidBrush(Color.SteelBlue);

                if (!listOfObjects[i].isSelected)
                {
                    ///if is square
                    if (listOfObjects[i].body_Type == 0 || listOfObjects[i].body_Type == 3 || listOfObjects[i].body_Type == 6 || listOfObjects[i].body_Type == 8 || listOfObjects[i].body_Type == 10)
                    {
                        ///if is an obstacle that doesn't do anything
                        if ((listOfObjects[i].body_Type == 0 || listOfObjects[i].body_Type == 8) && !listOfObjects[i].userName.Equals("hero"))
                        {
                            ///daca nu omoara jucatorul
                            if (listOfObjects[i].can_kill_or_next_level == 0)
                            {
                                brush.Color = Color.CornflowerBlue;
                            }
                            else
                                ///daca il omoara
                                if (listOfObjects[i].can_kill_or_next_level == 1)
                                {
                                    brush.Color = Color.OrangeRed;
                                }
                                else
                                    ///daca il trimite la nivelul urmator
                                    if (listOfObjects[i].can_kill_or_next_level == 2)
                                    {
                                        brush.Color = Color.YellowGreen;
                                    }
                        }
                        else
                            ///if is the hero
                            if (listOfObjects[i].body_Type == 0 && listOfObjects[i].userName.Equals("hero"))
                            {
                                brush.Color = Color.SandyBrown;
                            }
                            else
                                ///if is only a texture
                                if (listOfObjects[i].body_Type == 3)
                                {
                                    brush.Color = Color.DarkKhaki;
                                }
                                else
                                    ///if is a fan
                                    if (listOfObjects[i].body_Type == 6)
                                    {
                                        brush.Color = Color.BlanchedAlmond;
                                    }
                                    else
                                        ///if is a dust body
                                        if (listOfObjects[i].body_Type == 10)
                                        {
                                            brush.Color = Color.Brown;
                                        }

                        e.Graphics.DrawRectangle(thePen, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                            panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                        e.Graphics.FillRectangle(brush, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                            panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                    }
                    //if it is a circle
                    else
                    {
                        ///if is an obstacle that doesn't do anything
                        if ((listOfObjects[i].body_Type == 1 || listOfObjects[i].body_Type == 9) && !listOfObjects[i].userName.Equals("hero"))
                        {
                            ///daca nu omoara jucatorul
                            if (listOfObjects[i].can_kill_or_next_level == 0)
                            {
                                brush.Color = Color.CornflowerBlue;
                            }
                            else
                                ///daca il omoara
                                if (listOfObjects[i].can_kill_or_next_level == 1)
                                {
                                    brush.Color = Color.OrangeRed;
                                }
                                else
                                    ///daca il trimite la nivelul urmator
                                    if (listOfObjects[i].can_kill_or_next_level == 2)
                                    {
                                        brush.Color = Color.YellowGreen;
                                    }
                        }
                        else
                            ///if is only a texture
                            if (listOfObjects[i].body_Type == 4)
                            {
                                brush.Color = Color.DarkKhaki;
                            }
                            else
                                ///if is a coin
                                if (listOfObjects[i].body_Type == 5)
                                {
                                    brush.Color = Color.Gold;
                                }
                                else
                                    ///if is a worm hole
                                    if (listOfObjects[i].body_Type == 7)
                                    {
                                        brush.Color = Color.Orange;
                                        e.Graphics.DrawEllipse(thePen, (listOfObjects[i].xCoord - 2 / 2.0f) * ScaleSize,
                                                                            panelGame.Height - (listOfObjects[i].yCoord + 2 / 2.0f) * ScaleSize,
                                                                                2 * ScaleSize, 2 * ScaleSize);
                                        e.Graphics.FillEllipse(brush, (listOfObjects[i].xCoord - 2 / 2.0f) * ScaleSize,
                                                                            panelGame.Height - (listOfObjects[i].yCoord + 2 / 2.0f) * ScaleSize,
                                                                                2 * ScaleSize, 2 * ScaleSize);
                                    }

                        e.Graphics.DrawEllipse(thePen, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                            panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                        e.Graphics.FillEllipse(brush, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                            panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                    }
                }
                else
                {
                    brush.Color = Color.Blue;
                    ///if is square
                    if (listOfObjects[i].body_Type == 0 || listOfObjects[i].body_Type == 3 || listOfObjects[i].body_Type == 6 || listOfObjects[i].body_Type == 8 || listOfObjects[i].body_Type == 10)
                    {
                        e.Graphics.DrawRectangle(thePen, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                            panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                        e.Graphics.FillRectangle(brush, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                            panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                    }
                    //if it is a circle
                    else
                    {
                        ///if is a worm hole
                        if (listOfObjects[i].body_Type == 7)
                        {
                            e.Graphics.DrawEllipse(thePen, (listOfObjects[i].xCoord - 2 / 2.0f) * ScaleSize,
                                                                panelGame.Height - (listOfObjects[i].yCoord + 2 / 2.0f) * ScaleSize,
                                                                    2 * ScaleSize, 2 * ScaleSize);
                            e.Graphics.FillEllipse(brush, (listOfObjects[i].xCoord - 2 / 2.0f) * ScaleSize,
                                                                panelGame.Height - (listOfObjects[i].yCoord + 2 / 2.0f) * ScaleSize,
                                                                    2 * ScaleSize, 2 * ScaleSize);
                        }
                        else
                        {
                            e.Graphics.DrawEllipse(thePen, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                               panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                   listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                            e.Graphics.FillEllipse(brush, (listOfObjects[i].xCoord - listOfObjects[i].width / 2.0f) * ScaleSize,
                                                                panelGame.Height - (listOfObjects[i].yCoord + listOfObjects[i].height / 2.0f) * ScaleSize,
                                                                    listOfObjects[i].width * ScaleSize, listOfObjects[i].height * ScaleSize);
                        }
                    }
                }
            }

            ///draw the position body (the one that moves with the mouse) 
            Pen hoverPen = new Pen(Color.Black);
            hoverPen.Width = 2;
            SolidBrush hoverBrush = new SolidBrush(Color.Orange);


            if (body_Type == 0 || body_Type == 3 || body_Type == 6 || body_Type == 8 || body_Type == 10)
            {
                e.Graphics.DrawRectangle(hoverPen, (xCoordHover - widthHover / 2.0f) * ScaleSize,
                                                    panelGame.Height - (yCoordHover + heightHover / 2.0f) * ScaleSize,
                                                        widthHover * ScaleSize, heightHover * ScaleSize);
                e.Graphics.FillRectangle(hoverBrush, (xCoordHover - widthHover / 2.0f) * ScaleSize,
                                                    panelGame.Height - (yCoordHover + heightHover / 2.0f) * ScaleSize,
                                                        widthHover * ScaleSize, heightHover * ScaleSize);
            }
            //if it is a circle
            else
            {
                ///if is a worm hole
                if (body_Type == 7)
                {
                    e.Graphics.DrawEllipse(hoverPen, (xCoordHover - widthHover / 2.0f) * ScaleSize,
                                                        panelGame.Height - (yCoordHover + heightHover / 2.0f) * ScaleSize,
                                                            widthHover * ScaleSize, heightHover * ScaleSize);
                    e.Graphics.FillEllipse(hoverBrush, (xCoordHover - widthHover / 2.0f) * ScaleSize,
                                                        panelGame.Height - (yCoordHover + heightHover / 2.0f) * ScaleSize,
                                                            widthHover * ScaleSize, heightHover * ScaleSize);
                }
                else
                {
                    e.Graphics.DrawEllipse(hoverPen, (xCoordHover - widthHover / 2.0f) * ScaleSize,
                                                        panelGame.Height - (yCoordHover + heightHover / 2.0f) * ScaleSize,
                                                            widthHover * ScaleSize, heightHover * ScaleSize);
                    e.Graphics.FillEllipse(hoverBrush, (xCoordHover - widthHover / 2.0f) * ScaleSize,
                                                        panelGame.Height - (yCoordHover + heightHover / 2.0f) * ScaleSize,
                                                            widthHover * ScaleSize, heightHover * ScaleSize);
                }
            }

            //panelGame.Invalidate();
            //e.Graphics.DrawLine(myPen1, 32, 32, k / 10, 312);
            //e.Graphics.DrawRectangle(myPen1, 32, 32, 32, 32);
            //panelGame.Update();
        }

        public BSXMLStruct readXML(String path, List<String> secondNodes, List<String> attributes, List<String> headAttributes, String headNode, String secondNode)
        {
            BSXMLStruct xmlStruct = new BSXMLStruct();
            XmlTextReader theFile = new XmlTextReader(path);
            //BSXMLNode newNode = null;
            BSXMLNode newSecondNode = null;
            String nodeName = "";
            while (theFile.Read())
            {
                switch (theFile.NodeType)
                {
                    case XmlNodeType.Element: // The node is an element.
                        if (theFile.Name.Equals(secondNode))
                        {
                            newSecondNode = new BSXMLNode();
                        }

                        nodeName = theFile.Name;
                        
                        while (theFile.MoveToNextAttribute()) // Read the attributes.
                        {
                            if (nodeName.Equals(headNode))
                            {
                                for (int i = 0; i < headAttributes.Count; i++)
                                {
                                    ///MessageBox.Show(theFile.Name +": " + headAttributes[i]);
                                    if (theFile.Name.Equals(headAttributes[i]))
                                    {
                                        xmlStruct.headAttributes.Add(theFile.Value);
                                    }
                                }
                            }
                            else
                            {
                                if (newSecondNode != null)
                                {
                                    for (int i = 0; i < attributes.Count; i++)
                                    {
                                        if (theFile.Value.Equals(attributes[i]))
                                        {
                                            newSecondNode.attributes.Add(theFile.Value);
                                            ///xmlStruct.headAttributes.Add(theFile.Value);
                                        }
                                    }
                                }
                            }
                            System.Diagnostics.Debug.WriteLine("atr " + theFile.Value + " atr");
                        }
                        System.Diagnostics.Debug.WriteLine("<" + theFile.Name + ">");
                        break;

                    case XmlNodeType.Text: //Display the text in each element.
                        if (newSecondNode != null)
                        {
                            System.Diagnostics.Debug.WriteLine("lal3lalaa: " + nodeName);
                            for (int i = 0; i < secondNodes.Count; i++)
                            {
                                if (nodeName.Equals(secondNodes[i]))
                                {
                                    newSecondNode.nodeValue.Add(theFile.Value);
                                    //newNode.nodeValue
                                    //xmlStruct.secondNodes.Add(newNode);
                                }
                            }
                        }
                        System.Diagnostics.Debug.WriteLine(theFile.Value);
                        break;

                    case XmlNodeType.EndElement: //Display the end of the element.
                        if (theFile.Name.Equals(secondNode))
                        {
                            xmlStruct.secondNodes.Add(newSecondNode);
                            newSecondNode = null;
                        }

                        System.Diagnostics.Debug.WriteLine("</" + theFile.Name + ">");
                        break;
                }
            }
            theFile = null;
            return xmlStruct;
        }

        private void tvObjects_AfterSelect(object sender, TreeViewEventArgs e)
        {
            int selectedIndex;
            //float xCoordSelected, yCoordSelected, widthSelected, heightSelected;
            //int can_kill_or_next_levelSelected, body_TypeSelected;
            //String texture_PathSelected, animation_PathSelected, userNameSelected;

            try
            {
                selectedIndex = int.Parse(tvObjects.SelectedNode.Parent.Nodes[8].Text);
            }
            catch
            {
                selectedIndex = int.Parse(tvObjects.SelectedNode.Nodes[8].Text);
            }

            for (int i = 0; i < listOfObjects.Count; i++)
            {
                if (listOfObjects[i].index != selectedIndex)
                {
                    listOfObjects[i].isSelected = false;
                }
                else
                {
                    listOfObjects[i].isSelected = true;

                    tbBodyType.Text = listOfObjects[i].body_Type.ToString();
                    tbTexturePath.Text = listOfObjects[i].texture_Path.ToString();
                    tbActionOverPlayer.Text = listOfObjects[i].can_kill_or_next_level.ToString();
                    tbXCoordinate.Text = listOfObjects[i].xCoord.ToString();
                    tbYCoordinate.Text = listOfObjects[i].yCoord.ToString();
                    tbWidth.Text = listOfObjects[i].width.ToString();
                    tbHeight.Text = listOfObjects[i].height.ToString();
                    tbUserName.Text = listOfObjects[i].userName.ToString();
                    tbAnimationName.Text = listOfObjects[i].animation_Path.ToString();

                    theSelectedBodyIndex = i;

                    panelGame.Invalidate();
                    break;
                }
            }

        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            bool canChange = false;
            try
            {
                levelName = tbLevelName.Text;
                boundary_left = float.Parse(tbBoundaryLeft.Text);
                boundary_down = float.Parse(tbBoundaryDown.Text);
                boundary_up = float.Parse(tbBoundaryUp.Text);
                boundary_right = float.Parse(tbBoundaryRight.Text);

                hasScript = int.Parse(tbHasScript.Text);

                ScaleSize = float.Parse(tbScaleSize.Text);

                float last = panelGame.Width;
                if (panelGame.Width < (int)(boundary_right * ScaleSize) || panel1.Width < (int)(boundary_right * ScaleSize))
                {
                    panelGame.Width = (int)(boundary_right * ScaleSize);
                }
                if (panelGame.Height < (int)(boundary_up * ScaleSize) || panel1.Height < (int)(boundary_up * ScaleSize))
                {
                    panelGame.Height = (int)(boundary_up * ScaleSize);
                }

                body_Type = int.Parse(tbBodyType.Text);
                texture_Path = tbTexturePath.Text;
                can_kill_or_next_level = int.Parse(tbActionOverPlayer.Text);
                width = float.Parse(tbWidth.Text);
                widthHover = width;
                height = float.Parse(tbHeight.Text);
                heightHover = height;
                userName = tbUserName.Text;
                animation_Path = tbAnimationName.Text;

                modifiedObjectOrLevel = false;
                lblLevelUpdated.Text = "Level Updated: true";

                canChange = true;
                panelGame.Invalidate();
            }
            catch
            {
                MessageBox.Show("Introduceti valori corecte in proprietati!");
            }
            if (theSelectedBodyIndex != -1 && canChange)
            {
                try
                {
                    listOfObjects[theSelectedBodyIndex].body_Type = int.Parse(tbBodyType.Text);
                    listOfObjects[theSelectedBodyIndex].texture_Path = tbTexturePath.Text;
                    listOfObjects[theSelectedBodyIndex].can_kill_or_next_level = int.Parse(tbActionOverPlayer.Text);
                    listOfObjects[theSelectedBodyIndex].xCoord = float.Parse(tbXCoordinate.Text);
                    listOfObjects[theSelectedBodyIndex].yCoord = float.Parse(tbYCoordinate.Text);
                    listOfObjects[theSelectedBodyIndex].width = float.Parse(tbWidth.Text);
                    listOfObjects[theSelectedBodyIndex].height = float.Parse(tbHeight.Text);
                    listOfObjects[theSelectedBodyIndex].userName = tbUserName.Text;
                    listOfObjects[theSelectedBodyIndex].animation_Path = tbAnimationName.Text;

                    panelGame.Invalidate();
                    MessageBox.Show("Properties saved.");
                }
                catch
                {
                    MessageBox.Show("Introduceti valori corecte in proprietati!!");
                }
            }
        }

        private void panelGame_MouseClick(object sender, MouseEventArgs e)
        {
            bool canAdd = true;
            ///check if there is another body (a body that reacts to physics) with the same coordinates and size over the body that we want to add
            for (int i = 0; i < listOfObjects.Count; i++)
            {
                listOfObjects[i].isSelected = false;
                ///daca e diferit de textura corpul adaugat (patrata sau rotunda)
                if (((listOfObjects[i].body_Type != 3 && body_Type != 3) || (listOfObjects[i].body_Type != 4 && body_Type != 4)) &&
                    listOfObjects[i].xCoord == xCoordHover && listOfObjects[i].yCoord == yCoordHover &&
                    listOfObjects[i].width == widthHover && listOfObjects[i].height == heightHover)
                {
                    canAdd = false;
                    listOfObjects[i].isSelected = true;
                    theSelectedBodyIndex = i;
                    tvObjects.SelectedNode = tvObjects.Nodes[listOfObjects[i].treeNodeIndex];
                    ///break;
                }
            }
            if (canAdd == true)
            {
                tbXCoordinate.Text = xCoordHover.ToString();
                tbYCoordinate.Text = yCoordHover.ToString();

                BSObject newObject = new BSObject();
                newObject.animation_Path = animation_Path;
                newObject.body_Type = body_Type;
                newObject.can_kill_or_next_level = can_kill_or_next_level;
                newObject.height = height;
                newObject.width = width;
                newObject.texture_Path = texture_Path;
                newObject.userName = userName;
                newObject.xCoord = xCoordHover;
                newObject.yCoord = yCoordHover;
                newObject.index = lastBodyIndex;
                newObject.isSelected = true;
                
                BSXMLNode newNode = new BSXMLNode();
                newNode.nodeValue.Add(body_Type.ToString());
                newNode.nodeValue.Add(texture_Path);
                newNode.nodeValue.Add(can_kill_or_next_level.ToString());
                newNode.nodeValue.Add(xCoordHover.ToString());
                newNode.nodeValue.Add(yCoordHover.ToString());
                newNode.nodeValue.Add(width.ToString());
                newNode.nodeValue.Add(height.ToString());
                newNode.nodeValue.Add(userName);
                newNode.nodeValue.Add(animation_Path);
                newNode.nodeValue.Add(lastBodyIndex.ToString());

                newXML.secondNodes.Add(newNode);

                lastBodyIndex++;
                theSelectedBodyIndex = listOfObjects.Count;
                newObject.treeNodeIndex = listOfObjects.Count;


                listOfObjects.Add(newObject);
                int indiceTreeView = tvObjects.Nodes.Count;

                tvObjects.Nodes.Add(newObject.userName);
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.body_Type.ToString());
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.texture_Path);
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.can_kill_or_next_level.ToString());
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.xCoord.ToString());
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.yCoord.ToString());
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.width.ToString());
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.height.ToString());
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.animation_Path);
                tvObjects.Nodes[indiceTreeView].Nodes.Add(newObject.index.ToString());

                tvObjects.SelectedNode = tvObjects.Nodes[theSelectedBodyIndex];

                ///xCoordHover = (int)(e.X / ScaleSize);
                ///yCoordHover = (int)((panelGame.Height - e.Y) / ScaleSize);
                panelGame.Invalidate();
                ///MessageBox.Show(xCoordHover + " " + yCoordHover);
            }
        }
        

        private void btnNewObject_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < listOfObjects.Count; i++)
            {
                listOfObjects[i].isSelected = false;
            }
            theSelectedBodyIndex = -1;

            tvObjects.SelectedNode = null;

            tbActionOverPlayer.Text = "0";
            tbUserName.Text = "object";
            tbXCoordinate.Text = "3";
            tbYCoordinate.Text = "3";
            tbWidth.Text = "1";
            tbHeight.Text = "1";
            tbHeight.Text = "1";
            tbBodyType.Text = "0";
            tbTexturePath.Text = "Animations/texture.png";
            tbAnimationName.Text = "textureAnimation";

            body_Type = 0;
            can_kill_or_next_level = 0;
            width = 1;
            height = 1;
            texture_Path = tbTexturePath.Text;
            animation_Path = tbAnimationName.Text;
            userName = tbUserName.Text;
            widthHover = width;
            heightHover = height;


            panelGame.Invalidate();
        }

        private void panelGame_MouseMove(object sender, MouseEventArgs e)
        {
            if (widthHover % 2 == 0)
            {
                moveShiftX = 0;
            }
            else
            {
                moveShiftX = 0.5f;
            }
            
            if (heightHover % 2 == 0)
            {
                moveShiftY = 0;
            }
            else
            {
                moveShiftY = 0.5f;
            }
            xCoordHover = (int)(e.X / ScaleSize) + moveShiftX;
            yCoordHover = (int)((panelGame.Height - e.Y) / ScaleSize) + moveShiftY;
            panelGame.Invalidate();
        }

        private void btnNewLevel_Click(object sender, EventArgs e)
        {
            listOfObjects.Clear();
            panelGame.Invalidate();

            int nrOfItems = tvObjects.Nodes.Count;

            for (int i = 0; i < nrOfItems; i++)
            {
                tvObjects.Nodes[0].Remove();
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void menuNewLevel_Click(object sender, EventArgs e)
        {
            listOfObjects.Clear();
            panelGame.Invalidate();

            int nrOfItems = tvObjects.Nodes.Count;

            for (int i = 0; i < nrOfItems; i++)
            {
                tvObjects.Nodes[0].Remove();
            }
        }

        public void saveLevel(String path)
        {
            try
            {
                richTextBoxLevel.Text = "<?xml version=" + '"' + "1.0" + '"' + " encoding=" + '"' + "UTF-8" + '"' + "?>\n<Level";

                richTextBoxLevel.Text += " name =" + '"' + "Menu Of Levels/Chapter1/The Levels objects/" + path + '"';
                richTextBoxLevel.Text += " boundary_Left =" + '"' + boundary_left.ToString() + '"';
                richTextBoxLevel.Text += " boundary_Down =" + '"' + boundary_down.ToString() + '"';
                richTextBoxLevel.Text += " boundary_Up =" + '"' + boundary_up.ToString() + '"';
                richTextBoxLevel.Text += " boundary_Right =" + '"' + boundary_right.ToString() + '"';
                richTextBoxLevel.Text += " script =" + '"' + hasScript.ToString() + '"' + ">\n\n";

                ///Save first and foremost the hero!!!!**********************************************
                richTextBoxLevel.Text += "  <obstacle>\n";
                for (int i = 0; i < listOfObjects.Count; i++)
                {
                    if (listOfObjects[i].userName.Equals("hero"))
                    {
                        for (int j = 0; j < secondNodes.Count; j++)
                        {
                            richTextBoxLevel.Text += "      <" + secondNodes[j] + ">";

                            richTextBoxLevel.Text += newXML.secondNodes[i].nodeValue[j];

                            richTextBoxLevel.Text += "</" + secondNodes[j] + ">\n";
                        }
                        richTextBoxLevel.Text += "  </obstacle>\n\n";
                    }
                }

                for (int i = 0; i < listOfObjects.Count; i++)
                {
                    if (!listOfObjects[i].userName.Equals("hero"))
                    {
                        richTextBoxLevel.Text += "  <obstacle>\n";
                        for (int j = 0; j < secondNodes.Count; j++)
                        {
                            richTextBoxLevel.Text += "      <" + secondNodes[j] + ">";

                            richTextBoxLevel.Text += newXML.secondNodes[i].nodeValue[j];

                            richTextBoxLevel.Text += "</" + secondNodes[j] + ">\n";
                        }

                        richTextBoxLevel.Text += "  </obstacle>\n\n";
                    }
                }

                richTextBoxLevel.Text += "</Level>";
                richTextBoxLevel.SaveFile(path, RichTextBoxStreamType.PlainText);
                
                this.pbSave.Image = global::BrainStorm_Studios_Game_Engine_Level_Creator.Properties.Resources.bullet_accept;
                MessageBox.Show("Saved: " + path);
            }
            catch
            {
                MessageBox.Show("Error while saving the file!");
                this.pbSave.Image = global::BrainStorm_Studios_Game_Engine_Level_Creator.Properties.Resources.bullet_error;
            }
        }

        private void menuLoadLevel_Click(object sender, EventArgs e)
        {

        }

        private void menuSave_Click(object sender, EventArgs e)
        {
            if (tbLevelName.Text != "")
            {
                saveLevel("Menu Of Levels/Chapter1/The Levels objects/" + tbLevelName.Text + ".xml");
            }
        }

        private void menuSaveAs_Click(object sender, EventArgs e)
        {

        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (tbLevelName.Text != "")
            {
                saveLevel("Menu Of Levels/Chapter1/The Levels objects/" + tbLevelName.Text + ".xml");
            }
        }

        private void tbBodyType_TextChanged(object sender, EventArgs e)
        {
            modifiedObjectOrLevel = true;
            lblLevelUpdated.Text = "Level Updated: false";
        }

        private void btnRemoveObject_Click(object sender, EventArgs e)
        {
            bool canRemove = false;
            int treeViewIndex = 0;
            if(theSelectedBodyIndex != -1)
            {
                if (listOfObjects[theSelectedBodyIndex].isSelected == true)
                {
                    treeViewIndex = listOfObjects[theSelectedBodyIndex].treeNodeIndex;
                    canRemove = true;
                    listOfObjects.Remove(listOfObjects[theSelectedBodyIndex]);
                    theSelectedBodyIndex = -1;
                    ///break;
                }
            }
            for (int i = 0; i < listOfObjects.Count; i++)
            {
                listOfObjects[i].isSelected = false;
            }

            if (canRemove == true)
            {
                tvObjects.Nodes[treeViewIndex].Remove();
            }
            panelGame.Invalidate();
        }




    }
}
