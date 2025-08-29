using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBForces
{
    internal class FFBSpring : FFBForce
    {
        public double Offset { get; set; }
        public double Strength { get; set; }


        public delegate double StrengthFunction();
        public StrengthFunction strengthDelegate = Zero;

        public delegate double OffsetFunction();
        public OffsetFunction offsetDelegate = Zero;

        private static double Zero()
        {
            return 0;
        }

        private double CurrentStrength()
        {
            return Strength;
        }
        private double CurrentOffset()
        {
            return Offset;
        }
        public FFBSpring()
        {
            strengthDelegate = CurrentStrength;
            offsetDelegate = CurrentOffset;
        }

        public FFBSpring(double strength, double offset)
        {
            Offset = offset;
            Strength = strength;
            strengthDelegate = CurrentStrength;
            offsetDelegate = CurrentOffset;

        }

        public override ForceSet CalcForce(double measuredPosition, double dt)
        {
            return new ForceSet
            {
                Constant = offsetDelegate(),
                Spring = strengthDelegate(),
                Damper = 0.0
            };
        }
    }
}
