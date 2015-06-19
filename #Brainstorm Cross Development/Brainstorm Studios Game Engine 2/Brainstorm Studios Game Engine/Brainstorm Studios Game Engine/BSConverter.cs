using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Brainstorm_Studios_Game_Engine
{
    class BSConverter
    {
        const float toMeters = 1 / 64f;
        const float toPixels = 64f;

        public static Vector2 PixelToMeter(Vector2 v)
        {
            return v * toMeters;
        }
        public static Vector2 MeterToPixel(Vector2 v)
        {
            return v * toPixels;
        }
        public static float MeterToPixel(float p)
        {
            return p * toPixels;
        }
        public static float PixelToMeter(float p)
        {
            return p * toMeters;
        }

        public static Vector3 MeterToPixel(Vector3 v3)
        {
            return v3 * toPixels;
        }
    }
}
