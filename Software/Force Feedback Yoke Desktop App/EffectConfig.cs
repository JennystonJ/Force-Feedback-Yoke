using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class EffectConfig
    {
        public string Type { get; set; } = "";
        public Dictionary<string, double> Parameters { get; set; } = new Dictionary<string, double>();
    }
}
