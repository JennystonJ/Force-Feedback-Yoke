using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    public class TravelIndicator : Panel
    {

        public enum TravelIndicatorType
        {
            Normal,
            Centered
        }

        private TravelIndicatorType _type = TravelIndicatorType.Normal;
        private Pen _centerLine = new(SystemColors.ControlDarkDark, 2);
        private int _value = 0;

        private SolidBrush _brush = new(SystemColors.ControlDark);
        private SolidBrush _background = new(SystemColors.Control);
        private Pen _border = new(SystemColors.ControlDarkDark, 2);

        private int _maximum = 100;
        private int _minimum = 0;

        public TravelIndicator()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint |
                ControlStyles.UserPaint |
                ControlStyles.OptimizedDoubleBuffer |
                ControlStyles.ResizeRedraw, true);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            _brush = new(base.ForeColor);
            _background = new(base.BackColor);

            if (Type == TravelIndicatorType.Normal)
            {
                PaintNormal(e);
            }
            else if (Type == TravelIndicatorType.Centered) 
            { 
                PaintCentered(e); 
            }
        }

        private void PaintNormal(PaintEventArgs e)
        {
            float fillRatio = (Value - _minimum) / (float)(_maximum - _minimum);
            int fillTo = (int)(Width * fillRatio);

            e.Graphics.FillRectangle(_background, 0, 0, Width, Height);
            e.Graphics.FillRectangle(_brush, 0, 0, fillTo, Height);
            e.Graphics.DrawRectangle(_border, 0, 0, Width, Height);
        }

        private void PaintCentered(PaintEventArgs e)
        {
            float range = _maximum - _minimum;
            float center = Width - Width / range * (range + _minimum);
            float fillRatio = (Value - _minimum) / range;
            float fillWidth = (int)(Width * fillRatio) - center;

            // Determine fill x position from bar direction
            float fillX;
            if(fillWidth < 0)
            {
                fillX = (int)(center + fillWidth);
                fillWidth = Math.Abs(fillWidth);
            }
            else
            {
                fillX = center;
            }

            e.Graphics.FillRectangle(_background, 0, 0, Width, Height);
            e.Graphics.FillRectangle(_brush, fillX, 0, fillWidth, Height);
            e.Graphics.DrawRectangle(_border, 0, 0, Width, Height);

            e.Graphics.DrawLine(_centerLine, center, 0, center, Height);

        }

        [Description("Determines how the indicator is displayed."), Category("Behavior")]
        public TravelIndicatorType Type 
        { 
            get { return _type; } 
            set { _type = value; Invalidate(); }
        }

        [Description("Travel indicator value."), Category("Behavior")]
        public int Value
        {
            get { return _value; }
            set { _value = value; Invalidate(); }
        }

        [Description("Maximum travel indicator value."), Category("Behavior")]
        public int Maximum
        {
            get { return _maximum; }
            set { _maximum = value; Invalidate(); }
        }

        [Description("Minimum travel indicator value."), Category("Behavior")]
        public int Minimum
        {
            get { return _minimum; }
            set { _minimum = value; Invalidate(); }
        }

        [Description("Color of travel indicator center line."), Category("Appearance")]
        public Color CenterLineColor
        {
            get { return _centerLine.Color; }
            set { _centerLine.Color = value; Invalidate(); }
        }

    }
}
