using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Device.Net;
using Hid.Net.Windows;
using System.Management;
using System.Runtime.InteropServices;
using Timer = System.Threading.Timer;
using Hid.Net;
using System.Runtime.CompilerServices;
using System.IO;
using Microsoft.Win32.SafeHandles;
using System.Formats.Asn1;
using System.Collections.Concurrent;


namespace Force_Feedback_Yoke_Desktop_App
{
    public class FFBDevice
    {

        [DllImport("hid.dll", SetLastError = true)]
        static extern bool HidD_GetFeature(IntPtr hidDeviceObject, byte[] reportBuffer, int reportBufferLength);
        [DllImport("hid.dll", SetLastError = true)]
        static extern bool HidD_SetFeature(IntPtr hidDeviceObject, byte[] reportBuffer, int reportBufferLength);
      
        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        static extern SafeFileHandle CreateFile(
            string lpFileName,
            uint dwDesiredAccess,
            uint dwShareMode,
            IntPtr lpSecurityAttributes,
            uint dwCreationDisposition,
            uint dwFlagsAndAttributes,
            IntPtr hTemplateFile);

        // Access and share flags
        const uint GENERIC_READ = 0x80000000;
        const uint GENERIC_WRITE = 0x40000000;
        const uint FILE_SHARE_READ = 1;
        const uint FILE_SHARE_WRITE = 2;
        const uint OPEN_EXISTING = 3;

        private const int HID_CONTROL_REPORT_ID = 1;
        private const int HID_IN_REPORT_ID = 2;
        private const int HID_OUT_REPORT_ID = 3;
        private const int HID_CAPABILITIES_REPORT_ID = 4;

        private const int outBufferLength = 9;

        public event EventHandler? DataReadyEvent = null;
        public event EventHandler? DeviceConnectedEvent = null;
        public event EventHandler? DeviceDisconnectedEvent = null;

        public bool running { get; set; }

        private SafeFileHandle deviceHandle;
        private UsbDeviceMonitor monitor;
        private IDevice device;
        private byte[] outBuffer = new byte[outBufferLength + 1];

        private byte[] inBuffer;

        private bool transferComplete = false;
        private Timer timer;

        private Task ?hidReaderTask = null;
        private Task ?hidWorkerTask = null;

        private CancellationTokenSource hidReaderCts;
        private CancellationTokenSource hidWorkerCts;

        public const string USB_VID = "0483";
        public const string USB_PID = "5750";

        public const int FFB_HID_NUM_AXIS = 2;
        public const int FFB_HID_PITCH_INDEX = 0;
        public const int FFB_HID_ROLL_INDEX = 1;

        private ForceSet hardwareForce = new ForceSet();

        private readonly SemaphoreSlim transferLock = new SemaphoreSlim(1, 1);
        private readonly ConcurrentQueue<byte[]> hidCommandQueue = new ConcurrentQueue<byte[]>();

        public bool Connected { get; private set; }

        private enum ConnectStatus
        {
            SUCCESS,
            NOT_FOUND,
        };

        public class CapabilityData
        {
            internal bool CapabilityInitialized { get; set; } = false;
            public float PitchTravelRange { get; internal set; }
            public float RollTravelRange { get; internal set; }
            public float PitchMaxForce { get; internal set; }
            public float RollMaxForce { get; internal set; }
        }

        public class ControlData
        {
            internal bool modified { get; set; } = true;
            private bool ffbEnabled;
            private float pitchLimitInMMMin;
            private float pitchLimitInMMMax;
            private float rollLimitInDegMin;
            private float rollLimitInDegMax;


            public ControlData()
            {
                ffbEnabled = false;
                pitchLimitInMMMin = -50;
                pitchLimitInMMMax = 50;
                rollLimitInDegMin = -90;
                rollLimitInDegMax = 90;
            }
            public bool FFBEnabled
            {
                get
                {
                    return ffbEnabled;
                }
                set
                {
                    modified = true;
                    ffbEnabled = value;
                }
            }

            public float PitchLimitInMMMin
            {
                get { return pitchLimitInMMMin; }
                set
                {
                    modified = true;
                    pitchLimitInMMMin = value;
                }
            }
            public float PitchLimitInMMMax
            {
                get { return pitchLimitInMMMax; }
                set
                {
                    modified = true;
                    pitchLimitInMMMax = value;
                }
            }

            public float RollLimitInDegMin
            {
                get { return rollLimitInDegMin; }
                set
                {
                    modified = true;
                    rollLimitInDegMin = value;
                }
            }
            public float RollLimitInDegMax
            {
                get { return rollLimitInDegMax; }
                set
                {
                    modified = true;
                    rollLimitInDegMax = value;
                }
            }
        }

        private ControlData controlData;
        public ControlData ControlParams {
            get 
            {
                return controlData; 
            } 
            set 
            { 
                controlData = value;
            } 
        }
        public CapabilityData Capabilities { get; set; }
        public class ForceReport
        {
            internal byte ReportId { get; set; }
            public float SpringForce { get; set; }
        }
        public ForceReport Force { get; set; }

        public struct HIDData
        { 
            public short pitchAxis;
            public short rollAxis;
            public short pitchForce;
            public short rollForce;
        }
        public HIDData HidData { get; set; }

        public FFBDevice()
        {
            running = false;
            controlData = new ControlData();
            Capabilities = new CapabilityData();
            Force = new ForceReport();

            hidReaderCts = new CancellationTokenSource();
            hidWorkerCts = new CancellationTokenSource();

            monitor = new UsbDeviceMonitor(USB_VID, USB_PID);
            monitor.RegisterDeviceArrived(new EventArrivedEventHandler(UsbDeviceConnected));
            monitor.RegisterDeviceRemoved(new EventArrivedEventHandler(UsbDeviceDisconnected));
        }

        private void UsbDeviceConnected(object sender, EventArrivedEventArgs e)
        {
            if(Connect())
            {
                DeviceConnectedEvent?.Invoke(this, EventArgs.Empty);
            }
        }

        private void UsbDeviceDisconnected(object sender, EventArrivedEventArgs e)
        {
            DeviceConnectedEvent?.Invoke(this, EventArgs.Empty);
        }

        public bool Connect()
        {

            Task<ConnectStatus> hidTask = ConnectHid();
            if (hidTask.Result == ConnectStatus.NOT_FOUND)
            {
                return false;
            }
            if (StartHid(hidTask, HIDTransferHandle).Result != 0)
            {
                Console.WriteLine("Device failed to connect.");
                return false;
            }

            Connected = true;
            return true;
        }

        public void Disconnect()
        {
            if (hidReaderTask != null)
            {
                hidReaderCts.Cancel();
            }
            if(hidWorkerTask != null)
            {
                hidCommandQueue.Enqueue(PrepareFFBReport(ForceSet.Empty, ForceSet.Empty));
                hidWorkerCts.Cancel();
            }

            deviceHandle?.Close();
            device?.Close();

            Connected = false;
        }

        public void Start()
        {
            running = true;
            controlData.FFBEnabled = true;
        }

        public void Stop()
        {
            running = false;
            controlData.FFBEnabled = false;
        }

        public void WriteControlData()
        {
            hidCommandQueue.Enqueue(ConvertControlToReport());
        }

        public void SetForces(ForceSet pitchForce, ForceSet rollForce)
        {
            byte[] forceReport = PrepareFFBReport(pitchForce, rollForce);
            hidCommandQueue.Enqueue(forceReport);
        }

        public double GetMeasuredPitchForce()
        {
            if (Capabilities.CapabilityInitialized &&
                Capabilities.PitchMaxForce > 0)
            {
                return Utilities.Scale(HidData.pitchForce, -32767, 32767,
                    -Capabilities.PitchMaxForce,
                    Capabilities.PitchMaxForce);
            }
            else
            {
                // Axis max power is invalid
                return 0.0;
            }
        }
        public double GetMeasuredRollForce()
        {
            if (Capabilities.CapabilityInitialized &&
                  Capabilities.RollMaxForce > 0)
            {
                return Utilities.Scale(HidData.rollForce, -32767, 32767,
                    -Capabilities.RollMaxForce,
                    Capabilities.RollMaxForce);
            }
            else
            {
                // Axis max power is invalid
                return 0.0;
            }
        }

        private async Task<ConnectStatus> ConnectHid()
        {
            
            //// Register the factory for creating Hid devices
            uint vid = Convert.ToUInt32(USB_VID, 16);
            uint pid = Convert.ToUInt32(USB_PID, 16);
            var hidFactory = new FilterDeviceDefinition(vid, pid).CreateWindowsHidDeviceFactory();
            //var hidFactory = new FilterDeviceDefinition(0x0483, 0x5750, 65280).CreateWindowsHidDeviceFactory();//, "Force Feedback Yoke",
            //new Guid("{745A17A0-74D3-11D0-B6Fe-00A0C90F57DA}")).CreateWindowsHidDeviceFactory();

            // Get connected device definitions
            var deviceDefinitions = (await hidFactory.GetConnectedDeviceDefinitionsAsync().
                ConfigureAwait(false)).ToList();

            if (deviceDefinitions.Count == 0)
            {
                Console.WriteLine("Device not found.");
                return ConnectStatus.NOT_FOUND;
            }

            Console.WriteLine("Device found.");

            // Obtain device from definitions
            string devicePath = deviceDefinitions.First().DeviceId;

            deviceHandle = CreateFile(
                devicePath,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                IntPtr.Zero,
                OPEN_EXISTING,
                0,
                IntPtr.Zero);

            if(deviceHandle.IsInvalid)
            {
                Console.WriteLine("Device not found.");
                return ConnectStatus.NOT_FOUND;
            }

            device = await hidFactory.GetDeviceAsync(deviceDefinitions.First()).ConfigureAwait(false);

            // Initialize device
            await device.InitializeAsync().ConfigureAwait(false);


            // Create request buffer (must be 1 byte larger than report buffer)
            var buffer = new byte[65];
            buffer[1] = 0x02;

            //var readBuffer = await device.WriteAndReadAsync(buffer).ConfigureAwait(false);
            return ConnectStatus.SUCCESS;
        }

        private async Task<int> StartHid(Task<ConnectStatus> hidTask, TimerCallback callback)
        {
            //ConnectStatus connectStatus = await hidTask;

            if (hidTask.Result == ConnectStatus.NOT_FOUND)
            {
                return 1;
            }

            // Obtain force feedback capabilities 
            //IntPtr handle = device.
            //byte[] reportIdBuffer = new byte[1];
            //buffer[0] = HID_CAPABILITIES_REPORT_ID;

            //timer = new Timer(callback, null, 10000, Timeout.Infinite);

            transferComplete = true;
            outBuffer = new byte[19];
            outBuffer[0] = HID_OUT_REPORT_ID;
            RefreshCapabilities();

            hidReaderCts = new CancellationTokenSource();
            hidWorkerCts = new CancellationTokenSource();

            hidWorkerTask = HidWorkerLoop(hidWorkerCts.Token);
            hidReaderTask = HidReaderLoop(hidReaderCts.Token);
            //Task transferHidTask = TransferHid();
            //((IHidDevice)device).

            return 0;
        }

        private async Task<byte[]> TransferHid(byte[] outBuffer)
        {
           return await device.WriteAndReadAsync(outBuffer);
        }

        private async Task<byte[]> ReadCapabilities()
        {
            byte[] featureReport = new byte[19];
            featureReport[0] = HID_CAPABILITIES_REPORT_ID;
            await Task.Run(() => HidD_GetFeature(deviceHandle.DangerousGetHandle(), featureReport, featureReport.Length));
            return featureReport;
        }
        private void HIDTransferHandle(object? state)
        {
            if (!transferComplete)
            {
                return;
            }
            else if (!Capabilities.CapabilityInitialized)
            {
                byte[] featureReport = ReadCapabilities().Result;
                ProcessCapabilities(featureReport);
            }
            //else if(ControlParams.modified)
            //{
            //    WriteControl(ConvertControlToReport());
            //    ControlParams.modified = false;
            //}
            else
            {
                switch (inBuffer[0])
                {
                    case HID_IN_REPORT_ID:
                        ProcessHID(inBuffer);
                        DataReadyEvent?.Invoke(this, EventArgs.Empty);
                        break;
                    //case HID_CAPABILITIES_REPORT_ID:
                    //    ProcessCapabilities(inBuffer);
                    //    break;
                    default:
                        // Do nothing
                        break;

                }
            }

            //PrepareFFBReport();
            //Task transferHidTask = TransferHid();
        }

        void ProcessHID(byte[] data)
        {
            // data without reportId
            var values = data[1..];
            HidData = new HIDData
            {
                pitchAxis = ByteArrayToInt16(values[0..2]),
                rollAxis = ByteArrayToInt16(values[2..4]),
                pitchForce = ByteArrayToInt16(values[4..6]),
                rollForce = ByteArrayToInt16(values[6..8])
            };
        }
        byte[] PrepareFFBReport(ForceSet pitchForce, ForceSet rollForce)
        {
            byte[] outBuffer = new byte[25];
            outBuffer[0] = HID_OUT_REPORT_ID;

            float maxForce = Capabilities.PitchMaxForce;

            float[] forces = new float[6];
            // Clamp all forces
            // Pitch
            forces[0] = (float)Math.Clamp(pitchForce.Constant, -maxForce, maxForce);
            forces[1] = (float)Math.Clamp(pitchForce.Spring, -maxForce, maxForce);
            forces[2] = (float)Math.Clamp(pitchForce.Damper, -maxForce, maxForce);

            // Roll
            forces[3] = (float)Math.Clamp(rollForce.Constant, -maxForce, maxForce);
            forces[4] = (float)Math.Clamp(rollForce.Spring, -maxForce, maxForce);
            forces[5] = (float)Math.Clamp(rollForce.Damper, -maxForce, maxForce);

            // Copy roll and pitch forces to byte array
            byte[] forceOutBytes = new byte[sizeof(float) * forces.Length];
            for(int i = 0; i < forces.Length; i++)
            {
                byte[] bytes = BitConverter.GetBytes(forces[i]);
                Array.Copy(bytes, 0, forceOutBytes, i * sizeof(float), bytes.Length);
            }

            Array.Copy(forceOutBytes, 0, outBuffer, 1, forceOutBytes.Length);

            return outBuffer;
        }
        private async Task WriteControl(byte[] controlReport)
        {
            await Task.Run(() => HidD_SetFeature(deviceHandle.DangerousGetHandle(), controlReport, controlReport.Length));
        }
        private void RefreshCapabilities()
        {
            hidCommandQueue.Enqueue(new byte[] { HID_CAPABILITIES_REPORT_ID });
        }
        private async Task HidReaderLoop(CancellationToken cancellationToken)
        {
            while (true) 
            { 
                await transferLock.WaitAsync();
                try
                {
                    byte[] hidBuffer = await device.ReadAsync(cancellationToken);
                    if (hidBuffer[0] == HID_IN_REPORT_ID)
                    {
                        ProcessHID(hidBuffer);
                    }
                }
                finally
                {
                    transferLock.Release();
                }

                DataReadyEvent?.Invoke(this, EventArgs.Empty);

                if(cancellationToken.IsCancellationRequested)
                {
                    return;
                }

                await Task.Delay(2);
            }
        }
        private async Task HidWorkerLoop(CancellationToken cancellationToken)
        {
            while (true)
            {
                if(hidCommandQueue.TryDequeue(out var command))
                {
                    //bool hidReceived = false;
                    await transferLock.WaitAsync();
                    try
                    {
                        switch(command[0])
                        {
                            case HID_CONTROL_REPORT_ID:
                                await WriteControl(command);
                                break;
                            case HID_IN_REPORT_ID:
                                break;
                            case HID_OUT_REPORT_ID:
                                await device.WriteAsync(command);
                                break;
                            case HID_CAPABILITIES_REPORT_ID:
                                byte[] capabilitiesBuffer = await ReadCapabilities();
                                ProcessCapabilities(capabilitiesBuffer);
                                // Re-read capabilities if it's not yet initialized
                                if(!Capabilities.CapabilityInitialized)
                                {
                                    RefreshCapabilities();
                                }
                                break;
                            default:
                                // Do nothing
                                break;
                        }

                    }
                    finally
                    {
                        transferLock.Release(); 
                    }
                }
                else
                {
                    if(cancellationToken.IsCancellationRequested)
                    {
                        return;
                    }
                    await Task.Delay(1);
                }
            }
        }
        private byte[] ConvertControlToReport()
        {
            byte[] buffer = new byte[18];
            buffer[0] = HID_CONTROL_REPORT_ID; // reportId byte (control)
            buffer[1] = controlData.FFBEnabled ? (byte)0x01 : (byte)0x00; // ffb disable

            byte[] pitchLimitInMMMin = BitConverter.GetBytes(controlData.PitchLimitInMMMin);
            Array.Copy(pitchLimitInMMMin, 0, buffer, 2, pitchLimitInMMMin.Length);

            byte[] pitchLimitInMMMax = BitConverter.GetBytes(controlData.PitchLimitInMMMax);
            Array.Copy(pitchLimitInMMMax, 0, buffer, 6, pitchLimitInMMMax.Length);

            byte[] rollLimitInDegMin = BitConverter.GetBytes(controlData.RollLimitInDegMin);
            Array.Copy(rollLimitInDegMin, 0, buffer, 10, rollLimitInDegMin.Length);

            byte[] rollLimitInDegMax = BitConverter.GetBytes(controlData.RollLimitInDegMax);
            Array.Copy(rollLimitInDegMax, 0, buffer, 14, rollLimitInDegMax.Length);

            return buffer;
        }

        private void ProcessCapabilities(byte[] data)
        {
            // data without reportId
            var values = data[1..];
            Capabilities.CapabilityInitialized = values[0] == 1;
            Capabilities.PitchTravelRange = BitConverter.ToSingle(values, 1);
            Capabilities.RollTravelRange = BitConverter.ToSingle(values, 5);
            Capabilities.PitchMaxForce = BitConverter.ToSingle(values, 9);
            Capabilities.RollMaxForce = BitConverter.ToSingle(values, 13);
            //Capabilities.MaxSupportedForces = values[17];
        }
        private static Int16 ByteArrayToInt16(byte[] arr)
        {
            return (Int16)(((arr[0] & 0xFF)) |
                ((arr[1] & 0xFF) << 8));
        }
    }
}
