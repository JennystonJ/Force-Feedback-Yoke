using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class AircraftTestSettingsBuilder : INotifyPropertyChanged
    {

        private AircraftData _aircraftData;
        public AircraftData AircraftData 
        {
            get => _aircraftData;
            private set 
            {

            }
        }

        public event PropertyChangedEventHandler? PropertyChanged;

        public IEnumerable<SettingsItem> Build()
        {
            Font categoryFont = new Font("Microsoft Sans Serif", 12, FontStyle.Bold);
            Font settingsFont = new Font("Microsoft Sans Serif", 12, FontStyle.Regular);

            yield return new SettingsItem("General", categoryFont);

            var airspeedSlider = ControlFactory.GenerateAirspeedNumericSlider(new Range(0, 25000));
            airspeedSlider.ValueChanged += (_, _) => DoubleUpdate(airspeedSlider, nameof(AircraftData), ref _aircraftData.airSpeed);
            yield return new SettingsItem("Airspeed", settingsFont, airspeedSlider);

            var engineRPMSlider = ControlFactory.GenerateRPMNumericSlider();
            engineRPMSlider.ValueChanged += (_, _) => DoubleUpdate(engineRPMSlider, nameof(AircraftData), ref _aircraftData.engineRPM);
            yield return new SettingsItem("Engine RPM", settingsFont, engineRPMSlider);

            
        }
        private void OnPropertyChanged(string? propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        private void DoubleUpdate(Control control, string propertyName, ref double data)
        {
            PropertyInfo? controlProperty = control.GetType().GetProperty("Value");
            if ((controlProperty != null && controlProperty.GetValue(control, null) is double value))
            {
                data = value;
                OnPropertyChanged(propertyName);
            }
        }
        private static void Bind(Control control, object source, string dataMember)
        {
            control.DataBindings.Add("Value", source, dataMember, true, DataSourceUpdateMode.OnPropertyChanged);
        }
    }
}
