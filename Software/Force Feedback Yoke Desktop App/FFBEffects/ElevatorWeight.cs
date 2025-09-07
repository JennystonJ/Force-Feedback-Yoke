using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
{
    public class ElevatorWeightConfig : FFBEffectConfig
    {
        public double Weight { get; set; }
        public double DamperGain { get; set; }
        public double EngineRPMStrength { get; set; }
    }
    internal class ElevatorWeight : FFBEffect
    {
        public double Weight { get; set; }

        private double _damperGain;
        public double DamperGain 
        { 
            get => _damperGain;
            set
            {
                if (_damperGain != value)
                {
                    _damperGain = value;
                    OnPropertyChanged(this, new PropertyChangedEventArgs(nameof(DamperGain)));
                }
            }
        }

        private double _engineRPMStrength;
        public double EngineRPMStrength 
        { 
            get => _engineRPMStrength;
            set
            {
                if (_engineRPMStrength != value)
                {
                    _engineRPMStrength = value;
                    OnPropertyChanged(this, new PropertyChangedEventArgs(nameof(EngineRPMStrength)));
                }
            }
        }

        public double EngineRPM { get; set; }

        private FFBSpring springForce;
        private FFBConstant constantForce;
        private FFBDamper damperForce;

        public ElevatorWeight()
        {
            Weight = 0;
            EngineRPMStrength = 0;
            DamperGain = 0;

            constantForce = new FFBConstant();
            springForce = new FFBSpring();
            damperForce = new FFBDamper();

            Forces = [springForce, constantForce, damperForce];

            // Ensure delegates start disabled
            Enabled = false;
            OnEnabledChanged(false);
        }

        public ElevatorWeight(double weight, double engineRPMStrength, double damperGain=0.025)
        {
            Weight = weight;
            EngineRPMStrength = engineRPMStrength;
            DamperGain = damperGain;

            constantForce = new FFBConstant(weight);
            springForce = new FFBSpring();
            damperForce = new FFBDamper();

            Forces = [springForce, constantForce, damperForce];

            // Ensure delegates start disabled
            Enabled = false;
            OnEnabledChanged(false);
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

        protected override void OnEnabledChanged(bool enabled)
        {
            constantForce.forceDelegate = enabled ? ElevatorWeightFunction : Zero;
            springForce.strengthDelegate = enabled ? ElevatorWeightCenterStrengthFunction : Zero;
            damperForce.strengthDelegate = enabled ? ElevatorWeightDamperFunction : Zero;
        }

        public override void LoadParameters(Dictionary<string, double> parameters)
        {
            Weight = parameters["weight"];
            EngineRPMStrength = parameters["engine_rpm_strength"];
            DamperGain = parameters["damper_gain"];
        }

        public override Dictionary<string, double> SaveParameters()
        {
            return new Dictionary<string, double>
            {
                { "weight", Weight },
                { "engine_rpm_strength", EngineRPMStrength },
                { "damper_gain", DamperGain },
            };
        }

        public override void ApplyConfig(FFBEffectConfig config)
        {
            if (config is ElevatorWeightConfig elevatorWeightConfig)
            {
                Weight = elevatorWeightConfig.Weight;
                EngineRPMStrength = elevatorWeightConfig.EngineRPMStrength;
                DamperGain = elevatorWeightConfig.DamperGain;
            }
        }

        public override ElevatorWeightConfig ExportConfig()
        {
            return new ElevatorWeightConfig
            {
                Weight = this.Weight,
                EngineRPMStrength = this.EngineRPMStrength,
                DamperGain = this.DamperGain,
            };
        }

        public override void UpdateData(SimData simData)
        {
            EngineRPM = simData.AircraftData.engineRPM;
        }
    }
}
