using Force_Feedback_Yoke_Desktop_App;
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
    public partial class Form1 : Form
    {
        private Color colorMenuBackground = Color.DodgerBlue;
        private Color colorMenuSelectedBackground = Color.DeepSkyBlue;


        private FFBDevice ffbDevice = new FFBDevice();
        private static SimConnectHelper simConnectHelper = new SimConnectHelper();
        private CancellationTokenSource cts;

        public Form1()
        {
            InitializeComponent();

            // Select home page on startup
            resetMenuButtons();
            tablessControlContent.SelectedTab = homePage;
            btnHome.BackColor = colorMenuSelectedBackground;

            // Add event callbacks to ffbDevice
            ffbDevice.DataReadyEvent += ProcessFFB;
            ffbDevice.DeviceConnectedEvent += FFBDeviceConnected;
            ffbDevice.DeviceDisconnectedEvent += FFBDeviceDisconnected;
        }

        private void FFBDeviceDisconnected(object? sender, EventArgs e)
        {
            SetLabelText("Status: Disconnected", lblStatus);
            SetButtonText("Connect", btnConnect);
            ResetIndicators();
        }

        private void FFBDeviceConnected(object? sender, EventArgs e)
        {
            SetLabelText("Status: Connected", lblStatus);
            SetButtonText("Disconnect", btnConnect);

            ffbDevice.ControlParams.PitchLimitInMMMin = -150.0f / 2.0f;
            ffbDevice.ControlParams.PitchLimitInMMMax = 150.0f / 2.0f;
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
            resetMenuButtons();
            tablessControlContent.SelectedTab = homePage;
            btnHome.BackColor = colorMenuSelectedBackground;
        }

        private void btnProfiles_Click(object sender, EventArgs e)
        {
            resetMenuButtons();
            tablessControlContent.SelectedTab = profilesPage;
            btnProfiles.BackColor = colorMenuSelectedBackground;
        }

        private void btnYokeData_Click(object sender, EventArgs e)
        {
            resetMenuButtons();
            tablessControlContent.SelectedTab = yokeDataPage;
            btnYokeData.BackColor = colorMenuSelectedBackground;
        }

        private void resetMenuButtons()
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
                    btnConnect.Text = "Disconnect";
                    lblStatus.Text = "Status: Connected";
                }
            }
            else
            {
                ffbDevice.Disconnect();
                btnConnect.Text = "Connect";
                lblStatus.Text = "Status: Disconnected";
                ResetIndicators();
            }
            //this.Controls.Add(simConnectHelper);
            //simConnectHelper.OpenConnection();
        }

        private void ProcessFFB(object? sender, EventArgs e)
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
    }
}
