using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Force_Feedback_Yoke_Desktop_App
{
    public partial class RangeSelector : UserControl, IValueChanged
    {
        public event EventHandler? ValueChanged;
        object IValueChanged.Value
        {
            get => Value;
            set
            {
                Value = (Range)value;
            }
        }
        public Range Value
        {
            get => new Range { Minimum = nudMinRange.Value, Maximum = nudMaxRange.Value};
            set
            {
                nudMinRange.Value = value.Minimum;
                nudMaxRange.Value = value.Maximum;
                UpdateNudValues(false);
            }
        }

        private decimal _valueGap;
        [Description("Minimum gap between minimum and maximum."), Category("Behavior")]
        public decimal ValueGap
        {
            get => _valueGap;
            set
            {
                _valueGap = value;
                UpdateNudValues(false);
            }
        }

        private string _unit = "unit";
        [Description("Displayed units."), Category("Appearance")]
        public string Unit
        {
            get => _unit;
            set
            {
                _unit = value;
                lblMinRangeUnit.Text = _unit + " to ";
                lblMaxRangeUnit.Text = _unit;
            }
        }

        private decimal _minimum = 0;
        [Description("Minimum value."), Category("Behavior")]
        public decimal Minimum
        {
            get => _minimum;
            set
            {
                _minimum = value;
                nudMinRange.Minimum = value;
                nudMaxRange.Minimum = value;
                UpdateNudValues(true);
            }
        }

        private decimal _maximum = 0;

        [Description("Maximum value."), Category("Behavior")]
        public decimal Maximum
        {
            get => _maximum;
            set
            {
                _maximum = value;
                nudMinRange.Maximum = value;
                nudMaxRange.Maximum = value;
                UpdateNudValues(false);
            }
        }

        public RangeSelector()
        {
            InitializeComponent();
        }

        private void nudMinRange_ValueChanged(object sender, EventArgs e)
        {
            UpdateNudValues(true);
            ValueChanged?.Invoke(this, EventArgs.Empty);
        }

        private void nudMaxRange_ValueChanged(object sender, EventArgs e)
        {
            UpdateNudValues(false);
            ValueChanged?.Invoke(this, EventArgs.Empty);
        }

        private void UpdateNudValues(bool minimumPriority)
        {
            decimal minRange;
            decimal maxRange;
            //if (minimumPriority)
            //{
            //    nudMaxRange.Value = Math.Clamp(nudMaxRange.Value,
            //        Math.Max(nudMinRange.Value + _valueGap, nudMinRange.Value), 
            //        Math.Max(nudMaxRange.Maximum, nudMinRange.Value + _valueGap));
            //    nudMinRange.Value = Math.Clamp(nudMinRange.Value,
            //        nudMinRange.Minimum, Math.Max(nudMaxRange.Value - _valueGap, nudMaxRange.Value));

            //}
            //else
            //{
            //    nudMinRange.Value = Math.Clamp(nudMinRange.Value,
            //        nudMinRange.Minimum, 
            //        Math.Max(nudMaxRange.Value - _valueGap, nudMaxRange.Value));
            //    nudMaxRange.Value = Math.Clamp(nudMaxRange.Value,
            //        Math.Min(nudMinRange.Value + _valueGap, nudMinRange.Value), nudMaxRange.Maximum);
            //}

            // Maintain value gap between both numeric up downs
            if(minimumPriority)
            {
                maxRange = Math.Max(nudMaxRange.Value, nudMinRange.Value + _valueGap);
                minRange = Math.Min(nudMinRange.Value, maxRange - _valueGap);
            }
            else
            {
                minRange = Math.Min(nudMinRange.Value, nudMaxRange.Value - _valueGap);
                maxRange = Math.Max(nudMaxRange.Value, minRange + _valueGap);
            }

            // Clamp numeric up down value if bounds reached
            if (minRange < nudMinRange.Minimum)
            {
                nudMinRange.Value = nudMinRange.Minimum;
                nudMaxRange.Value = nudMinRange.Minimum + _valueGap;
            }
            else if (maxRange > nudMaxRange.Maximum)
            {
                nudMinRange.Value = nudMinRange.Maximum - _valueGap;
                nudMaxRange.Value = nudMinRange.Maximum;
            }
            // Update normally
            else
            {
                nudMinRange.Value = minRange;
                nudMaxRange.Value = maxRange;
            }
        }
    }

    public class Range
    {
        public decimal Minimum { get; set; }
        public decimal Maximum { get; set; }
    }
}
