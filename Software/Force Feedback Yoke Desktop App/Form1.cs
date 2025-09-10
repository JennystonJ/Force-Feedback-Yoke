using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using Force_Feedback_Yoke_Desktop_App.FFBEffects;
using Microsoft.FlightSimulator.SimConnect;

namespace Force_Feedback_Yoke_Desktop_App
{
    public partial class Form1 : Form
    {
        private Color colorMenuBackground = Color.DodgerBlue;
        private Color colorMenuSelectedBackground = Color.DeepSkyBlue;


        private FFBDevice ffbDevice = new FFBDevice();
        private static SimConnectHelper simConnectHelper = new SimConnectHelper();
        private CancellationTokenSource cts;

        private FFBController pitchFFB;
        private FFBController rollFFB;

        public Form1()
        {
            InitializeComponent();

            // Add event callbacks to sim connect helper
            simConnectHelper.SimPauseChangedEvent += simConnectHelper_SimPauseChangedEvent;
            simConnectHelper.DataReadyEvent += simConnectHelper_DataReadyEvent;
            simConnectHelper.SimConnectionClosedEvent += simConnectHelper_SimConnectionClosedEvent;

            // Add event callbacks to ffbDevice
            ffbDevice.DataReadyEvent += ProcessFFB;
            ffbDevice.DeviceConnectedEvent += FFBDeviceConnected;
            ffbDevice.DeviceDisconnectedEvent += FFBDeviceDisconnected;

            pitchFFB = new FFBController();
            rollFFB = new FFBController();

            AddPitchFFBEffects();
            AddRollFFBEffects();

            pitchFFB.Enable = true;
            rollFFB.Enable = true;

            // *** UI Setup ***
            // Select home page on startup
            ResetMenuButtons();
            tablessControlContent.SelectedTab = homePage;
            btnHome.BackColor = colorMenuSelectedBackground;

            // Select pitch profile in profile editor on startup
            ResetProfileButtons();
            btnPitchProfile.BackColor = colorMenuSelectedBackground;
            profileEditorTablessControl.SelectedTab = pitchProfileTabPage;

            var pitchSettingsBuilder = new AxisSettingsBuilder(Axis.Pitch, pitchFFB, ffbDevice);
            SetupSettingsTable(pitchSettingsTable, pitchSettingsBuilder.Build());

            var rollSettingsBuilder = new AxisSettingsBuilder(Axis.Roll, rollFFB, ffbDevice);
            SetupSettingsTable(rollSettingsTable, rollSettingsBuilder.Build());

            //SetupPitchSettingsTable();
            //SetupRollSettingsTable();

            SetupPitchSettingsToolTip();

            LoadCboProfiles();
        }

        private void simConnectHelper_SimConnectionClosedEvent(object? sender, EventArgs e)
        {
            btnConnectSim.Text = "Connect";
            lblConnectSimStatus.Text = "Simulator Status: Disconnected";
        }

        private void simConnectHelper_DataReadyEvent(object? sender, EventArgs e)
        {
            pitchFFB.UpdateData(simConnectHelper.SimData);
            rollFFB.UpdateData(simConnectHelper.SimData);

            simConnectHelper.SetValue(new SimControlAxisData
            {
                elevator = ffbDevice.HidData.pitchAxis / 2,
                aileron = ffbDevice.HidData.rollAxis / 2
            });
        }

        private void simConnectHelper_SimPauseChangedEvent(object? sender, EventArgs e)
        {
            if (e is SimPauseEventArgs pauseArgs)
            {
                if (pauseArgs.Paused)
                {
                    pitchFFB.Enable = false;
                    rollFFB.Enable = false;
                }
                else
                {
                    pitchFFB.Enable = true;
                    rollFFB.Enable = true;
                }
            }
        }

        private void FFBDeviceDisconnected(object? sender, EventArgs e)
        {
            SetButtonText("FFB ON", btnFfbOn);
            SetButtonEnabled(false, btnFfbOn);

            SetLabelText("Status: Disconnected", lblStatus);
            SetButtonText("Connect", btnConnect);
            ResetIndicators();
        }

        private void FFBDeviceConnected(object? sender, EventArgs e)
        {
            SetButtonText("FFB ON", btnFfbOn);
            SetButtonEnabled(true, btnFfbOn);

            SetLabelText("Status: Connected, OFF", lblStatus);
            SetButtonText("Disconnect", btnConnect);


            ffbDevice.ControlParams.FFBEnabled = false;
        }

        private void AddPitchFFBEffects()
        {
            pitchFFB.Effects.Clear();
            pitchFFB.Effects.Add(typeof(AirspeedStiffness), new AirspeedStiffness());
            pitchFFB.Effects.Add(typeof(ElevatorWeight), new ElevatorWeight());


            foreach (FFBEffect effect in pitchFFB.Effects.Values)
            {
                effect.Enabled = true;
            }
        }

        private void AddRollFFBEffects()
        {
            rollFFB.Effects.Clear();
            rollFFB.Effects.Add(typeof(AirspeedStiffness), new AirspeedStiffness());

            foreach (FFBEffect effect in rollFFB.Effects.Values)
            {
                effect.Enabled = true;
            }
        }

        delegate void SetLabelTextCallback(string text, Label label);
        private void SetLabelText(string text, Label label)
        {
            // Check if on different threads
            if (label.InvokeRequired)
            {
                SetLabelTextCallback d = new SetLabelTextCallback(SetLabelText);
                label.Invoke(d, new object[] { text, label });
            }
            else
            {
                label.Text = text;
            }
        }

        delegate void SetButtonTextCallback(string text, Button button);
        private void SetButtonText(string text, Button button)
        {
            // Check if on different threads
            if (button.InvokeRequired)
            {
                SetButtonTextCallback d = new SetButtonTextCallback(SetButtonText);
                button.Invoke(d, new object[] { text, button });
            }
            else
            {
                button.Text = text;
            }
        }

        delegate void SetButtonEnabledCallback(bool enable, Button button);
        private void SetButtonEnabled(bool enabled, Button button)
        {
            // Check if on different threads
            if(button.InvokeRequired)
            {
                SetButtonEnabledCallback d = new SetButtonEnabledCallback(SetButtonEnabled);
                button.Invoke(d, new object[] { enabled, button });
            }
            else
            {
                button.Enabled = enabled;
            }
        }

        delegate void SetTravelIndicatorValueCallback(int value, TravelIndicator ti);
        private void SetTravelIndicatorValue(int value, TravelIndicator ti)
        {
            // Check if on different threads
            if (ti.InvokeRequired)
            {
                SetTravelIndicatorValueCallback d = new SetTravelIndicatorValueCallback(SetTravelIndicatorValue);
                Invoke(d, new object[] { value, ti });
            }
            else
            {
                ti.Value = value;
            }
        }

        private void btnHome_Click(object sender, EventArgs e)
        {
            ResetMenuButtons();
            tablessControlContent.SelectedTab = homePage;
            btnHome.BackColor = colorMenuSelectedBackground;
        }

        private void btnProfiles_Click(object sender, EventArgs e)
        {
            ResetMenuButtons();
            tablessControlContent.SelectedTab = profilesPage;
            btnProfiles.BackColor = colorMenuSelectedBackground;
        }

        private void btnYokeData_Click(object sender, EventArgs e)
        {
            ResetMenuButtons();
            tablessControlContent.SelectedTab = yokeDataPage;
            btnYokeData.BackColor = colorMenuSelectedBackground;
        }

        private void ResetMenuButtons()
        {
            btnHome.BackColor = colorMenuBackground;
            btnProfiles.BackColor = colorMenuBackground;
            btnYokeData.BackColor = colorMenuBackground;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (!ffbDevice.Connected)
            {
                if (!ffbDevice.Connect())
                {
                    MessageBox.Show("Force feedback device unavailable.",
                        "Connection failed", MessageBoxButtons.OK,
                        MessageBoxIcon.Exclamation);
                }
                else
                {
                    btnFfbOn.Enabled = true;
                    btnFfbOn.Text = "FFB ON";
                    ffbDevice.ControlParams.FFBEnabled = false;
                    btnConnect.Text = "Disconnect";
                    lblStatus.Text = "Status: Connected, OFF";
                }
            }
            else
            {
                ffbDevice.Disconnect();
                btnFfbOn.Enabled = false;
                btnFfbOn.Text = "FFB ON";
                ffbDevice.ControlParams.FFBEnabled = false;
                btnConnect.Text = "Connect";
                lblStatus.Text = "Status: Disconnected";
                ResetIndicators();
            }
            //this.Controls.Add(simConnectHelper);
            //simConnectHelper.OpenConnection();
        }

        private void ProcessFFB(object? sender, EventArgs e)
        {
            ffbDevice.SetForces(pitchFFB.CalcForces(), rollFFB.CalcForces());
            UpdateIndicators();
        }

        private void UpdateIndicators()
        {
            // *** Handle pitch axis ***
            // Pitch position
            decimal pitchPosition = Convert.ToDecimal(ffbDevice.HidData.pitchAxis);
            SetTravelIndicatorValue((int)Utilities.Scale(pitchPosition,
                -32767, 32767, -100, 100),
                tiPitchPosition);
            // Calculate pitch position in mm
            decimal pitchTravelRangeMM = ffbDevice.ControlParams.PitchRangeMM.CalcRange();
            decimal pitchPositionMM = (pitchTravelRangeMM / 2.0M) * Convert.ToDecimal(pitchPosition) / 32767.0M;
            // Set label indicator
            SetLabelText(string.Format("{0:0.0} mm", pitchPositionMM), lblPitchPosValue);

            //Pitch force
            double pitchForce = ffbDevice.HidData.pitchForce;
            double maxPitchForce = ffbDevice.Capabilities.PitchMaxForce;
            SetTravelIndicatorValue((int)Utilities.Scale(pitchForce,
                -32767, 32767, -100, 100), tiPitchForce);
            // Calculate pitch force in N
            double pitchForceN = (pitchForce / 32767.0) * maxPitchForce;
            // Set label indicator
            SetLabelText(string.Format("{0:0.0} N", pitchForceN), lblPitchForceValue);


            // *** Handle roll axis ***
            // Roll position
            decimal rollPosition = Convert.ToDecimal(ffbDevice.HidData.rollAxis);
            SetTravelIndicatorValue((int)Utilities.Scale(rollPosition,
                -32767, 32767, -100, 100),
                tiRollPosition);
            // Calculate roll position in deg
            decimal rollTravelRangeDeg = ffbDevice.ControlParams.RollRangeDeg.CalcRange();
            decimal rollPositionDeg = (rollTravelRangeDeg / 2) * rollPosition / 32767;
            // Set label indicator
            SetLabelText(string.Format("{0:0.0} deg", rollPositionDeg), lblRollPosValue);

            //Roll force
            double rollTorque = ffbDevice.HidData.rollForce;
            double maxRollTorque = ffbDevice.Capabilities.RollMaxForce;
            SetTravelIndicatorValue((int)Utilities.Scale(rollTorque,
                -32767, 32767, -100, 100), tiRollTorque);
            // Calculate pitch force in N
            double rollTorqueNm = (rollTorque / 32767.0) * maxRollTorque;
            // Set label indicator
            SetLabelText(string.Format("{0:0.0} N", rollTorqueNm), lblRollTorqueValue);
        }

        private void ResetIndicators()
        {
            // Reset travel indicators to 0
            tiPitchPosition.Value = 0;
            tiPitchForce.Value = 0;
            tiPitchUserForce.Value = 0;

            tiRollPosition.Value = 0;
            tiRollTorque.Value = 0;
            tiRollUserTorque.Value = 0;

            // Reset label indicators
            lblPitchPosValue.Text = "----.- mm";
            lblPitchForceValue.Text = "--.-- N";
            lblPitchUserForceValue.Text = "--.-- N";

            lblRollPosValue.Text = "---.- deg";
            lblRollTorqueValue.Text = "--.-- Nm";
            lblRollUserTorqueValue.Text = "--.-- Nm";
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            ffbDevice.Disconnect();
            btnConnect.Text = "Connect";
            lblStatus.Text = "Status: Disconnected";
            ResetIndicators();
        }

        private void btnPitchProfile_Click(object sender, EventArgs e)
        {
            ResetProfileButtons();
            btnPitchProfile.BackColor = colorMenuSelectedBackground;
            profileEditorTablessControl.SelectedTab = pitchProfileTabPage;
        }

        private void btnRollProfile_Click(object sender, EventArgs e)
        {
            ResetProfileButtons();
            btnRollProfile.BackColor = colorMenuSelectedBackground;
            profileEditorTablessControl.SelectedTab = rollProfileTabPage;
        }
        private void ResetProfileButtons()
        {
            btnPitchProfile.BackColor = colorMenuBackground;
            btnRollProfile.BackColor = colorMenuBackground;
        }

        private void LoadCboProfiles()
        {
            cboProfile.Items.Clear();
            try
            {
                string[] fileDirs = Directory.GetFiles(@".\profiles", "*.json");
                foreach (string d in fileDirs)
                {
                    cboProfile.Items.Add(Path.GetFileNameWithoutExtension(d));
                }
            }
            catch (Exception)
            {
                // Do nothing
            }
        }

        private void btnSaveAs_Click(object sender, EventArgs e)
        {
            SaveAsDialog saveAsDialog = new SaveAsDialog();
            DialogResult result = saveAsDialog.ShowDialog();
            if (result == DialogResult.OK)
            {
                AircraftConfig aircraftConfig =
                    ProfileSaver.ToAircraftConfig(saveAsDialog.UserInput, pitchFFB, rollFFB);
                ProfileSaver.WriteFile(aircraftConfig);
                LoadCboProfiles();
            }
            else
            {
                // Cancelled, do nothing
            }
        }

        private void btnSaveProfile_Click(object sender, EventArgs e)
        {
            // Ensure a profile is selected
            if(cboProfile.Text != "")
            {
                // Write to current profile
                AircraftConfig aircraftConfig =
                    ProfileSaver.ToAircraftConfig(cboProfile.Text, pitchFFB, rollFFB);
                ProfileSaver.WriteFile(aircraftConfig);
            }
        }

        private void btnConnectSim_Click(object sender, EventArgs e)
        {
            if (!simConnectHelper.Connected)
            {
                try
                {
                    simConnectHelper.OpenConnection();
                    btnConnectSim.Text = "Disconnect";
                    lblConnectSimStatus.Text = "Simulator Status: Connected";
                }
                catch (COMException)
                {
                    MessageBox.Show("Failed to connect to Microsoft Flight Simulator.",
                        "Connection Failed", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            else
            {
                simConnectHelper.CloseConnection();
                btnConnectSim.Text = "Connect";
                lblConnectSimStatus.Text = "Simulator Status: Disconnected";
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.Controls.Add(simConnectHelper);
        }

        //public void SetupPitchSettingsTable()
        //{
        //    string[] strings = ["General", "Travel Range", "Gain",
        //                        "Main Effects", "Airspeed Stiffness", "Calibration Airspeed",
        //                        "Prop Wash Effects", "Elevator Weight", "Engine RPM Center Strength"];

        //    var travelSelector = new RangeSelector
        //    {
        //        ValueGap = 50,
        //        Unit = "mm",
        //        Minimum = -100,
        //        Maximum = 100
        //    };
        //    travelSelector.DataBindings.Add("Value", pitchFFB, "Travel", true, DataSourceUpdateMode.OnPropertyChanged);
        //    travelSelector.ValueChanged += (s, e) => ffbDevice.ControlParams.PitchRangeMM = travelSelector.Value;

        //    var gainSlider = GenerateGainNumericSlider();
        //    gainSlider.DataBindings.Add("Value", pitchFFB, "Gain", true, DataSourceUpdateMode.OnPropertyChanged);

        //    var airspeedSlider = GenerateGainNumericSlider();
        //    airspeedSlider.DataBindings.Add("Value", pitchFFB.Effects[typeof(AirspeedStiffness)], "SpringGain", true, DataSourceUpdateMode.OnPropertyChanged);

        //    var calibrationAirspeedSlider = GenerateAirspeedSlider();
        //    calibrationAirspeedSlider.DataBindings.Add("Value", pitchFFB.Effects[typeof(AirspeedStiffness)], "CalibrationAirspeed", true, DataSourceUpdateMode.OnPropertyChanged);

        //    var elevatorWeightSlider = GenerateForceNumericSlider();
        //    elevatorWeightSlider.DataBindings.Add("Value", pitchFFB.Effects[typeof(ElevatorWeight)], "Weight", true, DataSourceUpdateMode.OnPropertyChanged);

        //    var engineRpmStrengthSlider = GenerateGainNumericSlider();
        //    engineRpmStrengthSlider.DataBindings.Add("Value", pitchFFB.Effects[typeof(ElevatorWeight)], "EngineRPMStrength", true, DataSourceUpdateMode.OnPropertyChanged);

        //    bool[] isCategories = [true, false, false,
        //                        true, false, false,
        //                        true, false, false];
        //    Control?[] controls = [null,
        //        travelSelector, 
        //        gainSlider,
        //        null, airspeedSlider, calibrationAirspeedSlider,
        //        null, elevatorWeightSlider, engineRpmStrengthSlider,
        //        ];

        //    SetupSettingsTable(pitchSettingsTable, strings, isCategories, controls);
        //}

        //public void SetupRollSettingsTable()
        //{
        //    string[] strings = ["General", "Travel Range", "Gain",
        //                        "Main Effects", "Airspeed Stiffness", "Calibration Airspeed"];
        //    bool[] isCategories = [true, false, false,
        //                        true, false, false];


        //    var travelSelector = new RangeSelector
        //    {
        //        ValueGap = 50,
        //        Unit = "deg",
        //        Minimum = -180,
        //        Maximum = 180
        //    };
        //    travelSelector.DataBindings.Add("Value", rollFFB, "Travel", true, DataSourceUpdateMode.OnPropertyChanged);
        //    travelSelector.ValueChanged += (s, e) => ffbDevice.ControlParams.RollRangeDeg = travelSelector.Value;

        //    var gainSlider = GenerateGainNumericSlider();
        //    gainSlider.DataBindings.Add("Value", rollFFB, "Gain", true, DataSourceUpdateMode.OnPropertyChanged);

        //    var airSpeedSlider = GenerateGainNumericSlider();
        //    airSpeedSlider.DataBindings.Add("Value", rollFFB.Effects[typeof(AirspeedStiffness)], "SpringGain", true, DataSourceUpdateMode.OnPropertyChanged);

        //    var calibrationAirspeedSlider = GenerateAirspeedSlider();
        //    calibrationAirspeedSlider.DataBindings.Add("Value", rollFFB.Effects[typeof(AirspeedStiffness)], "CalibrationAirspeed", true, DataSourceUpdateMode.OnPropertyChanged);

        //    Control?[] controls = [null,
        //        travelSelector, 
        //        gainSlider,
        //        null, airSpeedSlider, calibrationAirspeedSlider,
        //        ];

        //    SetupSettingsTable(rollSettingsTable, strings, isCategories, controls);
        //}

        public void SetupSettingsTable(SettingsTable table, IEnumerable<SettingsItem> items)
        {

            table.Items = items.ToList();
            //Font categoryFont = new Font("Microsoft Sans Serif", 12, FontStyle.Bold);
            //Font settingsFont = new Font("Microsoft Sans Serif", 12, FontStyle.Regular);

            //Color foreColor = Color.WhiteSmoke;

            //List<SettingsItem> items = new List<SettingsItem>();
            //for (int i = 0; i < controls.Length; i++)
            //{
            //    items.Add(new SettingsItem
            //    {
            //        IsCategory = isCategories[i],
            //        Control = controls[i],
            //    });

            //    SettingsItem item = items[i];

            //    item.Label.Text = strings[i];
            //    if (item.IsCategory)
            //    {
            //        // Use category font since it's a category
            //        item.Label.Font = categoryFont;
            //    }
            //    else
            //    {
            //        // Otherwise use settings font
            //        item.Label.Font = settingsFont;
            //    }
            //    item.Label.ForeColor = foreColor;
            //    item.Label.AutoSize = true;
            //}

            //table.Items = items;
        }

        //public NumericSlider GenerateGainNumericSlider()
        //{
        //    NumericSlider gainSlider = new NumericSlider
        //    {

        //        ShowUnit = true,
        //        UnitText = "%",
        //        Value = 0,
        //    };
        //    // TODO: Refactor code so Numeric Slider handles range (makes both track bar and numeric up down equal)
        //    gainSlider.TrackBar.SetRange(0, 100);
        //    gainSlider.NumericUpDown.Maximum = 100;
        //    gainSlider.NumericUpDown.Minimum = 0;
        //    gainSlider.Value = 0;

        //    return gainSlider;
        //}

        //public NumericSlider GenerateForceNumericSlider()
        //{
        //    NumericSlider forceSlider = new NumericSlider
        //    {

        //        ShowUnit = true,
        //        UnitText = "N",
        //        Value = 0,
        //        Divisor = 10,
        //    };
        //    // TODO: Refactor code so Numeric Slider handles range (makes both track bar and numeric up down equal)
        //    // TODO: Add divider to track bar to increase resolution
        //    forceSlider.TrackBar.SetRange(0, 100);
        //    forceSlider.NumericUpDown.Maximum = 10;
        //    forceSlider.NumericUpDown.Minimum = 0;
        //    forceSlider.NumericUpDown.DecimalPlaces = 2;
        //    forceSlider.Value = 0;

        //    return forceSlider;
        //}

        //public NumericSlider GenerateAirspeedSlider()
        //{
        //    NumericSlider airspeedSlider = new NumericSlider
        //    {
        //        ShowUnit = true,
        //        UnitText = "kt",
        //        Value = 1,
        //        Divisor = 1,
        //    };
        //    airspeedSlider.TrackBar.SetRange(1, 1000);
        //    airspeedSlider.NumericUpDown.Maximum = 1000;
        //    airspeedSlider.NumericUpDown.Minimum = 1;
        //    airspeedSlider.Value = 1;

        //    return airspeedSlider;
        //}

        private void SetupPitchSettingsToolTip()
        {
        }

        private void btnFfbOn_Click(object sender, EventArgs e)
        {
            if (ffbDevice.ControlParams.FFBEnabled)
            {
                ffbDevice.ControlParams.FFBEnabled = false;
                lblStatus.Text = "Status: Connected, OFF";
                btnFfbOn.Text = "FFB ON";
            }
            else
            {
                ffbDevice.ControlParams.FFBEnabled = true;
                lblStatus.Text = "Status: Connected, ON";
                btnFfbOn.Text = "FFB OFF";
            }
        }

        private void cboProfile_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cboProfile.Text != "")
            {
                btnSaveProfile.Enabled = true;
                ProfileLoader.LoadConfig(cboProfile.Text, ffbDevice, pitchFFB, rollFFB);
            }
            else
            {
                btnSaveProfile.Enabled= false;
            }
        }

        public static Binding BindDoubleToDecimal(Control control, string controlProperty,
            object dataSource, string dataMember)
        {
            Binding binding = control.DataBindings.Add(controlProperty, dataSource, dataMember);

            binding.Format += (s, e) =>
            {
                if (e.DesiredType == typeof(decimal) && e.Value is double d)
                {
                    e.Value = Convert.ToDecimal(d);
                }
            };

            binding.Parse += (s, e) =>
            {
                if(e.DesiredType == typeof(double) && e.Value is decimal d)
                {
                    e.Value = Convert.ToDouble(d);
                }
            };

            return binding;
        }
    }
}
