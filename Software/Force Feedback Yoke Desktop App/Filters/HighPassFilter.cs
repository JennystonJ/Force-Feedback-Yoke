using System;
using System.Collections.Generic;
using System.Linq;
using System.Resources;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.Filters
{
    internal class HighPassFilter
    {
        private double alpha;
        private double xPrev = 0.0;
        private double yPrev = 0.0;

        public HighPassFilter(double cutoffHz, double samplePeriod)
        {
            double rc = 1.0 / (2.0 * Math.PI * cutoffHz);
            alpha = rc / (rc + samplePeriod);
        }

        public double Update(double x)
        {
            double y = alpha * (yPrev + x - xPrev);
            xPrev = x;
            yPrev = y;
            return y;
        }
    }
}
