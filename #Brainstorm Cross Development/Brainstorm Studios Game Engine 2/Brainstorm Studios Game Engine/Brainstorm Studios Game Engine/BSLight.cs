using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Brainstorm_Studios_Game_Engine
{
    public enum LightType
    {
        Point,
        Spot
    }

    public abstract class PBLight
    {
        protected float _initialPower;

        public Vector3 Position { get; set; }
        public Vector4 Color;
        public string ScriptName;
        public Color PureColor { get { return new Color((int)(Color.X * 255f), (int)(Color.Y * 255f), (int)(Color.Z * 255f), (int)(Color.W * 255f)); } }

        [ContentSerializerIgnore]
        public float ActualPower { get; set; }
        public float SpecularPower { get; set; }
        public float Power
        {
            get { return _initialPower; }
            set
            {
                _initialPower = value;
                ActualPower = _initialPower;
            }
        }

        public int LightDecay { get; set; }

        [ContentSerializerIgnore]
        public LightType LightType { get; private set; }

        [ContentSerializer(Optional = true)]
        public bool IsEnabled { get; set; }

        [ContentSerializer(Optional = true)]
        public Vector3 Direction { get; set; }
        public float Angle;

        protected PBLight(LightType lightType)
        {
            LightType = lightType;
        }

        public void EnableLight(bool enabled, float timeToEnable)
        {
            IsEnabled = enabled;
        }

        public virtual void Update(GameTime gameTime)
        {
            if (!IsEnabled) return;
        }

        protected void CopyBaseFields(PBLight light)
        {
            light.Color = this.Color;
            light.IsEnabled = this.IsEnabled;
            light.LightDecay = this.LightDecay;
            light.LightType = this.LightType;
            light.Position = this.Position;
            light.Power = this.Power;
        }

        public abstract PBLight DeepCopy();

    }
}