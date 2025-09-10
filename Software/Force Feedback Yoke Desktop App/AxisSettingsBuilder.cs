using Force_Feedback_Yoke_Desktop_App.FFBEffects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class AxisSettingsBuilder
    {
        private readonly Axis axis;
        private readonly FFBController ffb;
        private readonly FFBDevice ffbDevice;

        public AxisSettingsBuilder(Axis axis, FFBController ffb, FFBDevice ffbDevice)
        {
            this.axis = axis;
            this.ffb = ffb;
            this.ffbDevice = ffbDevice;
        }

        public IEnumerable<SettingsItem> Build()
        {
            Font categoryFont = new Font("Microsoft Sans Serif", 12, FontStyle.Bold);
            Font settingsFont = new Font("Microsoft Sans Serif", 12, FontStyle.Regular);

            yield return new SettingsItem("General", categoryFont);

            var travelSelector = new RangeSelector
            {
                ValueGap = 50,
                Unit = axis != Axis.Roll ? "mm" : "deg",
                Minimum = -180,
                Maximum = 180
            };
            Bind(travelSelector, ffb, "Travel");
            travelSelector.ValueChanged += (s, e) =>
            {
                if (axis == Axis.Pitch) { ffbDevice.ControlParams.PitchRangeMM = travelSelector.Value; }
                else if (axis == Axis.Roll) { ffbDevice.ControlParams.RollRangeDeg = travelSelector.Value; }
            };
            yield return new SettingsItem("Travel Range", settingsFont, travelSelector);

            var gainSlider = ControlFactory.GenerateGainNumericSlider();
            Bind(gainSlider, ffb, "Gain");
            yield return new SettingsItem("Gain", settingsFont, gainSlider);

            yield return new SettingsItem("Main Effects", categoryFont);

            var airspeedStiffnessSlider = ControlFactory.GenerateGainNumericSlider();
            Bind(airspeedStiffnessSlider, ffb.Effects[typeof(AirspeedStiffness)], "SpringGain");
            yield return new SettingsItem("Airspeed Stiffness", settingsFont, airspeedStiffnessSlider);

            var calibrationAirspeedSlider = ControlFactory.GenerateAirspeedNumericSlider();
            Bind(calibrationAirspeedSlider, ffb.Effects[typeof(AirspeedStiffness)], "CalibrationAirspeed");
            yield return new SettingsItem("Calibration Airspeed", settingsFont, calibrationAirspeedSlider);

            // Pitch specific effects
            if (axis == Axis.Pitch)
            {
                yield return new SettingsItem("Prop Wash Effects", categoryFont);

                var elevatorWeightSlider = ControlFactory.GenerateForceNumericSlider();
                Bind(elevatorWeightSlider, ffb.Effects[typeof(ElevatorWeight)], "Weight");
                yield return new SettingsItem("Elevator Weight", settingsFont, elevatorWeightSlider);

                var engineRpmStrengthSlider = ControlFactory.GenerateGainNumericSlider();
                Bind(engineRpmStrengthSlider, ffb.Effects[typeof(ElevatorWeight)], "EngineRPMStrength");
                yield return new SettingsItem("Engine RPM Center Strength", settingsFont, engineRpmStrengthSlider);
            }

        }

        private static void Bind(Control control, object source, string dataMember)
        {
            control.DataBindings.Add("Value", source, dataMember, true, DataSourceUpdateMode.OnPropertyChanged);
        }
     }
}
