using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using FarseerPhysics.Dynamics;
using FarseerPhysics.Factories;

namespace Brainstorm_Studios_Game_Engine
{
    class BSBody
    {
        Texture2D texture;
        public Body body;
        public float height;
        public float width;

        public Vector2 Origin
        {
            get { return new Vector2(texture.Width/2f,texture.Height/2f); }
        }

        public Vector2 PhPosition
        {
            get
            {
                return body.Position;
            }
            set
            {
                body.Position = value;
            }
        }
        public Vector2 Position
        {
            get { return BSConverter.MeterToPixel(body.Position); }
        }

        public Rectangle Rectangle
        {
            get { return new Rectangle((int)(Position.X),(int)(Position.Y),(int)BSConverter.MeterToPixel(width),(int)BSConverter.MeterToPixel(height)); } 
        }

        public BSBody(World world,BodyType type ,float width, float height)
        {
            this.height = height;
            this.width = width;
            body = BodyFactory.CreateRectangle(world, width, height, 0f);
            body.BodyType = type;
        }
        public BSBody(World world, float width, float height)
        {
            this.height = height;
            this.width = width;
            body=BodyFactory.CreateRectangle(world, width, height, 0f);
            body.BodyType=BodyType.Dynamic;
        }
        public BSBody(World world,Texture2D texture,float width, float height)
        {
            this.texture = texture;
            body = BodyFactory.CreateRectangle(world, width, height,0f);
        }
        public void AttachTexture(Texture2D text)
        {
            texture = text;
        }
        public void Draw(SpriteBatch batch)
        {
            if (texture != null && body != null)
                batch.Draw(texture, Rectangle, null, Color.White, body.Rotation, Origin, SpriteEffects.None,0f);

        }
        public void Draw(SpriteBatch batch, Texture2D texture)
        {
            if (texture != null && body != null)
                batch.Draw(texture, Rectangle, null, Color.White, body.Rotation, Origin, SpriteEffects.None, 0f);

        }

        internal void Update(GameTime gameTime)
        {

        }

        public float Rotation { get { return body.Rotation; } set { body.Rotation = value; } }
    }
}
