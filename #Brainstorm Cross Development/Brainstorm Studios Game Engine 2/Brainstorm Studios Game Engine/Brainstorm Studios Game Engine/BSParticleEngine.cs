using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Brainstorm_Studios_Game_Engine
{
    class PBParticleEngine
    {
        List<PBParticle> particles;
        private Random random;
        public Vector2 EmitterLocation { get; set; }
        public Vector2 EmitterLocation2 { get; set; }
        private List<Texture2D> textures;
        int TTL;
        public PBParticleEngine(List<Texture2D> textures, Vector2 location,int ttl)
        {
            EmitterLocation = location;
            this.textures = textures;
            this.particles = new List<PBParticle>();
            random = new Random();
            TTL = ttl;
        }

        public void Update()
        {
            int total =1;

            for (int i = 0; i < total; i++)
            {
                particles.Add(GenerateNewParticle());
            }

            for (int particle = 0; particle < particles.Count; particle++)
            {
                particles[particle].Update();
                if (particles[particle].TTL <= 0)
                {
                    particles.RemoveAt(particle);
                    particle--;
                }
            }
        }
        public void Update(Vector2 pos, Color col,float angle,float size=0)
        {
            int total = 1;

            for (int i = 0; i < total; i++)
            {
                particles.Add(GenerateNewParticle(EmitterLocation, pos, col,angle));
                if(EmitterLocation2!=Vector2.Zero)
                particles.Add(GenerateNewParticle(EmitterLocation2, pos, col,angle));
            }

            for (int particle = 0; particle < particles.Count; particle++)
            {
                particles[particle].Update(size);
                if (particles[particle].TTL <= 0)
                {
                    particles.RemoveAt(particle);
                    particle--;
                }
            }
        }
        private PBParticle GenerateNewParticle()
        {
            Texture2D texture = textures[random.Next(textures.Count)];
            Vector2 position = EmitterLocation;
            Vector2 velocity = new Vector2(
                                    1f * (float)(random.NextDouble() * 2 - 1),
                                    1f * (float)(random.NextDouble() * 2 - 1));
            float angle = 0;
            float angularVelocity = 0.1f * (float)(random.NextDouble() * 2 - 1);
            Color color = new Color(
                        (float)random.NextDouble(),
                        (float)random.NextDouble(),
                        (float)random.NextDouble());
            float size = (float)random.NextDouble();
            int ttl = 20 + random.Next(40);

            return new PBParticle(texture, position, velocity, angle, angularVelocity, color, size, ttl);
        }
        private PBParticle GenerateNewParticle(Vector2 emiter,Vector2 vel,Color col,float angle)
        {
            Texture2D texture = textures[random.Next(textures.Count)];
            Vector2 position = emiter;
            Vector2 velocity = vel;
            float angularVelocity = 0f;
            Color color = col;
            float size = 0.6f;

            return new PBParticle(texture, position, velocity, angle, angularVelocity, color, size, TTL);
        }

        public void DrawC(SpriteBatch spriteBatch)
        {
            for (int index = 0; index < particles.Count; index++)
            {
                particles[index].DrawC(spriteBatch);
            }
        }
        public void DrawN(SpriteBatch spriteBatch)
        {
            for (int index = 0; index < particles.Count; index++)
            {
                particles[index].DrawN(spriteBatch);
            }
        }
    }
}
