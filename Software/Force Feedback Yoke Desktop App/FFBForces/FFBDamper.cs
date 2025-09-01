using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBForces
{
    internal class FFBDamper : FFBForce
    {
        public double Strength { get; set; }
        public delegate double StrengthFunction();
        public StrengthFunction strengthDelegate = Zero;
        public static double Zero()
        {
            return 0;
        }
        public double CurrentStrength()
        {
            return Strength;
        }
        public FFBDamper()
        {
            strengthDelegate = CurrentStrength;
        }

        public FFBDamper(double strength)
        {
            Strength = strength;
            strengthDelegate = CurrentStrength;
        }

        public override ForceSet CalcForce()
        {
            return new ForceSet
            {
                Constant = 0.0,
                Spring = 0.0,
                Damper = strengthDelegate()
            };
        }
    }
}
