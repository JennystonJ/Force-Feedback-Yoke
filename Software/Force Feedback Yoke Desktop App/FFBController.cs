using Force_Feedback_Yoke_Desktop_App.FFBEffects;
using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class FFBController
    {
        public bool Enable { get; set; }
        public double Gain { get; set; }
        public double MaxForce { get; set; }
        public double Travel { get; set; }
        public List<FFBEffect> Effects { get; set; }

        public FFBController()
        {
            Enable = false;
            Gain = 0; 
            MaxForce = 0;
            Travel = 100;
            Effects = new List<FFBEffect>();
        }

        public ForceSet CalcForces()
        {
            if (!Enable)
            {
                return new ForceSet();
            }

            ForceSet netForceSet = new ForceSet();
            foreach (FFBEffect effect in Effects)
            {
                foreach(FFBForce force in effect.Forces)
                {
                    netForceSet += force.CalcForce();
                }
            }

            return netForceSet * Gain;
        }
    }
}
