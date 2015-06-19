using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace BrainStorm_Studios_Game_Engine_Level_Creator
{

    public class BSPanel
    {
        public BSPanel()
        {

        }
    }

    public class BSObject
    {
        public float xCoord, yCoord, width, height;
        public int can_kill_or_next_level, index, body_Type, treeNodeIndex;
        public String texture_Path, animation_Path, userName;
        public bool isSelected;
        public int animationIndex;
    }

    public class BSXMLNode
    {
        public List<String> attributes = new List<String>();
        public List<String> nodeValue = new List<String>();
    }

    public class BSXMLStruct
    {
        public List<BSXMLNode> secondNodes = new List<BSXMLNode>();
        public List<String> headAttributes = new List<String>();
    }
}
