using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    public class Utilities
    {
        public static double Scale(double value, double inMin, double inMax, double outMin, double outMax)
        {
            return ((value - inMin) * (outMax - outMin)) / (inMax - inMin) + outMin;
        }

        public static decimal Scale(decimal value, decimal inMin, decimal inMax, decimal outMin, decimal outMax)
        {
            return ((value - inMin) * (outMax - outMin)) / (inMax - inMin) + outMin;
        }
    }
}
