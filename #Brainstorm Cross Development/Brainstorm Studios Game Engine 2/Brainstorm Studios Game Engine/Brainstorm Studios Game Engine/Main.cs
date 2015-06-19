using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using FarseerPhysics.Dynamics;
using System.Xml.Linq;
using FarseerPhysics.Factories;
using System.IO;
using System.Globalization;

namespace Brainstorm_Studios_Game_Engine
{
    public class Main : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Texture2D test;
        BSCamera Camera;
        BSAnimation animation;
        BSInput input;
        World world;
        BSBody Player;
        SpriteFont font;
        List<BSBody> bodies = new List<BSBody>();
        public Main()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            Window.AllowUserResizing = true;
            Window.ClientSizeChanged += Window_ClientSizeChanged;
            this.IsMouseVisible = true;
        }

        protected override void Initialize()
        {
            Camera = new BSCamera(GraphicsDevice.Viewport);
            input = new BSInput();
            Camera.position = new Vector2(0, 5.2f);
            world = new World(new Vector2(0,0));
            base.Initialize();
        }

        protected override void LoadContent()
        {
            spriteBatch = new SpriteBatch(GraphicsDevice);
            test=Content.Load<Texture2D>("Animations\\coin2");
            animation = new BSAnimation(Content, "right", 0, 12, 0, 0, 50, 0, 1);
            font = Content.Load<SpriteFont>("font");
            LoadLevel("Content\\level1.xml");
        }

        protected override void UnloadContent()
        {
        }

        List<BSAnimation> playerAnimations = new List<BSAnimation>();

        void LoadLevel(string xmlpath)
        {
            XElement xml = XElement.Load(xmlpath);
            XElement[] elem=xml.Elements("obstacle").ToArray();
            foreach (XElement el in elem)
            {
                XElement[] e = el.Elements().ToArray();
                int bodyType = int.Parse(e[0].Value);
                string texture_path = e[1].Value;
                int kill_or_next_level = int.Parse(e[2].Value);
                float xCoord = float.Parse(e[3].Value,CultureInfo.InvariantCulture);
                float yCoord = -float.Parse(e[4].Value,CultureInfo.InvariantCulture);
                float width = float.Parse(e[5].Value);
                float height = float.Parse(e[6].Value);
                string Animation_name = e[8].Value;
                string userName = e[7].Value;
                int Index = int.Parse(e[9].Value);
                if (userName == "hero")
                {
                    Player = new BSBody(world, width, height);
                    Player.PhPosition = new Vector2(xCoord, yCoord);
                    using (StreamReader reader = new StreamReader("Content\\Animations\\playerAnimation\\animations.txt"))
                    {
                        int n = int.Parse(reader.ReadLine());
                        for (int i = 1; i <= n; i++)
                        {
                            BSAnimation anim;
                            string[] split = reader.ReadLine().Trim().Split(' ');
                            anim = new BSAnimation(Content, split[9],
                                int.Parse(split[0]), int.Parse(split[1]), int.Parse(split[2]),
                                int.Parse(split[3]), int.Parse(split[4]), int.Parse(split[5]),
                                int.Parse(split[7]));
                            playerAnimations.Add(anim);
                            
                        }
                    }
                    Camera.Follow(Player.body);

                }
                else
                switch (bodyType)
                {
                    case 0:
                        BSBody temp;
                        temp = new BSBody(world,BodyType.Static,width,height);
                        temp.PhPosition = new Vector2(xCoord, yCoord);
                        string processedPath=texture_path.Replace(".png","");
                        Texture2D tempT = Content.Load<Texture2D>(processedPath);
                        temp.AttachTexture(tempT);
                        bodies.Add(temp);
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5: 
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8: 
                        break;
                    case 9:
                        break;
                }

            }
        }

        void Window_ClientSizeChanged(object sender, EventArgs e)
        {

            Camera = new BSCamera(GraphicsDevice.Viewport);
            Camera.Follow(Player.body);
        }

        protected override void Update(GameTime gameTime)
        {

            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();
            world.Step((float)gameTime.ElapsedGameTime.TotalMilliseconds * 0.001f);
            input.Update(gameTime);
            
            PlayerIndex playerIndex;
            if (input.IsKeyPress(Keys.S,PlayerIndex.One, out playerIndex))
                Player.body.ApplyLinearImpulse(Vector2.UnitY);
            if (input.IsKeyPress(Keys.W, PlayerIndex.One, out playerIndex))
                Player.body.ApplyLinearImpulse(-Vector2.UnitY);
            if (input.IsKeyPress(Keys.A, PlayerIndex.One, out playerIndex))
                Player.body.ApplyLinearImpulse(-Vector2.UnitX);
            if (input.IsKeyPress(Keys.D, PlayerIndex.One, out playerIndex))
                Player.body.ApplyLinearImpulse(Vector2.UnitX);
            if (input.IsKeyPress(Keys.Space, PlayerIndex.One, out playerIndex))
                Player.body.LinearVelocity = Vector2.Zero;
            if (input.IsNewKeyPress(Keys.D1, PlayerIndex.One, out playerIndex))
                count++;
            if (count > 17)
                count = 0;
            if (input.IsNewKeyPress(Keys.D2, PlayerIndex.One, out playerIndex))
                Camera.View *= -1;
            //foreach (var anim in playerAnimations)
            //    anim.Update(gameTime);
            playerAnimations[count].Update(gameTime);
            animation.Update(gameTime);
            float scale = (float)GraphicsDevice.Viewport.Height / (float)(animation.Height * TimesPerScreen);
            Camera.Scale = scale;
            Camera.Update();
            Player.Update(gameTime);
            base.Update(gameTime);
        }

        const int TimesPerScreen = 19;
        int count = 0;
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);
            
            spriteBatch.Begin(SpriteSortMode.Deferred, null, null, null, null, null, Camera.View);
            for (int i = 0; i < 19; i++)
                //animation.Draw(spriteBatch, new Vector2(0,i*animation.Height),0f);
                animation.Draw(spriteBatch, new Rectangle(0, i * animation.Height, animation.Width, animation.Height), 0f);
            //spriteBatch.Draw(test, Vector2.Zero, Color.White);
            foreach (BSBody b in bodies)
                b.Draw(spriteBatch);
            
            playerAnimations[count].Draw(spriteBatch, Player.Rectangle, Player.Rotation);

            spriteBatch.End();

            spriteBatch.Begin();
            spriteBatch.DrawString(font, Player.body.Position.ToString() + " " + Player.body.Rotation.ToString(), Vector2.Zero, Color.Black);
            spriteBatch.End();

            base.Draw(gameTime);
        }
    }
}
