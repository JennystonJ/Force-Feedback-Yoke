using GenericHid;
using Microsoft.Win32.SafeHandles;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Management;
using System.Reflection.Metadata;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace MSFSForceFeedbackController
{
    internal class HidWrapper
    {
        private enum ReportReadOrWritten
        {
            Read,
            Written
        }

        private enum ReportTypes
        {
            Input,
            Output,
            Feature
        }

        private enum SendOrGet
        {
            Send,
            Get
        }

        private enum TransferTypes
        {
            Control,
            Interrupt
        }

        private enum WmiDeviceProperties
        {
            Name,
            Caption,
            Description,
            Manufacturer,
            PNPDeviceID,
            DeviceID,
            ClassGUID
        }

        private Boolean deviceDetected;
        private IntPtr deviceNotificationHandle;
        private FileStream deviceData;
        private SafeFileHandle hidHandle;
        private String hidUsage;
        private ManagementEventWatcher deviceArrivedWatcher;
        private Boolean deviceHandleObtained;
        private ManagementEventWatcher deviceRemovedWatcher;
        private Int32 productId;
        private Int32 vendorId;
        private Boolean periodicTransfersRequested;
        private ReportReadOrWritten readOrWritten;
        private ReportTypes reportType;
        private SendOrGet sendOrGet;
        private Boolean transferInProgress;
        private TransferTypes transferType;

        private readonly DeviceManagement deviceManagement = new DeviceManagement();
        private Hid hid = new Hid();

        private void AddDeviceArrivedHandler()
        {
            const Int32 pollingIntervalSeconds = 3;
            var scope = new ManagementScope("root\\CIMV2");
            scope.Options.EnablePrivileges = true;

            try
            {
                var q = new WqlEventQuery();
                q.EventClassName = "__InstanceCreationEvent";
                q.WithinInterval = new TimeSpan(0, 0, pollingIntervalSeconds);
                q.Condition = @"TargetInstance ISA 'Win32_USBControllerdevice'";
                deviceArrivedWatcher = new ManagementEventWatcher(scope, q);
                deviceArrivedWatcher.EventArrived += DeviceAdded;

                deviceArrivedWatcher.Start();
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.Message);
                if (deviceArrivedWatcher != null)
                    deviceArrivedWatcher.Stop();
            }
        }

        private void AddDeviceRemovedHandler()
        {
            const Int32 pollingIntervalSeconds = 3;
            var scope = new ManagementScope("root\\CIMV2");
            scope.Options.EnablePrivileges = true;

            try
            {
                var q = new WqlEventQuery();
                q.EventClassName = "__InstanceDeletionEvent";
                q.WithinInterval = new TimeSpan(0, 0, pollingIntervalSeconds);
                q.Condition = @"TargetInstance ISA 'Win32_USBControllerdevice'";
                deviceRemovedWatcher = new ManagementEventWatcher(scope, q);
                deviceRemovedWatcher.EventArrived += DeviceRemoved;
                deviceRemovedWatcher.Start();
            }
            catch (Exception e)
            {
                Debug.WriteLine(e.Message);
                if (deviceRemovedWatcher != null)
                    deviceRemovedWatcher.Stop();
            }
        }

        private void CloseCommunications()
        {
            if (deviceData != null)
            {
                deviceData.Close();
            }

            if ((hidHandle != null) && (!(hidHandle.IsInvalid)))
            {
                hidHandle.Close();
            }

            // The next attempt to communicate will get a new handle and FileStreams.

            deviceHandleObtained = false;
        }

        private void DeviceAdded(object sender, EventArrivedEventArgs e)
        {
            try
            {
                Debug.WriteLine("A USB device has been inserted");

                deviceDetected = FindDeviceUsingWmi();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                throw;
            }
        }

        private void DeviceNotificationsStart()
        {
            AddDeviceArrivedHandler();
            AddDeviceRemovedHandler();
        }

        private void DeviceNotificationsStop()
        {
            try
            {
                if (deviceArrivedWatcher != null)
                    deviceArrivedWatcher.Stop();
                if (deviceRemovedWatcher != null)
                    deviceRemovedWatcher.Stop();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                throw;
            }
        }

        private void DeviceRemoved(object sender, EventArgs e)
        {
            try
            {
                Debug.WriteLine("A USB device has been removed");

                deviceDetected = FindDeviceUsingWmi();

                if (!deviceDetected)
                {
                    deviceHandleObtained = false;
                    CloseCommunications();
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                throw;
            }
        }

        private Boolean FindDeviceUsingWmi()
        {
            try
            {
                // Prepend "@" to string below to treat backslash as a normal character (not escape character):

                String deviceIdString = @"USB\VID_" + vendorId.ToString("X4") + "&PID_" + productId.ToString("X4");

                deviceDetected = false;
                var searcher = new ManagementObjectSearcher("root\\CIMV2", "SELECT * FROM Win32_PnPEntity");

                foreach (ManagementObject queryObj in searcher.Get())
                {
                    if (queryObj["PNPDeviceID"].ToString().Contains(deviceIdString))
                    {
                        deviceDetected = true;

                        // Display device properties.

                        foreach (WmiDeviceProperties wmiDeviceProperty in Enum.GetValues(typeof(WmiDeviceProperties)))
                        {
                            Debug.WriteLine(wmiDeviceProperty.ToString() + ": {0}", queryObj[wmiDeviceProperty.ToString()]);
                        }
                    }
                }
                if (!deviceDetected)
                {
                    Debug.WriteLine("Device not found");
                }
                return deviceDetected;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                throw;
            }
        }

        private Boolean FindTheHid()
        {
            var devicePathName = new String[128];
            String myDevicePathName = "";

            try
            {
                deviceHandleObtained = false;
                CloseCommunications();

                // Get the HID-class GUID.

                Guid hidGuid = hid.GetHidGuid();

                String functionName = "GetHidGuid";
                Debug.WriteLine("  GUID for system HIDs: " + hidGuid.ToString());

                //  Fill an array with the device path names of all attached HIDs.

                Boolean availableHids = deviceManagement.FindDeviceFromGuid(hidGuid, ref devicePathName);

                //  If there is at least one HID, attempt to read the Vendor ID and Product ID
                //  of each device until there is a match or all devices have been examined.

                if (availableHids)
                {
                    Int32 memberIndex = 0;

                    do
                    {
                        // Open the handle without read/write access to enable getting information about any HID, even system keyboards and mice.

                        hidHandle = hid.OpenHandle(devicePathName[memberIndex], false);

                        functionName = "CreateFile";
                        Debug.WriteLine("  Returned handle: " + hidHandle);

                        if (!hidHandle.IsInvalid)
                        {
                            // The returned handle is valid, 
                            // so find out if this is the device we're looking for.

                            hid.DeviceAttributes.Size = Marshal.SizeOf(hid.DeviceAttributes);

                            Boolean success = hid.GetAttributes(hidHandle, ref hid.DeviceAttributes);

                            if (success)
                            {
                                Debug.WriteLine("  HIDD_ATTRIBUTES structure filled without error.");
                                Debug.WriteLine("  Structure size: " + hid.DeviceAttributes.Size);
                                Debug.WriteLine("  Vendor ID: " + Convert.ToString(hid.DeviceAttributes.VendorID, 16));
                                Debug.WriteLine("  Product ID: " + Convert.ToString(hid.DeviceAttributes.ProductID, 16));
                                Debug.WriteLine("  Version Number: " + Convert.ToString(hid.DeviceAttributes.VersionNumber, 16));

                                if ((hid.DeviceAttributes.VendorID == vendorId) && (hid.DeviceAttributes.ProductID == productId))
                                {
                                    Debug.WriteLine("  Handle obtained to my device");

                                    //  Display the information in form's list box.

                                    deviceHandleObtained = true;

                                    myDevicePathName = devicePathName[memberIndex];
                                }
                                else
                                {
                                    //  It's not a match, so close the handle.

                                    deviceHandleObtained = false;
                                    hidHandle.Close();
                                }
                            }
                            else
                            {
                                //  There was a problem retrieving the information.

                                Debug.WriteLine("  Error in filling HIDD_ATTRIBUTES structure.");
                                deviceHandleObtained = false;
                                hidHandle.Close();
                            }
                        }

                        //  Keep looking until we find the device or there are no devices left to examine.

                        memberIndex = memberIndex + 1;
                    }
                    while (!((deviceHandleObtained || (memberIndex == devicePathName.Length))));
                }

                if (deviceHandleObtained)
                {
                    //  The device was detected.
                    //  Learn the capabilities of the device.

                    hid.Capabilities = hid.GetDeviceCapabilities(hidHandle);

                    //  Find out if the device is a system mouse or keyboard.

                    hidUsage = hid.GetHidUsage(hid.Capabilities);

                    //  Get the Input report buffer size.

                    GetInputReportBufferSize();

                    //Close the handle and reopen it with read/write access.

                    hidHandle.Close();

                    hidHandle = hid.OpenHandle(myDevicePathName, true);

                    if (hidHandle.IsInvalid)
                    {

                    }
                    else
                    {
                        if (hid.Capabilities.InputReportByteLength > 0)
                        {
                            //  Set the size of the Input report buffer. 

                            var inputReportBuffer = new Byte[hid.Capabilities.InputReportByteLength];

                            deviceData = new FileStream(hidHandle, FileAccess.Read | FileAccess.Write, inputReportBuffer.Length, false);
                        }

                        if (hid.Capabilities.OutputReportByteLength > 0)
                        {
                            Byte[] outputReportBuffer = null;
                        }
                        //  Flush any waiting reports in the input buffer. (optional)

                        hid.FlushQueue(hidHandle);
                    }
                }
                else
                {
                    Debug.WriteLine("Device not found.");
                }
                return deviceHandleObtained;
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
                throw;
            }
        }
    }
}
