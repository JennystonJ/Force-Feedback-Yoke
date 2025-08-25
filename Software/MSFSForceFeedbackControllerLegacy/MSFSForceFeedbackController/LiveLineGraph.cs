using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.VisualStyles;

namespace MSFSForceFeedbackController
{
    public partial class LiveLineGraph : Panel
    {
        private CircularBuffer<Point> pointsBuffer = new(1000);
        private readonly Pen _frame = new(SystemColors.ControlDarkDark, 2);
        private readonly Pen _xAxis = new(SystemColors.ControlDark, 2);
        private readonly Pen _tickMark = new(SystemColors.ControlDark, 2);
        private readonly Pen _graph = new(Color.Blue, 2);

        private decimal _tickMarkInterval = 10;
        public decimal Time { get; set; } = 0;

        [Description("Distance between tick marks."), Category("Appearance")]
        public decimal TickMarkInterval
        {
            get { return _tickMarkInterval; }
            set 
            { 
                if (value <= 0)
                {
                    throw new ArgumentOutOfRangeException("TickMarkInterval must be greater than 0.");
                }
                _tickMarkInterval = value; Invalidate(); 
            }
        }

        private decimal _maxXValue = (decimal)100.0;
        [Description("Maximum x scale value."), Category("Behavior")]
        public decimal MaxXValue
        {
            get { return _maxXValue; }
            set
            {
                if (value <= _minXValue)
                {
                    throw new ArgumentOutOfRangeException("MaxXValue must be greater than MinXValue.");
                }
                _maxXValue = value; Invalidate();
            }
        }

        private decimal _minXValue = (decimal)-100.0;
        [Description("Minimum x scale value."), Category("Behavior")]
        public decimal MinXValue
        {
            get { return _minXValue; }
            set
            {
                if (value >= _maxXValue)
                {
                    throw new ArgumentOutOfRangeException("MinXValue must be less than MaxXValue.");
                }
                _minXValue = value; Invalidate();
            }
        }

        private decimal _maxYValue = (decimal)100.0;
        [Description("Maximum y scale value."), Category("Behavior")]
        public decimal MaxYValue
        {
            get { return _maxYValue; }
            set 
            { 
                if (value <= _minYValue)
                {
                    throw new ArgumentOutOfRangeException("MaxYValue must be greater than MinYValue.");
                }
                _maxYValue = value; Invalidate(); 
            }
        }

        private decimal _minYValue = (decimal)-100.0;
        [Description("Minimum y scale value."), Category("Behavior")]
        public decimal MinYValue
        {
            get { return _minYValue; }
            set 
            {
                if(value >= _maxYValue)
                {
                    throw new ArgumentOutOfRangeException("MinYValue must be less than MaxYValue.");
                }
                _minYValue = value; Invalidate(); 
            }
        }

        public LiveLineGraph()
        {
            InitializeComponent();
            DoubleBuffered = true;
        }

        public LiveLineGraph(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
            DoubleBuffered = true;
        }

        public void AddPoint(Point point)
        {
            pointsBuffer.Add(point);
            Invalidate();
        }

        public void Shift(decimal x)
        {
            Time += x;
            Invalidate();
        }


        protected override void OnPaint(PaintEventArgs e)
        {
            DrawXAxis(e);
            DrawGraph(e);
            DrawTickMarks(e);
            DrawFrame(e);
        }

        private void DrawFrame(PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(_frame, 0, 0, Width, Height);
        }

        private void DrawXAxis(PaintEventArgs e)
        {
            int xAxisHeight = CalculateXAxisHeight();
            e.Graphics.DrawLine(_xAxis, 0, xAxisHeight, Width, xAxisHeight);
        }

        private double CalculateXScaleRatio()
        {
            double xScaleRange = (double)(_maxYValue - _minYValue);
            return Width / xScaleRange;
        }

        private int CalculateXAxisHeight()
        {
            int xAxisYValue = (int)(CalculateYScaleRatio() * 
                (CalculateYScaleRange() - (double)Math.Abs(_minYValue)));
            return xAxisYValue;
        }
        private double CalculateYScaleRange()
        {
            return (double)(_maxYValue - _minYValue);
        }
        private double CalculateYScaleRatio()
        {
            return Height / CalculateYScaleRange();
        }

        private void DrawTickMarks(PaintEventArgs e)
        {
            int pixelInterval = (int)(CalculateYScaleRatio() * (double)_tickMarkInterval);
            for (int y = 0; y <= Height; y += pixelInterval)
            {
                e.Graphics.DrawLine(_tickMark, 0, y, 5, y);
            }
        }

        private void DrawGraph(PaintEventArgs e)
        {
            if(pointsBuffer.Count <= 1) return;

            Point[] points = pointsBuffer.ToArray().OrderBy(p => p.X).ToArray();

            //Find index of the first on-screen point
            int firstOnScreenPointIndex = 0;
            for(int i = 0; i < points.Length; i++)
            {
                if (ScalePointToPixelCoord(points[i]).X >= 0)
                {
                    firstOnScreenPointIndex = i;
                    break;
                }
            }

            //Find index of the last on-screen point
            int lastOnScreenPointIndex = 0;
            for(int i = 0; i < points.Length; i++)
            {
                if (ScalePointToPixelCoord(points[i]).X > Width)
                {
                    break;
                }

                lastOnScreenPointIndex = i;
            }

            // Make array 3 elements larger to accomodate possible first and last off-screen points
            Point[] pixelPoints = new Point[lastOnScreenPointIndex - firstOnScreenPointIndex + 3];

            // Account for edge cases where there may be no off-screen points
            int firstPointIndex = firstOnScreenPointIndex == 0 ? firstOnScreenPointIndex : 
                firstOnScreenPointIndex - 1;
            int lastPointIndex = lastOnScreenPointIndex == points.Length - 1 ? lastOnScreenPointIndex : 
                lastOnScreenPointIndex+1;

            // Add points between first point index and last point index to points to draw array
            for(int i = firstPointIndex; i <= lastPointIndex; i++)
            {
                pixelPoints[i - firstPointIndex] = ScalePointToPixelCoord(points[i]);
            }

            // Draw points
            e.Graphics.DrawLines(_graph, pixelPoints[0..(lastPointIndex-firstPointIndex+1)]);
            

        }

        private Point ScalePointToPixelCoord(Point point)
        {
            double xAxisHeight = CalculateXAxisHeight();
            double yScaleRatio = CalculateYScaleRatio();
            double xScaleRatio = CalculateXScaleRatio();

            return new((int)(Width + (point.X - (double)Time) * xScaleRatio),
                (int)(Height - xAxisHeight - point.Y * yScaleRatio));
        }
    }
}
