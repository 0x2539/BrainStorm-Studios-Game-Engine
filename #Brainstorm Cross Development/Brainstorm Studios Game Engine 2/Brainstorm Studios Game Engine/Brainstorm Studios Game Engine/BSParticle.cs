using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Brainstorm_Studios_Game_Engine
{
    class PBParticle
    {
        public Texture2D Texture { get; set; }        // The texture that will be drawn to represent the particle
        public Vector2 Position { 
                                  get { return position; }
                                  set { this.position = value; }
                                }        // The current position of the particle    
        public Vector2 position;
        public Vector2 Velocity { get; set; }        // The speed of the particle at the current instance
        public float Angle { get; set; }            // The current angle of rotation of the particle
        public float AngularVelocity { get; set; }    // The speed that the angle is changing
        public Color Color { get; set; }            // The color of the particle
        public float Size { get; set; }                // The size of the particle
        public int TTL { get; set; }                    //"Time to Live"
        Color ColorN = Color.MediumPurple;
        public PBParticle(Texture2D texture, Vector2 position, Vector2 velocity,
            float angle, float angularVelocity, Color color, float size, int ttl)
        {
            Texture = texture;
            this.position = position;
            Velocity = velocity;
            Angle = angle;
            AngularVelocity = angularVelocity;
            Color = color;
            Size = size;
            TTL = ttl;
        }
        public void Update(float size=0f)
        {
            TTL--;
            position += Velocity;
            Angle += AngularVelocity;
            Size -= size;
        }
        public void Update(Vector2 newPos)
        {
            TTL--;
            position = newPos;
            
        }
        public void DrawC(SpriteBatch spriteBatch)
        {
            Rectangle sourceRectangle = new Rectangle(0, 0, Texture.Width, Texture.Height);
            Vector2 origin = new Vector2(Texture.Width / 2, Texture.Height / 2);

            spriteBatch.Draw(Texture, position, sourceRectangle, Color,
                Angle, origin, Size, SpriteEffects.None,0f);
        }
        public void DrawN(SpriteBatch spriteBatch)
        {
            Rectangle sourceRectangle = new Rectangle(0, 0, Texture.Width, Texture.Height);
            Vector2 origin = new Vector2(Texture.Width / 2, Texture.Height / 2);

            spriteBatch.Draw(Texture, position, sourceRectangle, ColorN,
                Angle, origin, Size, SpriteEffects.None, 0f);
        }
    }
}
