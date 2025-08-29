using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
{
    internal class ElevatorWeight : FFBEffect
    {
        public double Weight { get; set; }
        public double EngineRPM { get; set; }
        public double EngineRPMStrength { get; set; }
        public double DamperGain { get; set; }

        private FFBSpring springForce;
        private FFBConstant constantForce;
        private FFBDamper damperForce;

        public ElevatorWeight(double weight, double engineRPMStrength, double damperGain=0.025)
        {
            Weight = weight;
            EngineRPMStrength = engineRPMStrength;
            DamperGain = damperGain;

            springForce = new FFBSpring();
            springForce.strengthDelegate = ElevatorWeightCenterStrengthFunction;

            constantForce = new FFBConstant(weight);
            constantForce.forceDelegate = ElevatorWeightFunction;

            damperForce = new FFBDamper();
            damperForce.strengthDelegate = ElevatorWeightDamperFunction;

            Forces = new FFBForce[] { springForce, constantForce, damperForce };
            

        }
        public double ElevatorWeightCenterStrengthFunction()
        {
            return EngineRPMStrength/1000.0 * Math.Sqrt(EngineRPM);
        }

        public double ElevatorWeightFunction()
        {
            return -Weight;
        }
        public double ElevatorWeightDamperFunction()
        {
            return DamperGain / 1000.0 * Math.Sqrt(EngineRPM);
        }
    }
}
