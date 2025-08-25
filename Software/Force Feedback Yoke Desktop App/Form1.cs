using MSFSForceFeedbackController;
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
            ffbDevice.DataReadyEvent = ProcessFFB;
            ffbDevice.DeviceConnectedEvent += FFBDeviceConnected;
            ffbDevice.DeviceDisconnectedEvent += FFBDeviceDisconnected;
        }

        private void FFBDeviceDisconnected()
        {
            SetLabelText("Status: Disconnected", lblStatus);
            SetButtonText("Connect", btnConnect);
        }

        private void FFBDeviceConnected()
        {
            SetLabelText("Status: Connected", lblStatus);
            SetButtonText("Disconnect", btnConnect);

            ffbDevice.controlData.ElevatorRangeInMM = 165;
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
            if(button.InvokeRequired)
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
            }
            //this.Controls.Add(simConnectHelper);
            //simConnectHelper.OpenConnection();
        }

        private void ProcessFFB()
        {
            // Handle roll axis
            SetTravelIndicatorValue((int)Utilities.Scale(ffbDevice.hidData.aileron, 
                -32767, 32767, -100, 100), 
                tiRollPosition);

            // Handle pitch axis
            SetTravelIndicatorValue((int)Utilities.Scale(ffbDevice.hidData.elevator,
                -32767, 32767, -100, 100),
                tiPitchPosition);

        }
    }
}
