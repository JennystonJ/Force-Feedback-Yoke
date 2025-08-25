using Microsoft.FlightSimulator.SimConnect;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    internal enum DEFINITION
    {
        Def1,
        Def2,
    }

    internal enum REQUEST
    {
        Req1
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct StructSimVar
    {
        public double var1;
        public double var2;
        public double var3;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct StructSimVarOut
    {
        public double elevator;
        public double aileron;
    }


    public class SimConnectHelper : Control
    {
        public delegate void DataReady();
        public DataReady dataReadyCallback;
        public double AirSpeed { get; private set; } = 0;
        public double EngineRPM { get; private set; } = 0;
        public double ElevatorTrim { get; private set; } = 0;

        const int WM_USER_SIMCONNECT = 0x0402;
        SimConnect simConnect = null;
        bool connected = false;

        public bool Connected { get => connected; }
        public bool InputEnabled { get; set; } = true;

        public SimConnectHelper()
        {
           
        }

        public void OpenConnection()
        {
            try
            {
                simConnect = new SimConnect("MSFS Force Feedback Controller",
                    this.Handle, WM_USER_SIMCONNECT, null, 0);

                // Listen to connect message
                simConnect.OnRecvOpen += new SimConnect.
                    RecvOpenEventHandler(SimConnect_OnRecvOpen);

                // Listen to sim object data request
                simConnect.OnRecvSimobjectData += new SimConnect.
                    RecvSimobjectDataEventHandler(SimConnect_OnRecvSimobjectData);
                
                RegisterSimVar();

                Console.WriteLine("Successfully connected to Microsoft Flight Simulator.");
            }
            catch(COMException ex)
            {
                Console.WriteLine("Failed to connect to Microsoft Flight Simulator.");
                throw new COMException();
            }
        }

        public void CloseConnection()
        {
            simConnect.Dispose();
            simConnect = null;
        }

        private void SimConnect_OnRecvOpen(SimConnect sender, SIMCONNECT_RECV_OPEN data)
        {
            Console.WriteLine("Connected!");
            connected = true;
        }

        private void SimConnect_OnRecvSimobjectData(SimConnect sender, SIMCONNECT_RECV_SIMOBJECT_DATA data)
        {
            if(sender != null)
            {
                AirSpeed = ((StructSimVar)data.dwData[0]).var1;
                EngineRPM = ((StructSimVar)data.dwData[0]).var2;
                ElevatorTrim = ((StructSimVar)data.dwData[0]).var3;
                //Console.WriteLine("Air Speed (True): {0:0.00} Engine RPM: {1:0.00}", 
                //    airSpeed,
                //    engineRPM);

                dataReadyCallback();
            }
        }

        private void RegisterSimVar()
        {
            if(simConnect != null)
            {
                try
                {
                    // Add simualator variables to collect
                    simConnect.AddToDataDefinition(DEFINITION.Def1, "AIRSPEED TRUE", "knots",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);

                    simConnect.AddToDataDefinition(DEFINITION.Def1, "GENERAL ENG RPM:1", "rpm",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);

                    simConnect.AddToDataDefinition(DEFINITION.Def1, "ELEVATOR TRIM POSITION", "radians",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);

                    // Specify data format to simulator
                    simConnect.RegisterDataDefineStruct<StructSimVar>(DEFINITION.Def1);

                    // Request specified simulator variables
                    simConnect.RequestDataOnSimObject(REQUEST.Req1, DEFINITION.Def1, 0, SIMCONNECT_PERIOD.SIM_FRAME,
                        SIMCONNECT_DATA_REQUEST_FLAG.DEFAULT, 0, 0, 0);


                    // Add simulator variables to set
                    simConnect.AddToDataDefinition(DEFINITION.Def2, "ELEVATOR POSITION", "position 16k",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                    simConnect.AddToDataDefinition(DEFINITION.Def2, "AILERON POSITION", "position 16k",
                       SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);

                    //simConnect.AddToDataDefinition(DEFINITION.Def2, "YOKE X POSITION", "position 16k",
                    //    SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);

                    //specify data format to simulator
                    simConnect.RegisterDataDefineStruct<StructSimVarOut>(DEFINITION.Def2);
                }
                catch (COMException ex) 
                {
                    Console.WriteLine("RegisterSimVar failed");
                    Debug.WriteLine(ex.Message);
                }
            }
        }

        public void SetValue(StructSimVarOut structSimVarOut)
        {
            if (simConnect != null)
            {
                if (InputEnabled)
                {
                    simConnect.SetDataOnSimObject(DEFINITION.Def2, SimConnect.SIMCONNECT_OBJECT_ID_USER,
                        SIMCONNECT_DATA_SET_FLAG.DEFAULT, structSimVarOut);
                    //Console.WriteLine(value);
                }
            }
        }

        protected override void DefWndProc(ref Message msg)
        {
            // Process message if matched
            if(msg.Msg == WM_USER_SIMCONNECT)
            {
                if(simConnect != null)
                {
                    simConnect.ReceiveMessage();
                }
            }
            else
            {
                base.DefWndProc(ref msg);
            }
        }
    }
}
