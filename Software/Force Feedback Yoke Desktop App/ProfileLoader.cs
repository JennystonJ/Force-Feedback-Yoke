using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal static class ProfileLoader
    {
        public static AircraftConfig Load(string directory)
        {

            string json = File.ReadAllText(directory);
            AircraftConfig ?config = JsonSerializer.Deserialize<AircraftConfig>(json);

            if (config == null)
            {
                throw new ArgumentException();
            }

            return config;
        }
    }
}
