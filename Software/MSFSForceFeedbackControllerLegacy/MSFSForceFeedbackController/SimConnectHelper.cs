using Microsoft.FlightSimulator.SimConnect;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MSFSForceFeedbackController
{
    internal enum DEFINITION
    {
        Def1,
        Def2,
        AircraftData,
        WindData,
    }

    internal enum REQUEST
    {
        Req1,
        AircraftReq,
        WindReq,
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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct WeatherData
    {
        public double ambientWindX_mps;   // m/s
        public double ambientWindY_mps;   // m/s (vertical)
        public double ambientWindZ_mps;   // m/s
        public double windVel_kt;         // knots
        public double windDir_true_deg;   // degrees
        public double accelBodyZ_ftps2;   // ft/s^2
        public double ambientDensity_spcf; // slugs/cu.ft
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct AircraftData
    {
        public double incidenceAlpha;      // radians
    }

    internal enum EVENT_ID
    {
        PAUSE,
        RECUR_6Hz,
    }

    public class SimConnectHelper : Control
    {
        public delegate void DataReady();
        public DataReady ?dataReadyEvent;

        public delegate void SystemStateReady(bool paused);
        public SystemStateReady ?simPauseChangedEvent;
        public double AirSpeed { get; private set; } = 0;
        public double EngineRPM { get; private set; } = 0;
        public double ElevatorTrim { get; private set; } = 0;

        public WeatherData Weather { get; private set; }
        public AircraftData Aircraft { get; private set; }


        const int WM_USER_SIMCONNECT = 0x0402;
        SimConnect ?simConnect = null;
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

                // Listen to disconnect message
                simConnect.OnRecvQuit += new SimConnect.
                    RecvQuitEventHandler(SimConnect_OnRecvQuit);

                simConnect.SubscribeToSystemEvent(EVENT_ID.PAUSE, "Pause");
                simConnect.SubscribeToSystemEvent(EVENT_ID.RECUR_6Hz, "6Hz");
                simConnect.OnRecvEvent += new SimConnect.
                    RecvEventEventHandler(SimConnect_OnRecvEvent);

                // Listen to sim object data request
                simConnect.OnRecvSimobjectData += new SimConnect.
                    RecvSimobjectDataEventHandler(SimConnect_OnRecvSimobjectData);
                
                RegisterSimVar();
            }
            catch(COMException)
            {
                throw new COMException();
            }
        }

        public void CloseConnection()
        {
            if (simConnect != null)
            {
                simConnect.Dispose();
                simConnect = null;
            }
        }

        private void SimConnect_OnRecvOpen(SimConnect sender, SIMCONNECT_RECV_OPEN data)
        {
            Console.WriteLine("Connected!");
            connected = true;
        }

        private void SimConnect_OnRecvQuit(SimConnect sender, SIMCONNECT_RECV data)
        {
            Console.WriteLine("Microsoft Flight Simulator disconnected!");
            CloseConnection();
        }

        private void SimConnect_OnRecvSimobjectData(SimConnect sender, SIMCONNECT_RECV_SIMOBJECT_DATA data)
        {
            if (sender != null)
            {
                bool dataReady = false;
                switch ((REQUEST)data.dwRequestID) 
                {
                    case REQUEST.Req1:
                        AirSpeed = ((StructSimVar)data.dwData[0]).var1;
                        EngineRPM = ((StructSimVar)data.dwData[0]).var2;
                        ElevatorTrim = ((StructSimVar)data.dwData[0]).var3;
                        dataReady = true;
                        break;
                    case REQUEST.AircraftReq:
                        Aircraft = ((AircraftData)data.dwData[0]);
                        dataReady = true;
                        break;
                    case REQUEST.WindReq:
                        Weather = ((WeatherData)data.dwData[0]);
                        dataReady = true;
                        break;
                    default:
                        break;
                }
                //Console.WriteLine("Air Speed (True): {0:0.00} Engine RPM: {1:0.00}", 
                //    airSpeed,
                //    engineRPM);

                if (dataReady)
                {
                    dataReadyEvent?.Invoke();
                }
            }
        }

        private void SimConnect_OnRecvEvent(SimConnect sender, SIMCONNECT_RECV_EVENT data)
        {
            if (sender != null)
            {
                switch((EVENT_ID)data.uEventID)
                {
                    case EVENT_ID.PAUSE:
                        simPauseChangedEvent?.Invoke(data.dwData == 1);
                        break;
                    default:
                        break;
                }
            }
            //Console.WriteLine("FFB Paused");
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

                    RegisterAircraftSimVar();
                    RegisterWeatherSimVar();
                }
                catch (COMException ex) 
                {
                    Console.WriteLine("RegisterSimVar failed");
                    Debug.WriteLine(ex.Message);
                }
            }
        }

        private void RegisterAircraftSimVar()
        {
            if(simConnect != null)
            {
                try
                {
                    // Add simualator variables to collect
                    simConnect.AddToDataDefinition(DEFINITION.AircraftData, "INCIDENCE ALPHA", "radians",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);

                    // Specify data format to simulator
                    simConnect.RegisterDataDefineStruct<AircraftData>(DEFINITION.AircraftData);

                    // Request specified simulator variables
                    simConnect.RequestDataOnSimObject(REQUEST.AircraftReq, DEFINITION.AircraftData, 0, SIMCONNECT_PERIOD.SIM_FRAME,
                        SIMCONNECT_DATA_REQUEST_FLAG.DEFAULT, 0, 0, 0);
                }
                catch (COMException ex)
                {
                    Console.WriteLine("RegisterAircraftSimVar failed");
                    Debug.WriteLine(ex.Message);
                }
            }
        }

        private void RegisterWeatherSimVar()
        {
            if (simConnect != null)
            {
                try
                {
                    // Add simualator variables to collect
                    simConnect.AddToDataDefinition(DEFINITION.WindData, "AMBIENT WIND X", "meters per second",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                    simConnect.AddToDataDefinition(DEFINITION.WindData, "AMBIENT WIND Y", "meters per second",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                    simConnect.AddToDataDefinition(DEFINITION.WindData, "AMBIENT WIND Z", "meters per second",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                    simConnect.AddToDataDefinition(DEFINITION.WindData, "AMBIENT WIND VELOCITY", "knots",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                    simConnect.AddToDataDefinition(DEFINITION.WindData, "AMBIENT WIND DIRECTION", "degrees",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                    simConnect.AddToDataDefinition(DEFINITION.WindData, "ACCELERATION BODY Z", "feet per second squared",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);
                    simConnect.AddToDataDefinition(DEFINITION.WindData, "AMBIENT DENSITY", "slugs per cubic feet",
                        SIMCONNECT_DATATYPE.FLOAT64, 0.0f, SimConnect.SIMCONNECT_UNUSED);

                    // Specify data format to simulator
                    simConnect.RegisterDataDefineStruct<WeatherData>(DEFINITION.WindData);

                    // Request specified simulator variables
                    simConnect.RequestDataOnSimObject(REQUEST.WindReq, DEFINITION.WindData, 0, SIMCONNECT_PERIOD.SIM_FRAME,
                        SIMCONNECT_DATA_REQUEST_FLAG.DEFAULT, 0, 0, 0);
                }
                catch (COMException ex)
                {
                    Console.WriteLine("RegisterWeatherSimVar failed");
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
