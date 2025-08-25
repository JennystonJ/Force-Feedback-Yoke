using MSFSForceFeedbackController.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController.FFBEffects
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
            springForce.strengthDelegate = AirSpeedStiffnessSpringFunction;
            damperForce.strengthDelegate = AirSpeedStiffnessDamperFunction;

            Forces = new FFBForce[] { springForce, damperForce };
        }

        public double AirSpeedStiffnessSpringFunction()
        {
            return SpringGain * AirSpeed * AirSpeed;
        }

        public double AirSpeedStiffnessDamperFunction()
        {
            return DamperGain/10000.0 * Math.Sqrt(AirSpeed);
        }

    }
}
