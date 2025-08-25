using Microsoft.Win32.SafeHandles;
using System.Management;

using Device.Net;
using Hid.Net.Windows;
using Microsoft.Extensions.Logging;
using System.Threading.Tasks;
using System.Linq;
using System.Reactive.Linq;
using Timer = System.Threading.Timer;
using System.Security.Policy;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;
using System.Data.Common;
using System.Data;
using MSFSForceFeedbackController.FFBEffects;
using Microsoft.FlightSimulator.SimConnect;
using System;
using System.Diagnostics;

namespace MSFSForceFeedbackController
{

    public partial class MainForm : Form
    {
        private FormVisualizer visualizer;

        private FFBDevice ffbDevice;

        //private static bool ffbStarted = false;

        //private const string USB_VID = "0483";
        //private const string USB_PID = "5750";
        //private enum ConnectConnectStatus
        //{
        //    SUCCESS,
        //    NOT_FOUND,
        //};

        private enum ConnectMode
        {
            NONE,
            SIMULATOR,
            TEST,
        };

        private ConnectMode connectMode = ConnectMode.NONE;

        //private const int outBufferLength = 12;

        private static UsbDeviceMonitor usbDeviceMonitor;

        private static SimConnectHelper simConnectHelper = new SimConnectHelper();
        //private static IDevice device;
        //private static byte[] outBuffer;
        //private static byte[] outBufferBack;
        //private static byte[] outBufferA = new byte[outBufferLength + 1];
        //private static byte[] outBufferB = new byte[outBufferLength + 1];

        //private static byte[] inBuffer;

        //private static bool transferComplete = false;

        private static int tbAileronValue;
        private static int tbAileronFreqValue;
        private static int tbAileronAmpValue;

        //private static Timer timer;

        private CancellationTokenSource cts;

        private short aileronPosition;
        private short elevatorPosition;

        private FFBController elevatorFFBController;
        private FFBController aileronFFBController;


        private AirSpeedStiffness elevatorAirSpeedStiffness;
        private ElevatorWeight elevatorWeight;
        private ElevatorGust elevatorGust;

        // For measuring time between ProcessFFB calls
        private Stopwatch stopwatch;
        private long previousMilliseconds;

        delegate void SetLabelTextCallback(string text, Label label);
        private void SetLabelText(string text, Label label)
        {
            // Check if on different threads
            if (label.InvokeRequired)
            {
                SetLabelTextCallback d = new SetLabelTextCallback(SetLabelText);
                label.Invoke(d, new object[] { text });
            }
            else
            {
                label.Text = text;
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

        public MainForm()
        {
            InitializeComponent();

            //outBuffer = outBufferA;
            //outBufferBack = outBufferB;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            ffbDevice.Connect();

            this.Controls.Add(simConnectHelper);
            simConnectHelper.OpenConnection();
        }

        //private static async Task<int> StartHid(Task<ConnectStatus> hidTask, TimerCallback callback)
        //{
        //    //ConnectStatus connectStatus = await hidTask;

        //    if (hidTask.Result == ConnectStatus.NOT_FOUND)
        //    {
        //        return 1;
        //    }

        //    timer = new Timer(callback, null, TimeSpan.FromMilliseconds(100),
        //        TimeSpan.FromMilliseconds(1));

        //    transferComplete = false;
        //    outBufferA[0] = 0x01;
        //    Task transferHidTask = TransferHid();

        //    return 0;
        //}

        private void tbAileron_Scroll(object sender, EventArgs e)
        {
            //tbAileronValue = tbAileron.Value;

            //byte[] ffbOutBytes = BitConverter.GetBytes(ffbOut);
            //Array.Copy(ffbOutBytes, 0, outBufferA, 1, ffbOutBytes.Length);
            // simConnectHelper.SetValue(tbAileron.Value);
        }

        //private static async Task<ConnectStatus> ConnectHid()
        //{
        //    //// Register the factory for creating Hid devices
        //    uint vid = Convert.ToUInt32(USB_VID, 16);
        //    uint pid = Convert.ToUInt32(USB_PID, 16);
        //    var hidFactory = new FilterDeviceDefinition(vid, pid).CreateWindowsHidDeviceFactory();
        //    //var hidFactory = new FilterDeviceDefinition(0x0483, 0x5750, 65280).CreateWindowsHidDeviceFactory();//, "Force Feedback Yoke",
        //    //new Guid("{745A17A0-74D3-11D0-B6Fe-00A0C90F57DA}")).CreateWindowsHidDeviceFactory();

        //    // Get connected device definitions
        //    var deviceDefinitions = (await hidFactory.GetConnectedDeviceDefinitionsAsync().
        //        ConfigureAwait(false)).ToList();

        //    if (deviceDefinitions.Count == 0)
        //    {
        //        Console.WriteLine("Device not found.");
        //        return ConnectStatus.NOT_FOUND;
        //    }

        //    Console.WriteLine("Device found.");

        //    // Obtain device from definitions
        //    device = await hidFactory.GetDeviceAsync(deviceDefinitions.First()).ConfigureAwait(false);

        //    // Initialize device
        //    await device.InitializeAsync().ConfigureAwait(false);


        //    //var observable = Observable
        //    //    .Timer(TimeSpan.Zero, TimeSpan.FromSeconds(0.1))
        //    //    .SelectMany(_ => Observable.FromAsync(() => device.WriteAndReadAsync(outBufferA)))
        //    //    .Select(data => (ByteArrayToInt16(data.Data)));

        //    //observable.Subscribe(data => ProcessHIDData(data));

        //    // Create request buffer (must be 1 byte larger than report buffer)
        //    //var buffer = new byte[65];
        //    //buffer[1] = 0x02;

        //    //var readBuffer = await device.WriteAndReadAsync(buffer).ConfigureAwait(false);
        //    return ConnectStatus.SUCCESS;
        //}

        //private static async Task TransferHid()
        //{

        //    inBuffer = await device.WriteAndReadAsync(outBufferA).ConfigureAwait(false);
        //    transferComplete = true;
        //}

        //private static Int16 ByteArrayToInt16(byte[] arr)
        //{
        //    return (Int16)(((arr[0] & 0xFF)) |
        //        ((arr[1] & 0xFF) << 8));
        //}

        private static void swapOutBuffers()
        {
            //byte[] tmp;
            //tmp = outBuffer;
            //outBuffer = outBufferBack;
            //outBufferBack = tmp;
        }

        //private static void ProcessHIDData(byte[] data)
        //{
        //    var aileronAxisRaw = data[1..3];
        //    Int16 aileronAxis = ByteArrayToInt16(aileronAxisRaw);

        //    StructSimVarOut outData = new StructSimVarOut();
        //    outData.aileron = (aileronAxis / 32767.0) * 16000;
        //    //outData.yokeAileron = (aileronAxis / 32767.0) * 16000;
        //    Console.WriteLine("Aileron Position: " + outData.aileron);
        //    simConnectHelper.SetValue(outData);
        //    //Console.WriteLine(simConnectHelper.aileronPosition);
        //}

        //private static void ProcessFFB()
        //{
        //    if (ffbStarted)
        //    {
        //        float ffbOut = (float)(simConnectHelper.airSpeed * 0.005f);
        //        Math.Clamp(ffbOut, 0.0f, 1.0f);

        //        byte[] ffbOutBytes = BitConverter.GetBytes(ffbOut);
        //        Array.Copy(ffbOutBytes, 0, outBufferA, 1, ffbOutBytes.Length);
        //        outBufferA[0] = 0x01; // reportId byte
        //    }
        //    else
        //    {
        //        outBufferA[0] = 0x00; // reportId byte (control)
        //        outBufferA[1] = 0x00; // ffb disable
        //        //byte[] aileronRange = BitConverter.GetBytes();

        //    }
        //}

        //private static void CalcFFBTest()
        //{
        //    float ffbOut = tbAileronValue / 100.0f;

        //    byte[] ffbOutBytes = BitConverter.GetBytes(ffbOut);

        //    outBufferA[0] = 0x01; // reportId byte
        //    Array.Copy(ffbOutBytes, 0, outBufferA, 1, ffbOutBytes.Length);

        //    ffbOut = tbAileronAmpValue / 100.0f;
        //    ffbOutBytes = BitConverter.GetBytes(ffbOut);
        //    Array.Copy(ffbOutBytes, 0, outBufferA, 4 + 1, ffbOutBytes.Length);

        //    ffbOutBytes = BitConverter.GetBytes(tbAileronFreqValue);
        //    Array.Copy(ffbOutBytes, 0, outBufferA, 4 * 2 + 1, ffbOutBytes.Length);
        //}
        //private static void HIDTransferHandleTest(object? state)
        //{
        //    if (!transferComplete)
        //    {
        //        return;
        //    }
        //    else
        //    {
        //        ProcessHIDData(inBuffer);
        //        CalcFFBTest();
        //    }

        //    transferComplete = false;
        //    Task transferHidTask = TransferHid();
        //}
        //private static void HIDTransferHandle(object? state)
        //{
        //    if (!transferComplete)
        //    {
        //        return;
        //    }
        //    else
        //    {
        //        ProcessHIDData(inBuffer);
        //        ProcessFFB();
        //    }

        //    transferComplete = false;
        //    Task transferHidTask = TransferHid();
        //}

        //private void btnTest_Click(object sender, EventArgs e)
        //{
        //    Task<ConnectStatus> hidTask = ConnectHid();
        //    if (StartHid(hidTask, HIDTransferHandleTest).Result != 0)
        //    {
        //        Console.WriteLine("Device failed to connect.");
        //        return;
        //    }
        //}

        private void tbPeriAmp_Scroll(object sender, EventArgs e)
        {
            //tbAileronAmpValue = tbPeriAmp.Value;
        }

        private void tbPeriFreq_Scroll(object sender, EventArgs e)
        {
            //tbAileronFreqValue = tbPeriFreq.Value;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            // Initialize stopwatch for force dt calculation
            stopwatch = new Stopwatch();

            rbFromSim.Checked = true;

            //Task<ConnectStatus> hidTask = ConnectHid();
            //if (StartHid(hidTask, HIDTransferHandle).Result == 0)
            //{
            //    btnConnect.Text = "Disconnect";
            //}

            // Initialize force feedback controllers
            elevatorFFBController = new FFBController();
            aileronFFBController = new FFBController();

            // Initialize force effects
            CreateElevatorForces();

            ffbDevice = new FFBDevice();
            ffbDevice.FFBHidDataReadyCallback = ProcessFFBHid;
            ffbDevice.Connect();

            this.Controls.Add(simConnectHelper);
            bool success = ConnectSim();
            if (success)
            {
                btnConnect.Text = "Disconnect Simulator";
            }
            // Start USB device monitor for detecting device arrival and removal of matching USB_VID and PID
            usbDeviceMonitor = new UsbDeviceMonitor(FFBDevice.USB_VID, FFBDevice.USB_PID);
            RegisterUSBNotification();

            simConnectHelper.dataReadyEvent += simConnect_DataReady;
            simConnectHelper.simPauseChangedEvent += simConnect_PauseChanged;
        }

        private void StartMonitoringDevice()
        {
            cts = new CancellationTokenSource();
            Task.Run(() => MonitorDevice(cts.Token));
        }

        private async Task MonitorDevice(CancellationToken token)
        {

        }
        private void UpdateStatusLabel()
        {
            string[] connectionStatus = {"Not Connected",
                "Device Connected, Sim Not Connected",
                "Sim Connected, Device Not Connected",
                "Device and Sim Connected"};
            //int statusIndex = simConnectHelper.Connected << 1 | 
            //simConnectHelper.Connected == true;
        }

        private void RegisterUSBNotification()
        {
            usbDeviceMonitor.RegisterDeviceArrived(
                new EventArrivedEventHandler(usbDeviceConnected));
            usbDeviceMonitor.RegisterDeviceRemoved(
                new EventArrivedEventHandler(usbDeviceDisconnected));
        }

        private void usbDeviceConnected(object sender, EventArrivedEventArgs e)
        {
            ffbDevice.Connect();
            //Task<ConnectStatus> hidTask = ConnectHid();
            //if (StartHid(hidTask, HIDTransferHandle).Result == 0)
            //{
            //    btnConnect.Text = "Disconnect";
            //    Console.WriteLine("Device Connected!");
            //}
            Console.WriteLine("Device Connected!");
        }

        private void usbDeviceDisconnected(object sender, EventArrivedEventArgs e)
        {
            //TODO: Implement
            //ffbDevice.Disconnect();
            Console.WriteLine("Device Disconnected");
        }

        private void cbElevatorFFBEnable_CheckedChanged(object sender, EventArgs e)
        {
            elevatorFFBController.Enable = cbElevatorFFBEnable.Checked;
        }

        private void tbElevatorGain_Scroll(object sender, EventArgs e)
        {
            nudElevatorGain.Value = tbElevatorGain.Value;
            elevatorFFBController.Gain = decimal.ToDouble(nudElevatorGain.Value) / 100.0;
        }

        private void nudElevatorRange_ValueChanged(object sender, EventArgs e)
        {
            elevatorFFBController.Travel = decimal.ToDouble(nudElevatorRange.Value);
            ffbDevice.ControlParams.PitchLimitInMMMax = decimal.ToSingle(nudElevatorRange.Value / 2);
            ffbDevice.ControlParams.PitchLimitInMMMin = decimal.ToSingle(-nudElevatorRange.Value / 2);
            ffbDevice.WriteControlData();
        }

        private void rbTest_CheckedChanged(object sender, EventArgs e)
        {
            if (rbTest.Checked)
            {
                // Make parameters editable
                nudAirSpeed.Enabled = true;
                nudEngineRPM.Enabled = true;

                connectMode = ConnectMode.TEST;
            }
        }

        private void rbFromSim_CheckedChanged(object sender, EventArgs e)
        {
            if (rbFromSim.Checked)
            {
                // Make parameters uneditable
                nudAirSpeed.Enabled = false;
                nudEngineRPM.Enabled = false;

                connectMode = ConnectMode.SIMULATOR;
            }
        }

        private void nudElevatorGain_ValueChanged(object sender, EventArgs e)
        {
            tbElevatorGain.Value = decimal.ToInt32(nudElevatorGain.Value);
            elevatorFFBController.Gain = decimal.ToDouble(nudElevatorGain.Value) / 100.0;
        }

        private void nudElevatorMaxForce_ValueChanged(object sender, EventArgs e)
        {
            tbElevatorMaxForce.Value = decimal.ToInt32(nudElevatorMaxForce.Value);
            elevatorFFBController.MaxForce = decimal.ToDouble(nudElevatorMaxForce.Value);
        }

        private void tbElevatorMaxForce_Scroll(object sender, EventArgs e)
        {
            nudElevatorMaxForce.Value = tbElevatorMaxForce.Value;
            elevatorFFBController.MaxForce = decimal.ToDouble(nudElevatorMaxForce.Value);
        }

        private void tbElevatorAirSpeedStiffness_Scroll(object sender, EventArgs e)
        {
            nudElevatorAirSpeedStiffness.Value = tbElevatorAirSpeedStiffness.Value;
            elevatorAirSpeedStiffness.SpringGain = decimal.ToDouble(nudElevatorAirSpeedStiffness.Value) * 0.00001 / 7000 * 32;
        }

        private void nudElevatorAirSpeedStiffness_ValueChanged(object sender, EventArgs e)
        {
            tbElevatorAirSpeedStiffness.Value = decimal.ToInt32(nudElevatorAirSpeedStiffness.Value);
            elevatorAirSpeedStiffness.SpringGain = decimal.ToDouble(nudElevatorAirSpeedStiffness.Value) * 0.00001 / 7000 * 32;
        }
        private void CreateElevatorForces()
        {
            elevatorAirSpeedStiffness = new AirSpeedStiffness(0.00001);
            elevatorFFBController.Forces.AddRange(elevatorAirSpeedStiffness.Forces);
            elevatorWeight = new ElevatorWeight(0, 0.01);
            elevatorFFBController.Forces.AddRange(elevatorWeight.Forces);
            elevatorGust = new ElevatorGust();
            elevatorFFBController.Forces.AddRange(elevatorGust.Forces);
        }

        private void btnStartStop_Click(object sender, EventArgs e)
        {
            if (ffbDevice.running)
            {
                ffbDevice.Stop();
                stopwatch.Stop();
                btnStartStop.Text = "Start FFB";
            }
            else
            {
                ffbDevice.Start();
                stopwatch.Start();
                btnStartStop.Text = "Stop FFB";
            }
            ffbDevice.WriteControlData();
        }
        private void ProcessFFBHid()
        {
            // Calculate dt (time between calls)
            long currentMilliseconds = stopwatch.ElapsedMilliseconds;
            int dt = (int)(currentMilliseconds - previousMilliseconds);


            // Handle elevator axis
            elevatorPosition = ffbDevice.hidData.pitchAxis;
            ForceSet elevatorForce = elevatorFFBController.CalcForces(elevatorPosition, dt);
            //ffbDevice.forceData.elevatorForce = (float)Utilities.Scale(elevatorForce, -100.0, 100.0, -1.0, 1.0);
            ffbDevice.SetForce(elevatorForce);

            // Handle aileron axis
            aileronPosition = ffbDevice.hidData.rollAxis;
            ForceSet aileronForce = aileronFFBController.CalcForces(aileronPosition, dt);
            //ffbDevice.forceData.aileronForce = (float)Utilities.Scale(aileronForce, -100.0, 100.0, -1.0, 1.0);


            // Update previous elapsed time
            previousMilliseconds = currentMilliseconds;

            simConnectHelper.SetValue(new StructSimVarOut
            {
                elevator = Utilities.Scale(elevatorPosition, -32767, 32768, -16384, 16384),
                aileron = Utilities.Scale(aileronPosition, -32767, 32767, -16384, 16384)
            });

            // --- Update displays ---

            // Update position displays
            //tiAileron.Value = aileronPosition + 32768;
            SetTravelIndicatorValue((int)aileronPosition, tiAileron);
            //lblAileronIndicator.Text = string.Format("{0:0.0} %", aileronPosition / 32767.0 * 100.0);

            //tiElevator.Value = elevatorPosition + 32768;
            SetTravelIndicatorValue((int)elevatorPosition, tiElevator);
            //lblElevatorIndicator.Text = string.Format("{0:0.0} %", elevatorPosition / 32767.0 * 100.0);

            // Update feedback displays
            double maxPitchForce = ffbDevice.capabilities.AxisMaxPower[0];
            if (maxPitchForce != 0)
            {
                int scaledPitchFeedback = (int)Math.Round(Utilities.Scale(
                ffbDevice.GetMeasuredPitchForce(), -maxPitchForce, maxPitchForce,
                -100.0, 100.0));
                SetTravelIndicatorValue(scaledPitchFeedback, tiElevatorFeedback);
                //lblAileronFeedbackIndicator.Text = string.Format("{0:0.0} %", elevatorForce);
            }

            double maxRollForce = ffbDevice.capabilities.AxisMaxPower[1];
            if (maxRollForce != 0)
            {
                int scaledRollFeedback = (int)Math.Round(Utilities.Scale(
                    ffbDevice.GetMeasuredRollForce(), -maxRollForce, maxRollForce,
                    -100.0, 100.0));
                SetTravelIndicatorValue(scaledRollFeedback, tiAileronFeedback);
            }
            //lblElevatorFeedbackIndicator.Text = string.Format("{0:0.0} %", aileronForce);

            if (visualizer != null)
            {
                //visualizer.AddElevatorForceData((int)(elevatorForce*10), dt);
            }
        }

        private void nudAirSpeed_ValueChanged(object sender, EventArgs e)
        {
            //TODO: Add aileron
            elevatorAirSpeedStiffness.AirSpeed = decimal.ToDouble(nudAirSpeed.Value);
        }

        private void nudEngineRPM_ValueChanged(object sender, EventArgs e)
        {
            elevatorWeight.EngineRPM = decimal.ToDouble(nudEngineRPM.Value);
        }

        private void simConnect_DataReady()
        {
            if (connectMode == ConnectMode.SIMULATOR)
            {
                // Update indicators (NumericUpDowns)
                nudAirSpeed.Value = (decimal)simConnectHelper.AirSpeed;
                nudEngineRPM.Value = (decimal)Math.Abs(simConnectHelper.EngineRPM);

                // Update elevator force parameters
                elevatorAirSpeedStiffness.AirSpeed = simConnectHelper.AirSpeed;
                elevatorWeight.EngineRPM = simConnectHelper.EngineRPM;

                elevatorGust.Wind = simConnectHelper.Weather;
                elevatorGust.Aircraft = simConnectHelper.Aircraft;
            }
        }

        private void tbEngineOffWeight_Scroll(object sender, EventArgs e)
        {
            nudEngineOffWeight.Value = tbEngineOffWeight.Value;
            elevatorWeight.Weight = decimal.ToDouble(nudEngineOffWeight.Value);
        }

        private void nudAileronRange_ValueChanged(object sender, EventArgs e)
        {
            aileronFFBController.Travel = decimal.ToDouble(nudAileronRange.Value);
            ffbDevice.ControlParams.RollLimitInDegMax = decimal.ToSingle(nudAileronRange.Value / 2);
            ffbDevice.ControlParams.RollLimitInDegMin = decimal.ToSingle(-nudAileronRange.Value / 2);
            ffbDevice.WriteControlData();
        }

        private void cbDisableInput_CheckedChanged(object sender, EventArgs e)
        {
            simConnectHelper.InputEnabled = !cbDisableInput.Checked;
            if (cbDisableInput.Checked)
            {
                testForceUpdateTimer.Start();
            }
            else
            {
                testForceUpdateTimer.Stop();
            }
        }

        private void btnVisualizer_Click(object sender, EventArgs e)
        {
            visualizer = new();
            visualizer.Show();
        }

        private void testForceUpdateTimer_Tick(object sender, EventArgs e)
        {
            //ProcessFFBHid();
        }

        private void nudEngineOffWeight_ValueChanged(object sender, EventArgs e)
        {
            tbEngineOffWeight.Value = decimal.ToInt32(nudEngineOffWeight.Value);
            elevatorWeight.Weight = decimal.ToDouble(nudEngineOffWeight.Value);
        }

        private void tbEngineCenterStrength_Scroll(object sender, EventArgs e)
        {
            nudEngineCenterStrength.Value = tbEngineCenterStrength.Value;
            elevatorWeight.EngineRPMStrength = tbEngineCenterStrength.Value / 10.0;
        }

        private void nudEngineCenterStrength_ValueChanged(object sender, EventArgs e)
        {
            tbEngineCenterStrength.Value = decimal.ToInt32(nudEngineCenterStrength.Value);
            elevatorWeight.EngineRPMStrength = tbEngineCenterStrength.Value / 10.0;
        }

        private void btnConnectSim_Click(object sender, EventArgs e)
        {
            if (simConnectHelper.Connected)
            {
                DisconnectSim();
                btnConnectSim.Text = "Connect Simulator";
            }
            else
            {
                bool success = ConnectSim();
                if (success)
                {
                    btnConnectSim.Text = "Disconnect Simulator";
                }
            }
        }

        private bool ConnectSim()
        {
            try
            {
                simConnectHelper.OpenConnection();
                Console.WriteLine("Successfully connected to Microsoft Flight Simulator.");
            }
            catch (COMException)
            {
                Console.WriteLine("Failed to connect to Microsoft Flight Simulator.");
            }
            return simConnectHelper.Connected;
        }

        private void DisconnectSim()
        {
            simConnectHelper.CloseConnection();
        }

        private void simConnect_PauseChanged(bool paused)
        {
            if (simConnectHelper.Connected)
            {

                elevatorFFBController.Enable = cbElevatorFFBEnable.Checked && !paused;
            }
        }
    }
}