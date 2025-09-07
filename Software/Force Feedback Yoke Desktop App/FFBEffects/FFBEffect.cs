using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
{
    public abstract class FFBEffectConfig
    {
        protected FFBEffectConfig() { }
    }
    internal abstract class FFBEffect : IConfigurable<FFBEffectConfig>, INotifyPropertyChanged
    {
        public FFBForce[] Forces { get; protected set; } = [];

        public string Name { get; protected set; } = string.Empty;

        private bool _enabled = true;

        public event PropertyChangedEventHandler? PropertyChanged;

        public virtual bool Enabled 
        {
            get => _enabled;
            set
            {
                if(_enabled == value) return;

                _enabled = value;
                OnEnabledChanged(_enabled);
            }
        }

        protected void OnPropertyChanged(object sender, PropertyChangedEventArgs propertyName)
        {
            PropertyChanged?.Invoke(sender, propertyName);
        }
        protected virtual void OnEnabledChanged(bool enabled) { }
        public abstract void LoadParameters(Dictionary<string, double> parameters);
        public abstract Dictionary<string, double> SaveParameters();
        public abstract void UpdateData(SimData simData);


        public static double Zero() => 0.0;

        public abstract void ApplyConfig(FFBEffectConfig config);
        public abstract FFBEffectConfig ExportConfig();
    }
}
