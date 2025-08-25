using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class FFBConstant : IFFBForce
    {
        public double Force { get; set; }

        public delegate double ForceFunction();
        public ForceFunction forceDelegate = Zero;

        public static double Zero()
        {
            return 0;
        }
        public double currentForce()
        {
            return Force;
        }
        public FFBConstant(double force) 
        {
            forceDelegate = currentForce;
        }

        public double CalcForce(double measuredPosition, double dt)
        {
            return forceDelegate();
        }
    }
}
