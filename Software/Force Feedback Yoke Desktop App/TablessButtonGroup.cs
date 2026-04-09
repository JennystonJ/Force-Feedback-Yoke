using System;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    public class TablessButtonGroup
    {

        public event EventHandler? SelectedChanged;

        public ObservableCollection<TablessButton> TablessButtons = [];

        private int _selectedIndex = -1;
        public int SelectedIndex
        {
            get => _selectedIndex;
            set
            {
                if (_selectedIndex != value)
                {
                    _selectedIndex = value;
                    UpdateSelectedButton(SelectedIndex);
                    SelectedChanged?.Invoke(this, EventArgs.Empty);
                }
            }
        }

        public TablessButtonGroup()
        {
            TablessButtons.CollectionChanged += TablessButtons_CollectionChanged;
        }

        private void TablessButtons_CollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null)
            {
                foreach (var button in e.NewItems)
                {
                    if (button is TablessButton tablessButton)
                    {
                        tablessButton.SelectedChanged += TablessButton_SelectedChanged;
                        // Assign index of button in collection to tag
                        tablessButton.Tag = TablessButtons.IndexOf(tablessButton);
                    }
                }
            }
        }

        private void TablessButton_SelectedChanged(object? source, EventArgs e)
        {
            if (source is TablessButton tablessButton)
            {
                if (tablessButton.Selected)
                {
                    int btnIndex = tablessButton.Tag is int index ? index : -1;
                    UpdateSelectedButton(btnIndex);
                    SelectedIndex = btnIndex;
                }
            }
        }

        private void UpdateSelectedButton(int index)
        {
            SelectButton(index);
            //// Check if an index is selected
            //if (index > 0)
            //{
            //    TablessButtons[index].Selected = true;
            //}
            //else
            //{
            //    // Leave buttons unselected, do nothing
            //}
        }

        private void SelectButton(int selectedIndex)
        {
            foreach (var button in TablessButtons)
            {
                if (button.Tag is int index)
                {
                    if (index == selectedIndex)
                    {
                        button.Selected = true;
                    }
                    else
                    {
                        button.Selected = false;
                    }
                }
            }
        }


        public void ResetButtons()
        { 
            foreach (var button in TablessButtons)
            {
                button.Selected = false;
            }
        }
    }
}
