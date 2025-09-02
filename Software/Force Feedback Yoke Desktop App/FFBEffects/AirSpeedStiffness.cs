using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
{
    internal class AirSpeedStiffness : FFBEffect
    {
        public double AirSpeed { get; set; }
        public double SpringGain { get; set; }
        public double DamperGain { get; set; }

        private FFBSpring springForce;
        private FFBDamper damperForce;
        public AirSpeedStiffness(double springGain, double damperGain=0.1)
        {
            SpringGain = springGain;
            DamperGain = damperGain;

            springForce = new FFBSpring();
            damperForce = new FFBDamper();

            Forces = [springForce, damperForce];

            // Ensure delegates start disabled
            Enabled = false;
            OnEnabledChanged(false);
        }

        public double AirSpeedStiffnessSpringFunction()
        {
            return SpringGain * AirSpeed * AirSpeed;
        }

        public double AirSpeedStiffnessDamperFunction()
        {
            return DamperGain/1000.0 * AirSpeed;
        }

        protected override void OnEnabledChanged(bool enabled)
        {
            springForce.strengthDelegate = enabled ? AirSpeedStiffnessSpringFunction : Zero;
            damperForce.strengthDelegate = enabled ? AirSpeedStiffnessDamperFunction : Zero;
        }

        public override void LoadParameters(Dictionary<string, double> parameters)
        {
            SpringGain = parameters["spring_gain"];
            DamperGain = parameters["damper_gain"];
        }

        public override Dictionary<string, double> SaveParameters()
        {
            return new Dictionary<string, double>
            {
                { "spring_gain", SpringGain },
                { "damper_gain", DamperGain },
            };
        }
    }
}
