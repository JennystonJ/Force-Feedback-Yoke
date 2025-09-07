using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    public class SimData
    {
        public AircraftData AircraftData { get; set; }
        public WeatherData WeatherData { get; set; }

        public SimData()
        {
            
        }

        public SimData(AircraftData aircraftData, WeatherData weatherData)
        {
            AircraftData = aircraftData;
            WeatherData = weatherData;
        }
    }
}
