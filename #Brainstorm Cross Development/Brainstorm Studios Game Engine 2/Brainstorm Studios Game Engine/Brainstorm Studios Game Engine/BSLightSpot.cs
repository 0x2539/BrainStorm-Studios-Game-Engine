using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Brainstorm_Studios_Game_Engine
{
    class SpotLight : PBLight
    {
        public SpotLight()
            : base(LightType.Spot)
        {

        }
        public override PBLight DeepCopy()
        {
            var newLight = new SpotLight();
            CopyBaseFields(newLight);

            return newLight;
        }
    }
}
