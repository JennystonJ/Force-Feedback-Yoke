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
            AircraftConfig aircraftConfig = new AircraftConfig
            {
                Name = name,
                PitchTravelMM = pitchController.Travel,
                PitchGain = pitchController.Gain,
                PitchEffects = GetEffectConfigs(pitchController),
                RollTravelDeg = rollController.Travel,
                RollGain = rollController.Gain,
                RollEffects = GetEffectConfigs(rollController),
            };

            return aircraftConfig;
        }
        public static List<EffectConfig> GetEffectConfigs(FFBController controller)
        {
            List<EffectConfig> list = new List<EffectConfig>();
            foreach (var effect in controller.Effects)
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
            File.WriteAllText($"{aircraftConfig.Name}.json", json);
        }
    }
}
