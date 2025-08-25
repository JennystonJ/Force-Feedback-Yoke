using MSFSForceFeedbackController.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController.FFBEffects
{
    internal class FFBEffect
    {
        public FFBForce[] Forces { get; protected set; }

        protected FFBEffect()
        {
            Forces = Array.Empty<FFBForce>();
        }
    }
}
