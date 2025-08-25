using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal interface IFFBForce
    {
        public double CalcForce(double measuredPosition, double dt);
    }
}
