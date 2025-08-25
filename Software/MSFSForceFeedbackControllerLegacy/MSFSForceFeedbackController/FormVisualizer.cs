using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;                  
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MSFSForceFeedbackController
{

    public partial class FormVisualizer : Form
    {
        public FormVisualizer()
        {
            InitializeComponent();
        }

        private void FormVisualizer_Load(object sender, EventArgs e)
        {
            graphUpdateTimer.Start();
        }

        private void timerGraph_Tick(object sender, EventArgs e)
        {
            lgForce.Shift((decimal)4);
        }
        public void AddElevatorForceData(int force, int dt)
        {
            lgForce.AddPoint(new Point(dt + (int)lgForce.Time, force));
        }
    }
}
