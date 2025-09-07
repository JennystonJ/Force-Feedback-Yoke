using Force_Feedback_Yoke_Desktop_App.FFBEffects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal static class ProfileSaver
    {
        public static AircraftConfig ToAircraftConfig(string name, FFBController pitchController, 
            FFBController rollController)
        {
            FFBControllerConfig pitchConfig = pitchController.ExportConfig();
            FFBControllerConfig rollConfig = rollController.ExportConfig();

            AircraftConfig aircraftConfig = new AircraftConfig
            {
                Name = name,
                Pitch = pitchConfig,
                Roll = rollConfig,
                PitchEffects = GetEffectConfigs(pitchController.Effects),
                RollEffects = GetEffectConfigs(rollController.Effects),
            };

            return aircraftConfig;
        }
        private static List<EffectConfig> GetEffectConfigs(Dictionary<Type, FFBEffects.FFBEffect> effects)
        {
            List<EffectConfig> list = new List<EffectConfig>();
            foreach (FFBEffect effect in effects.Values)
            {
                list.Add(new EffectConfig
                {
                    Type = effect.GetType().Name,
                    Parameters = effect.SaveParameters()
                });
            }

            return list;
        }

        public static void WriteFile(AircraftConfig aircraftConfig)
        {
            var options = new JsonSerializerOptions { WriteIndented = true };
            string json = JsonSerializer.Serialize(aircraftConfig, options);

            // Create profiles directory if it does not exist
            if(!Directory.Exists(@"profiles"))
            {
                Directory.CreateDirectory(@"profiles");
            }

            // Save file 
            File.WriteAllText($@"profiles\{aircraftConfig.Name}.json", json);

        }
    }
}
