using GalaSoft.MvvmLight;
using BabyFeed.Provider;
using System;

namespace BabyFeed.ViewModel
{
    public class TimerViewModel : ViewModelBase
    {
        private readonly IDataService _dataService;
        private readonly INavigationService _navigationService;

        private DateTime _startTime;

        private string _time;

        public string Time
        {
            get
            {
                return _time;
            }

            set
            {
                _time = value;
                RaisePropertyChanged("Time");
            }
        }

        private string _secs;

        public string Secs
        {
            get
            {
                return _secs;
            }

            set
            {
                _secs = value;
                RaisePropertyChanged("Secs");
            }
        }

        
        private string _title;

        public string Title
        {
            get
            {
                return _title;
            }

            set
            {
                _title = value;
                RaisePropertyChanged("Title");
            }
        }

        public string[] EventTypes
        {
            get
            {
                return new string[] { "<Select>", "Left breast", "Right breast", "Bottle", "Nap" };
            }
        }

        public TimerViewModel(IDataService dataService, INavigationService navigationService)
        {
            _dataService = dataService;
            _navigationService = navigationService;

            if (IsInDesignMode)
            {
                Title = "Maria's event";
                Time = "23:59";
                Secs = "59";
            }
        }

        public void HandleNewTimerEvent(int babyId)
        {
            var baby = _dataService.GetBabyById(babyId);

            Title = baby.Name + "'s event";
            _startTime = DateTime.Now;
            Time = "00:00";
            Secs = "00";
        }


        public void UpdateTime()
        {
            Time = DateTime.Now.Subtract(_startTime).ToString("hh\\:mm");
            Secs = DateTime.Now.Subtract(_startTime).ToString("ss");
        }
    }
}