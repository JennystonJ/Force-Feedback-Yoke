using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Force_Feedback_Yoke_Desktop_App
{
    public partial class SettingsTable : UserControl
    {
        private List<SettingsItem> _items = new List<SettingsItem>();

        public event EventHandler? ValueChanged;

        public List<SettingsItem> Items
        {
            get => _items;
            set
            {
                _items = value;
                Invalidate();
            }
        }

        public SettingsTable()
        {
            InitializeComponent();
            Invalidate();
        }

        public new void Invalidate()
        {
            tableLayoutPanel.Controls.Clear();
            tableLayoutPanel.ColumnCount = 2;
            tableLayoutPanel.RowCount = _items.Count;

            tableLayoutPanel.ColumnStyles[0].SizeType = SizeType.AutoSize;
            tableLayoutPanel.RowStyles[0].SizeType = SizeType.AutoSize;

            int currentRow = 0;
            foreach (SettingsItem item in _items)
            {
                tableLayoutPanel.Controls.Add(item.Label);
                tableLayoutPanel.SetCellPosition(item.Label,
                    new TableLayoutPanelCellPosition(0, currentRow));
                item.Label.TextAlign = ContentAlignment.MiddleLeft;

                if (item.Category)
                {
                    tableLayoutPanel.SetColumnSpan(item.Label, 2);
                    item.Label.Margin = new System.Windows.Forms.Padding(3, 9, 3, 9);
                }
                else if (item.Control != null)
                {
                    tableLayoutPanel.Controls.Add(item.Control);
                    tableLayoutPanel.SetCellPosition(item.Control,
                        new TableLayoutPanelCellPosition(1, currentRow));
                    if (item.Control is IValueChanged vc)
                    {
                        vc.ValueChanged += ItemValueChangedEvent;
                    }
                }
                else
                {
                    // Do nothing
                }

                tableLayoutPanel.RowStyles.Add(new RowStyle(SizeType.AutoSize));

                currentRow++;
            }
        }

        private void ItemValueChangedEvent(object? sender, EventArgs e) 
        {
            ValueChanged?.Invoke(sender, e);
        }
    }

    public class SettingsItem
    {
        [Description("Specifies if item is a category (No control)."), Category("Behavior")]
        public bool Category { get; set; } = false;
        [Description("Label displaying name of settings item."), Category("Appearance")]
        public Label Label { get; set; } = new Label();
        [Description("Control associated with settings item."), Category("Behavior")]
        public Control? Control { get; set; } = null;
    }
}
