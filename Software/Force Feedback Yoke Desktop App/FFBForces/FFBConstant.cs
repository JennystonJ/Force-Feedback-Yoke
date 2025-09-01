using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBForces
{
    internal class FFBConstant : FFBForce
    {
        public double Force { get; set; }

        public delegate double ForceFunction();
        public ForceFunction forceDelegate = Zero;

        public static double Zero()
        {
            return 0;
        }
        public double CurrentForce()
        {
            return Force;
        }
        public FFBConstant()
        {
            forceDelegate = CurrentForce;
        }
        public FFBConstant(double force) 
        {
            Force = force;
            forceDelegate = CurrentForce;
        }

        public override ForceSet CalcForce()
        {
            return new ForceSet
            {
                Constant = forceDelegate(),
                Spring = 0.0,
                Damper = 0.0
            };
        }
    }
}
