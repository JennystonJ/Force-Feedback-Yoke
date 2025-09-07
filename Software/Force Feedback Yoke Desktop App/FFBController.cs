using Force_Feedback_Yoke_Desktop_App.FFBEffects;
using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class FFBControllerConfig
    {
        public Range Travel {  get; set; } = new Range();
        public double Gain { get; set; }
    }

    internal class FFBController : IConfigurable<FFBControllerConfig>, INotifyPropertyChanged
    {
        private bool _enable;
        public bool Enable 
        {
            get => _enable;
            set
            {
                if(_enable != value)
                {
                    _enable = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Enable)));
                }
            }
        }
        private double _gain;
        public double Gain 
        {
            get => _gain;
            set
            {
                if(_gain != value)
                {
                    _gain = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Gain)));
                }
            }
        }
        public double MaxForce { get; set; }
        private Range _travel = new();
        public Range Travel 
        { 
            get => _travel;
            set
            {
                if (_travel != value)
                {
                    _travel = value;
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Travel)));
                }
            }
        }
        public Dictionary<Type, FFBEffect> Effects { get; set; }

        public FFBController()
        {
            Enable = false;
            Gain = 0; 
            MaxForce = 0;
            Travel = new Range(-100, 100);
            Effects = [];
        }

        public event PropertyChangedEventHandler? PropertyChanged;

        public ForceSet CalcForces()
        {
            if (!Enable)
            {
                return new ForceSet();
            }

            ForceSet netForceSet = new ForceSet();
            foreach (FFBEffect effect in Effects.Values)
            {
                foreach(FFBForce force in effect.Forces)
                {
                    netForceSet += force.CalcForce();
                }
            }

            return netForceSet * Gain;
        }

        public void ApplyConfig(FFBControllerConfig config)
        {
            Travel = config.Travel;
            Gain = config.Gain;
        }

        public FFBControllerConfig ExportConfig()
        {
            return new FFBControllerConfig()
            {
                Travel = this.Travel,
                Gain = this.Gain,
            };
        }

        public void UpdateData(SimData simData)
        {
            foreach(FFBEffect effect in Effects.Values)
            {
                effect.UpdateData(simData);
            }
        }
    }
}
