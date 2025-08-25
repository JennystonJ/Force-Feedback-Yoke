using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class FFBSpringForce : IFFBForce
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

        private double currentStrength()
        {
            return Strength;
        }
        private double currrentOffset()
        {
            return Offset;
        }
        public FFBSpringForce()
        {
            strengthDelegate = currentStrength;
            offsetDelegate = currrentOffset;
        }

        public FFBSpringForce(double strength, double offset)
        {
            Offset = offset;
            Strength = strength;
        }

        public double CalcForce(double measuredPosition, double dt)
        {
            double error = offsetDelegate() - measuredPosition;
            return error * strengthDelegate();
        }
    }
}
