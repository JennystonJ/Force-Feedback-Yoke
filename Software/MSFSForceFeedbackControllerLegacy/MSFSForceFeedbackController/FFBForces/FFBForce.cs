using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController.FFBForces
{
    internal abstract class FFBForce
    {
        public abstract ForceSet CalcForce(double measuredPosition, double dt);
    }
}
