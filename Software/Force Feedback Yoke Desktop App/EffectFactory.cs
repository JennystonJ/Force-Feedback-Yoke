using Force_Feedback_Yoke_Desktop_App.FFBEffects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal static class EffectFactory
    {
        public static FFBEffect? CreateEffect(string type, Dictionary<string, double> parameters)
        {
            Assembly assembly = typeof(FFBEffect).Assembly;
            var effectType = assembly.GetTypes().
                FirstOrDefault(t => t.Name.Equals(type, StringComparison.OrdinalIgnoreCase)
                && typeof(FFBEffect).IsAssignableFrom(t));

            if (effectType == null)
            {
                throw new ArgumentException($"Unknown effect type: {type}");
            }

            var effect = Activator.CreateInstance(effectType) as FFBEffect;
            effect?.LoadParameters(parameters);

            return effect;
        }
    }
}
