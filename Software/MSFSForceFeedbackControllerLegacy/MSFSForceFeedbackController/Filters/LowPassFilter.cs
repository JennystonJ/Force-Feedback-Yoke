using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController.Filters
{
    internal class LowPassFilter
    {
        private double alpha;
        private double y = 0;
        
        public LowPassFilter(double cutOffHz, double samplePeriod)
        {
            double rc = 1.0/(2*Math.PI*cutOffHz);
            alpha = samplePeriod / (rc + samplePeriod);
        }

        public double Update(double x)
        {
            y += alpha * (x - y);
            return y;
        }
    }
}
