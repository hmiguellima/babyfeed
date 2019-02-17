using GalaSoft.MvvmLight;

namespace BabyFeed.ViewModel
{
    public class WhatStepViewModel : ViewModelBase, IValidableContent
    {
        public WhatStepViewModel()
        {
            _selectedIndex = 0;
        }

        public string[] EventTypes
        {
            get
            {
                return new string[] { "<select>", "Left Breast", "Right Breast", "Bottle", "Potty", "Medicine", "Measurement" };
            }
        }

        private int _selectedIndex;

        public int SelectedIndex
        {
            get
            {
                return _selectedIndex;
            }

            set
            {
                _selectedIndex = value;
            }
        }

        public bool IsValid()
        {
            return SelectedIndex > 0;
        }
    }
}