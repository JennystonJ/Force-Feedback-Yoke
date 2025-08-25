using MSFSForceFeedbackController.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController
{
    internal class FFBController
    {
        public bool Enable { get; set; }
        public double Gain { get; set; }
        public double MaxForce { get; set; }
        public double Travel { get; set; }
        public double TravelLimitStrength { get; set; }
        public List<FFBForce> Forces { get; set; }

        public FFBController()
        {
            Enable = false;
            Gain = 0; 
            MaxForce = 0;
            Travel = 100;
            TravelLimitStrength = 0;
            Forces = new List<FFBForce>();
        }

        public ForceSet CalcForces(double measuredPosition, double dt)
        {
            if (!Enable)
            {
                return new ForceSet();
            }

            ForceSet netForceSet = new ForceSet();
            foreach (FFBForce f in Forces)
            {
                netForceSet += f.CalcForce(measuredPosition, dt);
            }

            return netForceSet * Gain;
        }
    }
}
