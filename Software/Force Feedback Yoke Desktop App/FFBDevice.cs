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


namespace Force_Feedback_Yoke_Desktop_App
{
    public class FFBDevice
    {
        public const string USB_VID = "0483";
        public const string USB_PID = "5750";
        private const int outBufferLength = 9;

        private bool connected;

        public delegate void HIDEvent();
        public HIDEvent DataReadyEvent;

        private UsbDeviceMonitor usbDeviceMonitor;
        public delegate void FFBDeviceConnectedEvent();
        public FFBDeviceConnectedEvent DeviceConnectedEvent;
        public delegate void FFBDeviceDisconnectedEvent();
        public FFBDeviceDisconnectedEvent DeviceDisconnectedEvent;

        public bool running { get; set; }

        private IDevice device;
        private byte[] outBuffer = new byte[outBufferLength + 1];
        private byte[] inBuffer;


        private bool transferComplete = false;
        private Timer timer;

        private enum ConnectStatus
        {
            SUCCESS,
            NOT_FOUND,
        };

        public class ControlData
        {
            internal bool modified { get; set; } = true;
            private bool ffbEnabled;
            private int aileronRangeInDeg;
            private int elevatorRangeInMM;

            public ControlData()
            {
                ffbEnabled = false;
                aileronRangeInDeg = 180;
                elevatorRangeInMM = 0;
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
            public int AileronRangeInDeg
            {
                get
                {
                    return aileronRangeInDeg;
                }
                set
                {
                    modified = true;
                    aileronRangeInDeg = value;
                }
            }
            public int ElevatorRangeInMM
            {
                get
                {
                    return elevatorRangeInMM;
                }
                set
                {
                    modified = true;
                    elevatorRangeInMM = value;
                }
            }

        }
        public ControlData controlData { get; set; }
        public class ForceData
        {
            public float aileronForce { get; set; }
            public float elevatorForce { get; set; }
        }
        public ForceData forceData { get; set; }

        public struct HIDData
        {
            public short aileron;
            public short elevator;
        }
        public HIDData hidData { get; set; }

        public bool Connected {
            get
            {
                return connected;
            }
        }

        public FFBDevice()
        {
            connected = false;
            running = false;
            controlData = new ControlData();
            forceData = new ForceData();

            usbDeviceMonitor = new UsbDeviceMonitor(USB_VID, USB_PID);
            usbDeviceMonitor.RegisterDeviceArrived(usbDeviceConnected);
            usbDeviceMonitor.RegisterDeviceRemoved(usbDeviceDisconnected);
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

            connected = true;
            return true;
        }

        public void Disconnect()
        {
            Stop();
            if (timer != null)
            {
                timer.Dispose();
            }

            connected = false;
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

        private void usbDeviceConnected(object sender, EventArrivedEventArgs e)
        {
            // Ensure a device isn't already connected
            if (!connected)
            {
                if (Connect())
                {
                    // Connection successful
                    DeviceConnectedEvent();
                }
            }
        }

        private void usbDeviceDisconnected(object sender, EventArrivedEventArgs e)
        {

            Disconnect();
            DeviceDisconnectedEvent();
        }

        private async Task<ConnectStatus> ConnectHid()
        {
            // Register the factory for creating Hid devices
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
            device = await hidFactory.GetDeviceAsync(deviceDefinitions.First()).ConfigureAwait(false);

            // Initialize device
            await device.InitializeAsync().ConfigureAwait(false);

            return ConnectStatus.SUCCESS;
        }

        private async Task<int> StartHid(Task<ConnectStatus> hidTask, TimerCallback callback)
        {
            //ConnectStatus connectStatus = await hidTask;

            if (hidTask.Result == ConnectStatus.NOT_FOUND)
            {
                return 1;
            }

            timer = new Timer(callback, null, 10000, Timeout.Infinite);

            transferComplete = false;
            outBuffer[0] = 0x01;
            Task transferHidTask = TransferHid();

            return 0;
        }

        private async Task TransferHid()
        {
            inBuffer = await device.WriteAndReadAsync(outBuffer).ConfigureAwait(false);
            transferComplete = true;

            // 1 ms polling rate
            timer.Change(1, Timeout.Infinite);
        }
        private void HIDTransferHandle(object? state)
        {
            if (!transferComplete)
            {
                return;
            }
            else
            {
                ProcessHID(inBuffer);
                DataReadyEvent();
                // Control packet values did not change, transmit FFB
                if (!controlData.modified)
                {
                    ProcessFFB();
                }
                // Control packet values did change, transmit new control packet
                else
                {
                    controlData.modified = false;
                    ProcessControl();
                }
            }

            transferComplete = false;
            Task transferHidTask = TransferHid();
        }

        void ProcessHID(byte[] data)
        {
            // data without reportId
            var values = data[1..];
            hidData = new HIDData
            {
                aileron = ByteArrayToInt16(data[0..2]),
                elevator = ByteArrayToInt16(data[2..4]),
            };
        }
        void ProcessFFB()
        {
            // Clamp aileron force between 0.0 to 1.0
            Math.Clamp(forceData.aileronForce, 0.0f, 1.0f);
            // Convert aileron force float to bytes
            byte[] aileronForceOutBytes = BitConverter.GetBytes(forceData.aileronForce);

            // Clamp elevator force between 0.0 to 1.0
            Math.Clamp(forceData.elevatorForce, 0.0f, 1.0f);
            // Convert elevator force float to bytes
            byte[] elevatorForceOutBytes = BitConverter.GetBytes(forceData.elevatorForce);

            // Copy byte array data to ouput array buffer
            Array.Copy(aileronForceOutBytes, 0, outBuffer, 1, aileronForceOutBytes.Length);
            Array.Copy(elevatorForceOutBytes, 0, outBuffer, aileronForceOutBytes.Length + 1,
                elevatorForceOutBytes.Length);
            outBuffer[0] = 0x01; // reportId byte (force data)
        }

        void ProcessControl()
        {
            outBuffer[0] = 0x02; // reportId byte (control)
            outBuffer[1] = running ? (byte)0x01 : (byte)0x00; // ffb disable

            byte[] aileronRangeInDegBytes = BitConverter.GetBytes(controlData.AileronRangeInDeg);
            Array.Copy(aileronRangeInDegBytes, 0, outBuffer, 2, aileronRangeInDegBytes.Length);

            byte[] elevatorRangeInMMBytes = BitConverter.GetBytes(controlData.ElevatorRangeInMM);
            Array.Copy(elevatorRangeInMMBytes, 0, outBuffer, 6, elevatorRangeInMMBytes.Length);
        }
        private static Int16 ByteArrayToInt16(byte[] arr)
        {
            return (Int16)(((arr[0] & 0xFF)) |
                ((arr[1] & 0xFF) << 8));
        }
    }
}
