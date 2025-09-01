using Force_Feedback_Yoke_Desktop_App.FFBForces;
using Force_Feedback_Yoke_Desktop_App.Filters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App.FFBEffects
{
    internal class ElevatorGust : FFBEffect
    {
        private FFBConstant constantForce;
        // Convert to ft/s
        private const double MPS_TO_FTPS = 3.28084;
        private const double KT_TO_FTPS = 1.68781;

        public WeatherData Wind { get; set; }
        public AircraftData Aircraft { get; set; }
        public double HeaveGain { get; set; } = 0.2;
        public double AoaGain { get; set; } = 0.5;

        private HighPassFilter highPassHeave;
        private LowPassFilter lowPassHeave;

        private HighPassFilter highPassAoa;
        private LowPassFilter lowPassAoa;

        public ElevatorGust()
        {
            highPassHeave = new HighPassFilter(5, 0.02);
            lowPassHeave = new LowPassFilter(200, 0.02);

            highPassAoa = new HighPassFilter(5, 0.02);
            lowPassAoa= new LowPassFilter(200, 0.02);

            constantForce = new FFBConstant();

            Forces = [constantForce];

            // Ensure delegate starts disabled
            Enabled = false;
            OnEnabledChanged(false);
        }

        public double ElevatorGustFunction()
        {
            // Vertical speed in feet per second
            double v_true_ftps = Math.Max(50 * KT_TO_FTPS, Wind.windVel_kt * KT_TO_FTPS);

            // Dynamic pressure
            double q = 0.5f * Wind.ambientDensity_spcf * v_true_ftps * v_true_ftps;

            // Heave force
            double heaveIn = highPassHeave.Update(
                lowPassHeave.Update(Wind.accelBodyZ_ftps2));
            double gHeave = HeaveGain * q;
            double fHeave = gHeave * heaveIn;

            // AoA force
            double deltaAlpha = highPassAoa.Update(
                lowPassAoa.Update(Aircraft.incidenceAlpha));
            double gAoa = AoaGain * q;
            double fAoa = gAoa * deltaAlpha;

            double result = fHeave + fAoa;

            Console.WriteLine(result);

            return Math.Clamp(result, -1, 1);
        }

        private static double GainSchedule(double V_true_ftps, double windVel_kts)
        {
            const double v0 = 120.0; // knots
            double v_kt = V_true_ftps / KT_TO_FTPS;
            double airspeedFactor = v_kt / v0;

            // Limit gain at high or low speeds
            airspeedFactor = Math.Clamp(airspeedFactor, 0.3, 2.0);

            double windFactor = 1.0 + (windVel_kts / 10.0); // scales wind, tune divisor

            return airspeedFactor * windFactor;
        }

        protected override void OnEnabledChanged(bool enabled)
        {
            constantForce.forceDelegate = enabled ? ElevatorGustFunction : Zero;
        }

        public override void LoadParameters(Dictionary<string, double> parameters)
        {
            HeaveGain = parameters["heave_gain"];
            AoaGain = parameters["aoa_gain"];
        }

        public override Dictionary<string, double> SaveParameters()
        {
            return new Dictionary<string, double>
            {
                { "heave_gain", HeaveGain},
                { "aoa_gain", AoaGain},
            };
        }
    }
}
