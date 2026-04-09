using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    public class TablessButton : Button
    {

        public new Color ForeColor 
        { 
            get => base.ForeColor;
            set
            {
                base.ForeColor = value;
                _unselectedForeColor = value;
                UpdateColors();
            }
        }

        public new Color BackColor 
        { 
            get => base.BackColor;
            set 
            {
                base.BackColor = value;
                _unselectedBackColor = value;
                UpdateColors();
            } 
        }

        [Description("Fore color of tab button when selected."), Category("Appearance")]
        public Color SelectedForeColor { get; set; }
        private Color _unselectedForeColor;

        [Description("Back color of tab button when selected."), Category("Appearance")]
        public Color SelectedBackColor { get; set; }

        private Color _unselectedBackColor;

        private bool _selected = false;

        public event EventHandler? SelectedChanged;

        public bool Selected
        {
            get => _selected;
            set
            {
                if (_selected != value)
                {
                    _selected = value;
                    UpdateColors();
                    SelectedChanged?.Invoke(this, EventArgs.Empty);
                }
            }
        }

        public TablessButton()
        {
            Click += (s, e) => Selected = true;
        }

        private void UpdateColors()
        {
            base.ForeColor = Selected ? SelectedForeColor : _unselectedForeColor;
            base.BackColor = Selected ? SelectedBackColor : _unselectedBackColor;
        }
    }
}
