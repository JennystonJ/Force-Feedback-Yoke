using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
{
    public class AirspeedStiffnessConfig: FFBEffectConfig
    {
        public double SpringGain { get; set; }
        public double DamperGain { get; set; }
    }
    internal class AirspeedStiffness : FFBEffect
    {
        public double Airspeed { get; set; }
        
        private double _springGain;
        public double SpringGain {
            get => _springGain; 
            set 
            { 
                if (_springGain != value)
                {
                    _springGain = value;
                    OnPropertyChanged(this, new PropertyChangedEventArgs(nameof(SpringGain)));
                }
            } 
        }
        
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

        private FFBSpring springForce;
        private FFBDamper damperForce;
        
        public AirspeedStiffness()
        {
            SpringGain = 0;
            DamperGain = 0.1;

            springForce = new FFBSpring();
            damperForce = new FFBDamper();

            Forces = [springForce, damperForce];

            // Ensure delegates start disabled
            Enabled = false;
            OnEnabledChanged(false);
        }
        public AirspeedStiffness(double springGain, double damperGain=0.1)
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
            return SpringGain * Math.Min(Math.Pow(Airspeed / 100, 2), 1);
        }

        public double AirSpeedStiffnessDamperFunction()
        {
            return DamperGain / 1000.0 * Math.Min(Math.Pow(Airspeed / 100, 2), 1);
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

        public override void ApplyConfig(FFBEffectConfig config)
        {
            if (config is AirspeedStiffnessConfig airspeedStiffnessConfig)
            {
                SpringGain = airspeedStiffnessConfig.SpringGain;
                DamperGain = airspeedStiffnessConfig.DamperGain;
            }
       
        }

        public override AirspeedStiffnessConfig ExportConfig()
        {
            return new AirspeedStiffnessConfig
            {
                SpringGain = this.SpringGain,
                DamperGain = this.DamperGain,
            };
        }

        public override void UpdateData(SimData simData)
        {
            Airspeed = simData.AircraftData.airSpeed;
        }
    }
}
