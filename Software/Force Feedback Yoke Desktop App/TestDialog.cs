using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Force_Feedback_Yoke_Desktop_App
{
    public partial class TestDialog : Form
    {
        public event EventHandler? ValueChanged;

        private TablessButtonGroup ButtonGroup;

        public TestDialog()
        {
            InitializeComponent();
            ButtonGroup = new TablessButtonGroup();
            ButtonGroup.TablessButtons.Add(btnAircraft);
            ButtonGroup.TablessButtons.Add(btnWeather);
            mainTablessControl.TablessButtonGroup = ButtonGroup;
        }

        private void TestDialog_Load(object sender, EventArgs e)
        {
            // Select aircraft tab on startup
            mainTablessControl.SelectedTab = aircraftTabPage;

            var aircraftTestSettingsBuilder = new AircraftTestSettingsBuilder();
            SetupSettingsTable(aircraftSettingsTable, aircraftTestSettingsBuilder.Build());

        }

        public void SetupSettingsTable(SettingsTable table, IEnumerable<SettingsItem> items)
        {
            table.Items = items.ToList();
        }

        private void mainTablessControl_Selected(object sender, TabControlEventArgs e)
        {
            Console.WriteLine("Tab selected.");
        }
    }
}
