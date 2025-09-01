using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Force_Feedback_Yoke_Desktop_App
{
    public partial class NumericSlider : UserControl, IValueChanged
    {
        public event EventHandler? ValueChanged;

        private decimal _value;
        [Description("Numeric slider value."), Category("Behavior")]
        public decimal Value {
            
            get => _value;
            set
            {
                if (_value != value)
                {
                    _value = value;
                    tbSlider.Value = decimal.ToInt32(_value);
                    nudValue.Value = _value;
                    ValueChanged?.Invoke(this, EventArgs.Empty);
                }
            }
        }

        private decimal _nudDivisor = 1;
        [Description("Numeric up down to slider divisor"), Category("Behavior")]
        public decimal Divisor
        {
            get => _nudDivisor;
            set
            {
                _nudDivisor = value;
            }
        }


        object IValueChanged.Value 
        {
            get => Value; 
            set
            {
                Value = (decimal)value;
            }
        }

        [Description("Color of foreground."), Category("Appearance")]
        public override Color ForeColor { get => base.ForeColor;
            set
            { 
                base.ForeColor = value; 
                tbSlider.ForeColor = value;
                lblUnit.ForeColor = value;
            } 
        }

        [Description("Color of background."), Category("Appearance")]
        public override Color BackColor
        {
            get => base.BackColor;
            set
            {
                base.BackColor = value;
                tbSlider.BackColor = value;
                lblUnit.BackColor = value;
            }
        }

        private bool _showUnit = true;
        [Description("Display unit."), Category("Behavior")]
        public bool ShowUnit
        {
            get => _showUnit;
            set
            {
                
                _showUnit = value;
                lblUnit.Visible = value;
                
            }
        }

        private string _unitText = "%";

        [Description("Unit text."), Category("Appearance")]
        public string UnitText
        {
            get => _unitText;
            set
            {

                _unitText = value;
                lblUnit.Text = value;
            }
        }

        public TrackBar TrackBar {
            get => tbSlider;
            set => tbSlider = value;
        }
        public NumericUpDown NumericUpDown { 
            get => nudValue;
            set => nudValue = value;
        }

        public NumericSlider()
        {
            InitializeComponent();
        }

        private void tbSlider_Scroll(object sender, EventArgs e)
        {
            nudValue.Value = tbSlider.Value / _nudDivisor;
            _value = tbSlider.Value;
            ValueChanged?.Invoke(this, EventArgs.Empty);
        }

        private void nudValue_ValueChanged(object sender, EventArgs e)
        {
            tbSlider.Value = decimal.ToInt32(nudValue.Value * _nudDivisor);
            _value = nudValue.Value;
            ValueChanged?.Invoke(this, EventArgs.Empty);
        }
    }
}
