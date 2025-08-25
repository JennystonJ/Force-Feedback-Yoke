using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32.SafeHandles;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Management;

namespace MSFSForceFeedbackController
{
    internal static class NativeMethods
    {
        internal const Int32 DIGCF_PRESENT = 2;
        internal const Int32 DIGCF_DEVICEINTERFACE = 0x10;

        internal const Int32 FILE_ATTRIBUTE_NORMAL = 0x80;
        internal const Int32 FILE_FLAG_OVERLAPPED = 0x40000000;
        internal const Int32 FILE_SHARE_READ = 1;
        internal const Int32 FILE_SHARE_WRITE = 2;
        internal const UInt32 GENERIC_READ = 0x80000000;
        internal const UInt32 GENERIC_WRITE = 0x40000000;
        internal const Int32 OPEN_EXISTING = 3;

        internal struct SP_DEVICE_INTERFACE_DATA
        {
            internal Int32 cbSize;
            internal Guid interfaceClassGuid;
            internal Int32 flags;
            internal IntPtr reserved;
        }

        internal struct SP_DEVICE_INTERFACE_DETAIL_DATA
        {
            internal Int32 cbSize;
            internal String DevicePath;
        }

        internal struct HIDD_ATTRIBUTES
        {
            internal Int32 size;
            internal UInt16 vendorID;
            internal UInt16 productID;
            internal UInt16 versionNumber;



        }

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern void HidD_GetHidGuid(ref Guid hidGuid);

        [DllImport("hid.dll", SetLastError = true)]
        internal static extern Boolean HidD_GetAttributes
            (SafeFileHandle hidDeviceObject, ref HIDD_ATTRIBUTES attributes);

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        internal static extern IntPtr SetupDiGetClassDevs(
            ref Guid classGuid,
            IntPtr enumerator,
            IntPtr hwndParent,
            Int32 flags);

        [DllImport("setupapi.dll", SetLastError = true)]
        internal static extern Boolean SetupDiEnumDeviceInterfaces(
            IntPtr deviceInfoSet,
            IntPtr deviceInfoData,
            ref Guid interfaceClassGuid,
            Int32 memberIndex,
            ref SP_DEVICE_INTERFACE_DATA deviceInterfaceData);

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        internal static extern Boolean SetupDiGetDeviceInterfaceDetail(
            IntPtr DeviceInfoSet,
            ref SP_DEVICE_INTERFACE_DATA deviceInterfaceData,
            IntPtr deviceInterfaceDetailData,
            Int32 deviceInterfaceDetailDataSize,
            ref Int32 requiredSize,
            IntPtr deviceInfoData);

        [DllImport("setupapi.dll", SetLastError = true)]
        internal static extern Int32 SetupDiDestroyDeviceInfoList(IntPtr deviceInfoSet);

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        internal static extern SafeFileHandle CreateFile(
            String lpFileName,
            UInt32 dwDesiredAccess,
            Int32 dwShareMode,
            IntPtr lpSecurityAttributes,
            Int32 dwCreationDisposition,
            Int32 dwFlagsAndAttributes,
            IntPtr hTemplateFile);
    }

    public class Hid 
    {
        private const String DeviceInterfaceGuid = "{745a17a0-74d3-11d0-b6fe-00a0c90f57da}";

        private enum WmiDeviceProperties
        {
            Caption,
            Description,
            Manufacturer,
            Name,
            CompatibleID,
            PNPDeviceID,
            DeviceID,
            ClassGUID,
            Avilability
        }

        private Boolean deviceReady;
        private ManagementEventWatcher deviceArrivedWatcher;
        private ManagementEventWatcher deviceRemovedWatcher;

        internal NativeMethods.HIDD_ATTRIBUTES deviceAttributes;

        Int16 vendorID = 0x1781;
        Int16 productID = 0x0898;

        SafeFileHandle deviceHandle;



        public Hid()
        {
            var guid = ObtainGuid();
            //var guid = new Guid(DeviceInterfaceGuid);

            /* Request a pointer to device information set */
            var deviceInfoSet = new IntPtr();

            deviceInfoSet = NativeMethods.SetupDiGetClassDevs(
                ref guid,
                IntPtr.Zero,
                IntPtr.Zero,
                NativeMethods.DIGCF_PRESENT |
                    NativeMethods.DIGCF_DEVICEINTERFACE);

            /* Identify device interface */
            Int32 memberIndex = 0;
            var deviceInterfaceData = new NativeMethods.SP_DEVICE_INTERFACE_DATA();
            deviceInterfaceData.cbSize = Marshal.SizeOf(deviceInterfaceData);

            Boolean success = NativeMethods.SetupDiEnumDeviceInterfaces(
                deviceInfoSet,
                IntPtr.Zero,
                ref guid,
                memberIndex,
                ref deviceInterfaceData);

            if (success)
            {
                Console.WriteLine("Success");
            }

            /* Request a structure with device path name */
            Int32 bufferSize = 0;
            IntPtr detailDataBuffer = IntPtr.Zero;

            // Send an invalid request (deviceInterfaceDetailDataSize = 0) to find out correct size
            NativeMethods.SetupDiGetDeviceInterfaceDetail(
                deviceInfoSet,
                ref deviceInterfaceData,
                IntPtr.Zero,
                0,
                ref bufferSize,
                IntPtr.Zero);

            detailDataBuffer = Marshal.AllocHGlobal(bufferSize);

            // Select value of cbsize member depending on system (32-bit or 64-bit)
            Marshal.WriteInt32(detailDataBuffer,
                (IntPtr.Size == 4) ? (4 + Marshal.SystemDefaultCharSize) : 8);

            // Send another request, except with appropriate value for deviceInterfaceDetailDataSize
            NativeMethods.SetupDiGetDeviceInterfaceDetail(
                deviceInfoSet,
                ref deviceInterfaceData,
                detailDataBuffer,
                bufferSize,
                ref bufferSize,
                IntPtr.Zero);

            /* Extract device path name */
            String devicePathName = "";
            // String starts at byte 5, point to byte 5 since the first 4 bytes are cbsize
            var pDevicePathName = new IntPtr(detailDataBuffer.ToInt64() + 4);

            devicePathName = Marshal.PtrToStringAuto(pDevicePathName);
            Console.WriteLine(devicePathName);
            Marshal.FreeHGlobal(detailDataBuffer);

            /* Close communications */
            NativeMethods.SetupDiDestroyDeviceInfoList(deviceInfoSet);

            /* Request a communications handle */
            deviceHandle = NativeMethods.CreateFile(
                devicePathName,
                NativeMethods.GENERIC_READ | NativeMethods.GENERIC_WRITE,
                NativeMethods.FILE_SHARE_READ | NativeMethods.FILE_SHARE_WRITE,
                IntPtr.Zero,
                NativeMethods.OPEN_EXISTING,
                NativeMethods.FILE_ATTRIBUTE_NORMAL | NativeMethods.FILE_FLAG_OVERLAPPED,
                IntPtr.Zero);

            AddDeviceArrivedHandler();


            deviceAttributes.size = Marshal.SizeOf(deviceAttributes);
            success = NativeMethods.HidD_GetAttributes(deviceHandle, ref deviceAttributes);

            if (success)
            {
                if((deviceAttributes.vendorID == vendorID) &&
                    (deviceAttributes.productID == productID))
                {
                    Console.WriteLine("Device detected!");
                }
                else
                {
                    deviceHandle.Close();
                }
            }

            /* Close handle */
            //deviceHandle.Close();

            //deviceAttributes = new HIDD_ATTRIBUTES();
            //deviceAttributes.size = Marshal.SizeOf(deviceAttributes);

            //bool success = HIDD_ATTRIBUTES.HidD_GetAttributes(hidHandle, ref deviceAttributes);
        }

        public Guid ObtainGuid()
        {
            Guid guid = Guid.Empty;
            NativeMethods.HidD_GetHidGuid(ref guid);
            return guid;
        }

        private void AddDeviceArrivedHandler()
        {
            /* Creates and starts handler for detecting new devices */
            const Int32 pollingIntervalSeconds = 3;
            var scope = new ManagementScope("root\\CIMV2");
            scope.Options.EnablePrivileges = true;

            var q = new WqlEventQuery();
            q.EventClassName = "__InstanceCreationEvent";
            q.WithinInterval = new TimeSpan(0, 0, pollingIntervalSeconds);
            q.Condition = @"TargetInstance ISA 'Win32_USBControllerdevice'";
            deviceArrivedWatcher = new ManagementEventWatcher(scope, q);
            deviceArrivedWatcher.EventArrived += DeviceAdded;
            deviceArrivedWatcher.Start();
        }

        private void DeviceAdded(object sender, EventArrivedEventArgs e)
        {
            FindDevice();

            // Perform other actions as needed
        }

        void FindDevice()
        {
            /* Find a device with a specified vender ID and product ID */
            const String deviceIdString = @"USB\VID_1B1C&PID_1B11";

            deviceReady = false;

            // Specify scope and query of searcher instance
            var searcher = new ManagementObjectSearcher("root\\CIMV2",
                "SELECT PNPDeviceID FROM Win32_PnPEntity");

            foreach (ManagementObject queryObj in searcher.Get())
            {
                if (queryObj["PNPDeviceID"].ToString().Contains(deviceIdString))
                {
                    foreach(WmiDeviceProperties wmiDeviceProperty in
                        Enum.GetValues(typeof(WmiDeviceProperties)))
                    {
                        // This logic is inefficient for checking if a property exists
                        try
                        {
                            Console.WriteLine(wmiDeviceProperty.ToString() + ": {0}",
                                queryObj[wmiDeviceProperty.ToString()]);
                        }
                        catch (System.Management.ManagementException ex)
                        { 

                        }
                    }
                    deviceReady = true;
                }
            }
        }

        private void AddDeviceRemovedHandler()
        {
            const Int32 pollingIntervalSeconds = 3;
            var scope = new ManagementScope("root\\CIMV2");
            scope.Options.EnablePrivileges = true;

            var q = new WqlEventQuery();
            q.EventClassName = "__InstanceDeletionEvent";
            q.WithinInterval = new TimeSpan(0, 0, pollingIntervalSeconds);
            q.Condition = @"TargetInstance ISA 'Win32_USBControllerdevice'";
            deviceRemovedWatcher = new ManagementEventWatcher(scope, q);
            deviceRemovedWatcher.EventArrived += DeviceRemoved;
            deviceRemovedWatcher.Start();
        }

        private void DeviceRemoved(object sender, EventArgs e)
        {
            FindDevice();

            // Perform other actions as needed
        }

        
    }
}
