using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices.Marshalling;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Force_Feedback_Yoke_Desktop_App
{
    public class TablessControl : TabControl
    {
        //[Description("Links tabs to buttons"), Category("Data")]
        //public Dictionary<Button, TabPage> ButtonTabMap { get; set; } = [];

        //[Description("Selected button back color."), Category("Appearance")]

        //public Color ButtonBackColor { get; set; }
        //public Color SelectedButtonBackColor {  get; set; }

        private TablessButtonGroup _tablessButtonGroup = new TablessButtonGroup();
        public TablessButtonGroup TablessButtonGroup 
        {
            get => _tablessButtonGroup;
            set
            {
                if (_tablessButtonGroup != value)
                {
                    _tablessButtonGroup = value;
                    _tablessButtonGroup.SelectedChanged += TablessButtonGroup_SelectedChanged;
                }
            }
        }

        // TODO: Add selected changed event handler so tabless buttons change to keyboard left/right inputs.
        //public TablessControl()
        //{
        //    base.Selected += TablessControl_Selected;
        //}

        private void TablessControl_Selected(object? sender, TabControlEventArgs e)
        {
            base.SelectedIndex = TablessButtonGroup.SelectedIndex;

        }

        private void TablessButtonGroup_SelectedChanged(object? sender, EventArgs e)
        {
            base.SelectedIndex = TablessButtonGroup.SelectedIndex;
        }

        public TablessControl()
        {
            base.Selected += TabUpdate;
            base.SelectedIndexChanged += TabUpdate;
        }

        public void TabUpdate(object? source, EventArgs e)
        {
            TablessButtonGroup.SelectedIndex = base.SelectedIndex;
        }

        //public void ClearButtonEvents()
        //{
        //}

        public void ResetButtons()
        {
            //foreach (var button in ButtonTabMap.Keys)
            //{
            //    //button.
            //}
        }

        protected override void WndProc(ref Message m)
        {
            // Hide tabs by trapping the TCM_ADJUSTRECT message
            if (m.Msg == 0x1328 && !DesignMode) m.Result = 1;
            else base.WndProc(ref m);
        }
    }
}
