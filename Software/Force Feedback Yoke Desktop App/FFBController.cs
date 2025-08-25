using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class FFBController
    {
        public bool Enable { get; set; }
        public double Gain { get; set; }
        public double MaxForce { get; set; }
        public double Travel { get; set; }
        public double TravelLimitStrength { get; set; }
        public List<IFFBForce> Forces { get; set; }

        public FFBController()
        {
            Enable = false;
            Gain = 0; 
            MaxForce = 0;
            Travel = 100;
            TravelLimitStrength = 0;
            Forces = new List<IFFBForce>();
        }

        public double CalcForces(double measuredPosition, double dt)
        {
            if (!Enable)
            {
                return 0;
            }

            // Handle travel end stops motor strength
            //if (measuredPosition < -Travel / 2)
            //{
            //    return TravelLimitStrength;
            //}
            //else if (measuredPosition > Travel / 2)
            //{
            //    return -TravelLimitStrength;
            //}

            double netForce = 0;
            foreach (IFFBForce f in Forces)
            {
                netForce += f.CalcForce(measuredPosition, dt);
            }

            double scaledNetForce = netForce * Gain;
            //Console.WriteLine("Unclamped Force: {0}", scaledNetForce);
            return Math.Clamp(scaledNetForce, -MaxForce, MaxForce);
        }
    }
}
