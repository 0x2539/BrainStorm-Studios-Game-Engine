using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Brainstorm_Studios_Game_Engine
{
    class BSTexture
    {
        void renderSomeBody(SpriteBatch batch, float coordX, float coordY, float coordZ,
            float angleX, float angleY, float angleZ, Texture2D texture, Color color,
            float scaleX, float scaleY, float scaleZ)
        {
            Vector2 pos = new Vector2(coordX, coordY);

            batch.Draw(texture, pos, null, color, angleX, Vector2.Zero, new Vector2(scaleX, scaleY), SpriteEffects.None, 0f);

        }
    }
}
