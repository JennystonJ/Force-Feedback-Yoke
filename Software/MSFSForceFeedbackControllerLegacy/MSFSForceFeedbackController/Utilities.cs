using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController
{
    public class Utilities
    {
        public static double Scale(double value, double inMin, double inMax, double outMin, double outMax)
        {
            return ((value - inMin) * (outMax - outMin)) / (inMax - inMin) + outMin;
        }
    }
}
