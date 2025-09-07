using Force_Feedback_Yoke_Desktop_App.FFBEffects;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal static class ProfileLoader
    {
        private static AircraftConfig Load(string directory)
        {

            string json = File.ReadAllText(directory);
            AircraftConfig? config = JsonSerializer.Deserialize<AircraftConfig>(json);

            if (config == null)
            {
                throw new ArgumentException();
            }

            return config;
        }

        public static void LoadConfig(string name, FFBDevice device, FFBController pitchFFB,
            FFBController rollFFB)
        {
            AircraftConfig config = Load(@"profiles\" + name + ".json");

            // Load yoke configuration
            // Load pitch travels
            //device.ControlParams.PitchLimitInMMMin = (float)config.PitchTravelMMMin;
            //device.ControlParams.PitchLimitInMMMax = (float)config.PitchTravelMMMax;
            //pitchFFB.TravelMin = config.PitchTravelMMMin;
            //pitchFFB.TravelMax = config.PitchTravelMMMax;
            //// Load roll travels
            //device.ControlParams.RollLimitInDegMin = (float)config.RollTravelDegMin;
            //device.ControlParams.RollLimitInDegMax = (float)config.RollTravelDegMax;
            //rollFFB.TravelMin = config.RollTravelDegMin;
            //rollFFB.TravelMax = config.RollTravelDegMax;
            pitchFFB.ApplyConfig(config.Pitch);
            rollFFB.ApplyConfig(config.Roll);

            // Load pitch effects
            LoadFFBEffectsFromEffectConfigs(config.PitchEffects, pitchFFB);

            // Load roll effects
            LoadFFBEffectsFromEffectConfigs(config.RollEffects, rollFFB);

            //// Update device control data
            //device.WriteControlData();
        }

        private static void LoadFFBEffectsFromEffectConfigs(List<EffectConfig> effectConfigs, FFBController ffbController)
        {
            List<FFBEffect> effects = [];
            //foreach (EffectConfig config in effectConfigs)
            //{
            //    FFBEffect? effect = EffectFactory.CreateEffect(config.Type, config.Parameters);
            //    if (effect != null)
            //    {
            //        effects.Add(effect);
            //    }
            //}

            //return effects;

            foreach (EffectConfig config in effectConfigs)
            {
                Assembly assembly = typeof(FFBEffect).Assembly;

                // Find correct subtype in FFBEffect assembly using string name of type
                Type? effectType = assembly.GetTypes().FirstOrDefault(t => t.Name.Equals(config.Type, 
                    StringComparison.OrdinalIgnoreCase) && typeof(FFBEffect).IsAssignableFrom(t));

                if (effectType != null)
                {
                    ffbController.Effects[effectType].LoadParameters(config.Parameters);
                }
            }
        }
    }
}
