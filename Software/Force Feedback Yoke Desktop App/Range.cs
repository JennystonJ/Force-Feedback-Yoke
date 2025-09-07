using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    public class Range : INotifyPropertyChanged
    {
        public Range() { }
        public Range(decimal minimum, decimal maximum)
        {
            Minimum = minimum;
            Maximum = maximum;
        }

        private decimal _minimum;
        public decimal Minimum 
        {
            get => _minimum;
            set
            {
                if (_minimum != value)
                {
                    _minimum = value;
                    OnPropertyChanged(nameof(Minimum));
                }
            }
        }
        private decimal _maximum;
        public decimal Maximum 
        {
            get => _maximum;
            set
            {
                if (_maximum != value)
                {
                    _maximum = value; 
                    OnPropertyChanged(nameof(Maximum));
                }
            } 
        }

        public decimal CalcRange()
        {
            return _maximum - _minimum;
        }

        public event PropertyChangedEventHandler? PropertyChanged;

        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
