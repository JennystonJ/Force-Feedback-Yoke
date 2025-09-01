using Force_Feedback_Yoke_Desktop_App.FFBForces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
{
    internal abstract class FFBEffect
    {
        public FFBForce[] Forces { get; protected set; }

        public string Name { get; protected set; }

        private bool _enabled = true;
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

        protected FFBEffect()
        {
            Forces = [];
            Name = "FFBEffect";
        }

        protected virtual void OnEnabledChanged(bool enabled) { }
        public abstract void LoadParameters(Dictionary<string, double> parameters);
        public abstract Dictionary<string, double> SaveParameters();

        public static double Zero() => 0.0;
    }
}
