using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class ControlFactory
    {
        public static NumericSlider GenerateGainNumericSlider()
        {
            return new NumericSlider
            {
                Range = new Range(0, 100),
                UnitText = "%",
                ShowUnit = true,
                Value = 0,
            };
        }

        public static NumericSlider GenerateForceNumericSlider()
        {
            return new NumericSlider
            {
                Range = new Range(0, 10),
                UnitText = "N",
                ShowUnit = true,
                Value = 0,
            };
        }

        public static NumericSlider GenerateAirspeedNumericSlider()
        {
            return new NumericSlider
            {
                Range = new Range(1, 1000),
                UnitText = "kt",
                ShowUnit = true,
                Value = 1,
            };
        }
    }
}
