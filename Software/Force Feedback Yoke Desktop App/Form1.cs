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

        private Dictionary<IValueChanged, Action<object>?> controlToSettter = new();
        private Dictionary<string, FFBEffect> adjPitchFFBEffects = new();
        private Dictionary<string, FFBEffect> adjRollFFBEffects = new();

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

            SetupPitchSettingsTable();
            SetupRollSettingsTable();

            LoadCboProfiles();
        }

        private void simConnectHelper_SimConnectionClosedEvent(object? sender, EventArgs e)
        {
            btnConnectSim.Text = "Connect";
            lblConnectSimStatus.Text = "Simulator Status: Disconnected";
        }

        private void simConnectHelper_DataReadyEvent(object? sender, EventArgs e)
        {
            ((AirSpeedStiffness)adjPitchFFBEffects["airspeed stiffness"]).AirSpeed = simConnectHelper.Aircraft.airSpeed;
            ((ElevatorWeight)adjPitchFFBEffects["elevator weight"]).EngineRPM = simConnectHelper.Aircraft.engineRPM;

            ((AirSpeedStiffness)adjRollFFBEffects["airspeed stiffness"]).AirSpeed = simConnectHelper.Aircraft.airSpeed;

            simConnectHelper.SetValue(new ControlAxisData
            {
                elevator = ffbDevice.HidData.pitchAxis/2,
                aileron = ffbDevice.HidData.rollAxis/2
            });
        }

        private void simConnectHelper_SimPauseChangedEvent(object? sender, EventArgs e)
        {
            if(e is SimPauseEventArgs pauseArgs)
            {
                if(pauseArgs.Paused)
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
            btnFfbOn.Text = "FFB ON";
            btnFfbOn.Enabled = false;
            SetLabelText("Status: Disconnected", lblStatus);
            SetButtonText("Connect", btnConnect);
            ResetIndicators();
        }

        private void FFBDeviceConnected(object? sender, EventArgs e)
        {
            SetLabelText("Status: Connected, OFF", lblStatus);
            SetButtonText("Disconnect", btnConnect);

            btnFfbOn.Text = "FFB ON";
            btnFfbOn.Enabled = true;

            ffbDevice.ControlParams.FFBEnabled = false;
            ffbDevice.ControlParams.PitchLimitInMMMin = -150.0f / 2.0f;
            ffbDevice.ControlParams.PitchLimitInMMMax = 150.0f / 2.0f;
            ffbDevice.ControlParams.RollLimitInDegMin = -90.0f;
            ffbDevice.ControlParams.RollLimitInDegMax = 90.0f;
            ffbDevice.WriteControlData();
        }

        private void AddPitchFFBEffects()
        {
            adjPitchFFBEffects.Clear();

            AirSpeedStiffness airspeedStiffness = new AirSpeedStiffness(0.0);
            ElevatorWeight elevatorWeight = new ElevatorWeight(0.0, 0.0);

            adjPitchFFBEffects.Add("airspeed stiffness", airspeedStiffness);
            adjPitchFFBEffects.Add("elevator weight", elevatorWeight);

            pitchFFB.Effects.Add(airspeedStiffness);
            pitchFFB.Effects.Add(elevatorWeight);

            foreach(FFBEffect effect in pitchFFB.Effects)
            {
                effect.Enabled = true;
            }
        }

        private void AddRollFFBEffects()
        {
            adjRollFFBEffects.Clear();

            AirSpeedStiffness airSpeedStiffness = new AirSpeedStiffness(0.0);

            adjRollFFBEffects.Add("airspeed stiffness", airSpeedStiffness);

            rollFFB.Effects.Add(airSpeedStiffness);

            foreach (FFBEffect effect in rollFFB.Effects)
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
            double pitchPosition = ffbDevice.HidData.pitchAxis;
            SetTravelIndicatorValue((int)Utilities.Scale(pitchPosition,
                -32767, 32767, -100, 100),
                tiPitchPosition);
            // Calculate pitch position in mm
            double pitchTravelRangeMM = ffbDevice.ControlParams.PitchLimitInMMMax -
                ffbDevice.ControlParams.PitchLimitInMMMin;
            double pitchPositionMM = (pitchTravelRangeMM / 2.0) * pitchPosition / 32767.0;
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
            double rollPosition = ffbDevice.HidData.rollAxis;
            SetTravelIndicatorValue((int)Utilities.Scale(rollPosition,
                -32767, 32767, -100, 100),
                tiRollPosition);
            // Calculate roll position in deg
            double rollTravelRangeDeg = ffbDevice.ControlParams.RollLimitInDegMax -
                ffbDevice.ControlParams.RollLimitInDegMin;
            double rollPositionDeg = (rollTravelRangeDeg / 2.0) * rollPosition / 32767.0;
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

            }
            else
            {
                // Cancelled, do nothing
            }
        }

        private void btnSaveProfile_Click(object sender, EventArgs e)
        {

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

        public void SetupPitchSettingsTable()
        {
            string[] strings = ["General", "Travel Range", "Gain",
                                "Main Effects", "Airspeed Stiffness",
                                "Prop Wash Effects", "Elevator Weight", "Engine RPM Center Strength"];
            bool[] isCategories = [true, false, false,
                                true, false,
                                true, false, false];
            Control?[] controls = [null,
                new RangeSelector {
                    ValueGap = 50,
                    Unit = "mm",
                    Minimum = -90,
                    Maximum = 90
                }, GenerateGainNumericSlider(),
                null, GenerateGainNumericSlider(),
                null, GenerateForceNumericSlider(), GenerateGainNumericSlider(),
                ];

            SetupSettingsTable(pitchSettingsTable, strings, isCategories, controls);

            Action<object>?[] actions = {
                null,
                v => 
                {
                    ffbDevice.ControlParams.PitchLimitInMMMin = decimal.ToSingle(((Range)v).Minimum);
                    ffbDevice.ControlParams.PitchLimitInMMMax = decimal.ToSingle(((Range)v).Maximum);
                    ffbDevice.WriteControlData();
                }, // Travel Range
                v => pitchFFB.Gain = decimal.ToDouble((decimal) v / 100),                                   // Gain
                null,
                v => ((AirSpeedStiffness)adjPitchFFBEffects["airspeed stiffness"]).SpringGain = decimal.ToDouble((decimal)v/100), // Airspeed Stiffness
                null,
                v => ((ElevatorWeight)adjPitchFFBEffects["elevator weight"]).Weight = decimal.ToDouble((decimal)v), // Elevator weight
                v => ((ElevatorWeight)adjPitchFFBEffects["elevator weight"]).EngineRPMStrength = decimal.ToDouble((decimal)v/100), // Engine RPM Center Strength
            };

            SetupSettingsTableActions(pitchSettingsTable, actions);
        }

        public void SetupSettingsTableActions(SettingsTable table, Action<object>?[] actions)
        {
            int actionIndex = 0;
            foreach (SettingsItem item in table.Items)
            {
                if (item.Control is IValueChanged vc)
                {
                    controlToSettter[vc] = actions[actionIndex];
                }

                actionIndex++;
            }
        }

        public void SetupRollSettingsTable()
        {
            string[] strings = ["General", "Travel Range", "Gain",
                                "Main Effects", "Airspeed Stiffness"];
            bool[] isCategories = [true, false, false,
                                true, false];
            Control?[] controls = [null,
                new RangeSelector {
                    ValueGap = 50,
                    Unit = "deg",
                    Minimum = -120,
                    Maximum = 120
                }, GenerateGainNumericSlider(),
                null, GenerateGainNumericSlider()
                ];

            SetupSettingsTable(rollSettingsTable, strings, isCategories, controls);

            Action<object>?[] actions = {
                null,
                v =>                 
                {
                    ffbDevice.ControlParams.RollLimitInDegMin = decimal.ToSingle(((Range)v).Minimum);
                    ffbDevice.ControlParams.RollLimitInDegMax = decimal.ToSingle(((Range)v).Maximum);
                    ffbDevice.WriteControlData();
                }, // Travel Range
                v => rollFFB.Gain = decimal.ToDouble((decimal) v / 100),                                   // Gain
                null,
                v => ((AirSpeedStiffness)adjRollFFBEffects["airspeed stiffness"]).SpringGain = decimal.ToDouble((decimal)v/100), // Airspeed Stiffness
            };

            SetupSettingsTableActions(rollSettingsTable, actions);
        }

        public void SetupSettingsTable(SettingsTable table, string[] strings, bool[] isCategories, Control?[] controls)
        {
            Font categoryFont = new Font("Microsoft Sans Serif", 12, FontStyle.Bold);
            Font settingsFont = new Font("Microsoft Sans Serif", 12, FontStyle.Regular);

            Color foreColor = Color.WhiteSmoke;

            List<SettingsItem> items = new List<SettingsItem>();
            for (int i = 0; i < controls.Length; i++)
            {
                items.Add(new SettingsItem
                {
                    Category = isCategories[i],
                    Control = controls[i],
                });

                SettingsItem item = items[i];

                item.Label.Text = strings[i];
                if (item.Category)
                {
                    // Use category font since it's a category
                    item.Label.Font = categoryFont;
                }
                else
                {
                    // Otherwise use settings font
                    item.Label.Font = settingsFont;
                }
                item.Label.ForeColor = foreColor;
                item.Label.AutoSize = true;
            }

            table.Items = items;
        }

        public NumericSlider GenerateGainNumericSlider()
        {
            NumericSlider gain = new NumericSlider
            {

                ShowUnit = true,
                UnitText = "%",
                Value = 0,
            };
            // TODO: Refactor code so Numeric Slider handles range (makes both track bar and numeric up down equal)
            gain.TrackBar.SetRange(0, 100);
            gain.NumericUpDown.Maximum = 100;
            gain.NumericUpDown.Minimum = 0;
            gain.Value = 0;

            return gain;
        }

        public NumericSlider GenerateForceNumericSlider()
        {
            NumericSlider force = new NumericSlider
            {

                ShowUnit = true,
                UnitText = "N",
                Value = 0,
            };
            // TODO: Refactor code so Numeric Slider handles range (makes both track bar and numeric up down equal)
            // TODO: Add divider to track bar to increase resolution
            force.TrackBar.SetRange(0, 10);
            force.NumericUpDown.Maximum = 10;
            force.NumericUpDown.Minimum = 0;
            force.NumericUpDown.DecimalPlaces = 2;
            force.Value = 0;

            return force;
        }

        private void pitchSettingsTable_ValueChanged(object sender, EventArgs e)
        {
            if (sender is IValueChanged vc && controlToSettter.TryGetValue(vc, out var setter))
            {
                setter?.Invoke(vc.Value);
            }
        }

        private void rollSettingsTable_ValueChanged(object sender, EventArgs e)
        {
            if (sender is IValueChanged vc && controlToSettter.TryGetValue(vc, out var setter))
            {
                setter?.Invoke(vc.Value);
            }
        }

        private void btnFfbOn_Click(object sender, EventArgs e)
        {
            if(ffbDevice.ControlParams.FFBEnabled)
            {
                ffbDevice.ControlParams.FFBEnabled = false;
                ffbDevice.WriteControlData();
                lblStatus.Text = "Status: Connected, OFF";
                btnFfbOn.Text = "FFB ON";
            }
            else
            {
                ffbDevice.ControlParams.FFBEnabled = true;
                ffbDevice.WriteControlData();
                lblStatus.Text = "Status: Connected, ON";
                btnFfbOn.Text = "FFB OFF";
            }
        }
    }
}
