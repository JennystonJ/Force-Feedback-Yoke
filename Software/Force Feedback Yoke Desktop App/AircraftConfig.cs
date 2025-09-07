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
        public FFBControllerConfig Pitch {  get; set; } = new();
        public FFBControllerConfig Roll { get; set; } = new();
        public List<EffectConfig> PitchEffects { get; set; } = [];
        public List<EffectConfig> RollEffects { get; set; } = [];
    }
}
