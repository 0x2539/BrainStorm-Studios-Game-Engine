using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework;
using System.IO;

namespace Brainstorm_Studios_Game_Engine
{
    public struct AnimationFrame
    {
        public Texture2D texture;
        public TimeSpan TTLMl;
    }

    class BSAnimation
    {
        Texture2D texture;
        int height;
        int width;
        int bigHeight;
        int bigWidth;
        bool repeat = false;
        bool Active = false;
        int indexX;
        int indexY;
        int maxIndex;
        TimeSpan time;
        TimeSpan lastTime;
        private float angle;
        int cX, cY;
        public bool Finished=false;

        public int Height;
        public int Width;

        int nrFirstCycle;
        int nrSecondCycle;
        int nrThirdCycle;
        int firstTime;
        int secondTime;
        int thirdTime;

        AnimationFrame[,] textures;

        public BSAnimation(ContentManager content,string directory, int nrFirstCycle, int nrSecondCycle, int nrThirdCycle, int firstTime, int secondTime, int thirdTime, int loop)
        {
            Active = true;

            this.nrFirstCycle = nrFirstCycle;
            this.nrSecondCycle = nrSecondCycle;
            this.nrThirdCycle = nrThirdCycle;
            this.firstTime = firstTime;
            this.secondTime = secondTime;
            this.thirdTime = thirdTime;

            textures=new AnimationFrame[3,nrFirstCycle+nrSecondCycle+nrThirdCycle];
            for (int i = 0; i < nrFirstCycle; i++)
            {
                textures[0, i].texture = content.Load<Texture2D>("Animations\\playerAnimation\\" + directory + "\\playerTexture" + i.ToString());
                textures[0, i].TTLMl = TimeSpan.FromMilliseconds(firstTime);
                Height = textures[0, i].texture.Height;
                Width = textures[0, i].texture.Width;
            }
            for (int i = nrFirstCycle; i < nrFirstCycle+nrSecondCycle; i++)
            {
                textures[1, i-nrFirstCycle].texture = content.Load<Texture2D>("Animations\\playerAnimation\\" + directory + "\\playerTexture" + i.ToString());
                textures[1, i-nrFirstCycle].TTLMl = TimeSpan.FromMilliseconds(secondTime);
                Height = textures[1, i - nrFirstCycle].texture.Height;
                Width = textures[1, i - nrFirstCycle].texture.Width;
            }
            for (int i = nrSecondCycle+nrFirstCycle; i < nrFirstCycle+nrSecondCycle+nrThirdCycle; i++)
            {
                textures[2, i - (nrSecondCycle + nrFirstCycle)].texture = content.Load<Texture2D>("Animations\\playerAnimation\\" + directory + "\\playerTexture" + i.ToString());
                textures[2, i - (nrSecondCycle + nrFirstCycle)].TTLMl = TimeSpan.FromMilliseconds(thirdTime);
                Height = textures[2, i - (nrSecondCycle + nrFirstCycle)].texture.Height;
                Width = textures[2, i - (nrSecondCycle + nrFirstCycle)].texture.Width;

            }
            

            if (loop == 1)
                this.repeat = true;
            else
                this.repeat = false;

        }

       public void Update(GameTime gameTime)
        {
            if (Active)
            {
                switch (indexY)
                {

                    case 0:
                        if (nrFirstCycle > 0)
                        {

                            if (gameTime.TotalGameTime - lastTime > textures[indexY, indexX].TTLMl)
                            {
                                lastTime = gameTime.TotalGameTime;
                                indexX++;
                                if (indexX >= nrFirstCycle)
                                {
                                    indexY = 1;
                                    indexX = 0;
                                    if (nrSecondCycle == 0)
                                    {
                                        indexY = 2;
                                        if (nrThirdCycle == 0)
                                            Active = false;
                                    }
                                }
                            }
                        }
                        else
                        {
                            indexY = 1;
                            
                        }
                        break;
                    case 1:
                        if (nrSecondCycle > 0)
                        {

                            if (gameTime.TotalGameTime - lastTime > textures[indexY, indexX].TTLMl)
                            {
                                lastTime = gameTime.TotalGameTime;
                                indexX++;
                                if (indexX >= nrSecondCycle)
                                {
                                    if (repeat)
                                        indexX = 0;
                                    else
                                    {
                                        indexY = 2;
                                        indexX = 0;
                                    }
                                }
                            }
                        }
                        else
                            indexY = 2;
                        break;
                    case 2:
                        if (nrThirdCycle > 0)
                        {

                            if (gameTime.TotalGameTime - lastTime > textures[indexY, indexX].TTLMl)
                            {
                                lastTime = gameTime.TotalGameTime;
                                indexX++;
                                if (indexX > nrFirstCycle)
                                {
                                    Active = false;
                                }
                            }
                        }
                        else
                            Active = false;
                        break;
                }
            }
        }
       public void Play()
       {
           Active = true;
           indexX = 0;
           indexY = 0;
       }
       internal void Draw(SpriteBatch spriteBatch, Vector2 position, float rot)
       {
           if (Active)
           {
               Vector2 origin=new Vector2(textures[indexY,indexX].texture.Width/2f,textures[indexY,indexX].texture.Height/2f);
               spriteBatch.Draw(textures[indexY, indexX].texture, position, null, Color.White, rot, origin,1f,SpriteEffects.None,0f);
           }
       }
       internal void Draw(SpriteBatch spriteBatch, Rectangle rectangle, float rot)
       {
           if (Active)
           {
                Vector2 origin = new Vector2(textures[indexY, indexX].texture.Width / 2f, textures[indexY, indexX].texture.Height / 2f);
               spriteBatch.Draw(textures[indexY, indexX].texture, rectangle, null, Color.White, rot, origin, SpriteEffects.None, 0f);
           }
       }
    }
}
