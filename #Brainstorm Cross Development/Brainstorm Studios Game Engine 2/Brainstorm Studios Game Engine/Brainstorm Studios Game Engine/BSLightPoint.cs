using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Brainstorm_Studios_Game_Engine
{
    public class PointLight : PBLight
    {
        public PointLight()
            : base(LightType.Point)
        {

        }

        public override PBLight DeepCopy()
        {
            var newLight = new PointLight();
            CopyBaseFields(newLight);

            return newLight;
        }

    }
}
