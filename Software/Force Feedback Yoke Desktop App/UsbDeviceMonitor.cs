using System;
using System.Management;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal class UsbDeviceMonitor
    {
        bool deviceConnected;

        private ManagementEventWatcher deviceArrivalWatcher;
        private ManagementEventWatcher deviceRemovalWatcher;

        private EventArrivedEventHandler connected;
        private EventArrivedEventHandler disconnected;

        private string vid;
        private string pid;

        public UsbDeviceMonitor(string vid, string pid)
        {
            this.vid = vid;
            this.pid = pid;

            deviceConnected = DeviceFound();

            SetupDeviceArrivalWatcher();
            SetupDeviceRemovalWatcher();
        }

        public void RegisterDeviceArrived(EventArrivedEventHandler e)
        {
            connected = e;
        }

        public void RegisterDeviceRemoved(EventArrivedEventHandler e)
        {
            disconnected = e;
        }

        private void SetupDeviceArrivalWatcher()
        {
            deviceArrivalWatcher = new ManagementEventWatcher();
            deviceArrivalWatcher.EventArrived += new EventArrivedEventHandler(DeviceArrived);
            deviceArrivalWatcher.Query = new WqlEventQuery(
                "SELECT * FROM Win32_DeviceChangeEvent WHERE EventType = 2");
            deviceArrivalWatcher.Start();
        }

        private void SetupDeviceRemovalWatcher()
        {
            deviceRemovalWatcher = new ManagementEventWatcher();
            deviceRemovalWatcher.EventArrived += new EventArrivedEventHandler(DeviceRemoved);
            deviceRemovalWatcher.Query = new WqlEventQuery(
                "SELECT * FROM Win32_DeviceChangeEvent WHERE EventType = 3");
            deviceRemovalWatcher.Start();
        }

        private void DeviceArrived(object sender, EventArrivedEventArgs e)
        {
            //Console.WriteLine("A USB device has been connected.");
            if (!deviceConnected && DeviceFound())
            {
                deviceConnected = true;
                connected.Invoke(sender, e);
            }
        }

        private void DeviceRemoved(object sender, EventArrivedEventArgs e)
        {
            //Console.WriteLine("A USB device has been disconnected.");
            if (deviceConnected && !DeviceFound())
            {
                deviceConnected = false;
                disconnected.Invoke(sender, e);
            }
        }

        private bool DeviceFound()
        {
            bool found = false;
            var searcher = new ManagementObjectSearcher("" +
                "SELECT * FROM Win32_PnPEntity WHERE DeviceID LIKE 'USB%'");

            foreach (ManagementObject device in searcher.Get())
            {
                string deviceId = device["DeviceID"].ToString();
                if (deviceId.Contains($"VID_{vid}&PID_{pid}"))
                {
                    //Console.WriteLine(
                    //    $"Device: {device["Name"]}, DeviceID: {device["DeviceID"]}");
                    found = true;
                }
            }   

            return found;
        }

        public void Dispose()
        {
            deviceArrivalWatcher.Stop();
            deviceArrivalWatcher.Dispose();
            deviceRemovalWatcher.Stop();
            deviceRemovalWatcher.Dispose();
        }
    }
}
