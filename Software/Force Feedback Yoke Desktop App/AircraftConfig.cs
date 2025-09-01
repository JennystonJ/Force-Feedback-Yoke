using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class AircraftConfig
    {
        public string Name { get; set; } = "";
        public double PitchTravelMM { get; set; }
        public double RollTravelDeg {  get; set; }
        public double PitchGain { get; set; }
        public List<EffectConfig> PitchEffects { get; set; } = new List<EffectConfig>();
        public double RollGain { get; set; }
        public List<EffectConfig> RollEffects { get; set; } = new List<EffectConfig>();
    }
}
