using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
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
