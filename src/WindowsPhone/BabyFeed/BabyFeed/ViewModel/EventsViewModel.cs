using System;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;
using GalaSoft.MvvmLight;
using BabyFeed.Provider;
using System.Collections;
using BabyFeed.Domain;
using System.Collections.Generic;
using GalaSoft.MvvmLight.Messaging;
using GalaSoft.MvvmLight.Command;

namespace BabyFeed.ViewModel
{
    public class EventsViewModel : ViewModelBase
    {
        private class DynamicEventList : IList<Event>
        {
            private int _count;
            private Func<int, int, List<Event>> _listEvents;

            public DynamicEventList(int count, Func<int, int, List<Event>> listEvents)
            {
                _count = count;
                _listEvents = listEvents;
            }

            public int Count
            {
                get
                {
                    return _count;
                }
            }

            public Event this[int index]
            {
                get
                {
                    return (_listEvents.Invoke(index, 1)[0]);
                }
                set
                {
                    throw new NotImplementedException();
                }
            }

            public int IndexOf(Event item)
            {
                throw new NotImplementedException();
            }

            public void Insert(int index, Event item)
            {
                throw new NotImplementedException();
            }

            public void RemoveAt(int index)
            {
                throw new NotImplementedException();
            }

            public void Add(Event item)
            {
                throw new NotImplementedException();
            }

            public void Clear()
            {
                throw new NotImplementedException();
            }

            public bool Contains(Event item)
            {
                throw new NotImplementedException();
            }

            public void CopyTo(Event[] array, int arrayIndex)
            {
                throw new NotImplementedException();
            }

            public bool IsReadOnly
            {
                get { throw new NotImplementedException(); }
            }

            public bool Remove(Event item)
            {
                throw new NotImplementedException();
            }

            public IEnumerator<Event> GetEnumerator()
            {
                throw new NotImplementedException();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                throw new NotImplementedException();
            }
        }

                
        private readonly IDataService _dataService;
        private readonly INavigationService _navigationService;
        private Baby _baby;

        private IList<Event> _feedingEvents;
        private IList<Event> _pottyEvents;
        private IList<Event> _medicineEvents;
        private IList<Event> _measureEvents;
        private IList<Event> _napEvents;

        public RelayCommand NewEventCommand { get; set; }
        public RelayCommand<Event> EditEventCommand { get; set; }
        public RelayCommand TimedEventCommand { get; set; }
        public RelayCommand ViewChartsCommand { get; set; }
        public RelayCommand TodayCommand { get; set; }

        public string Title { get; set; }

        public IList<Event> FeedingEvents
        {
            get
            {
                return _feedingEvents;
            }
        }

        private int _feedingEventSelectedIndex=-1;

        public int FeedingEventSelectedIndex {
            get
            {
                return _feedingEventSelectedIndex;
            }

            set
            {
                _feedingEventSelectedIndex = value;
                RaisePropertyChanged("FeedingEventSelectedIndex");
            }
        }

        public bool NoFeedingEvents
        {
            get
            {
                return _feedingEvents.Count == 0;
            }
        }

        public IList<Event> PottyEvents
        {
            get
            {
                return _pottyEvents;
            }
        }

        private int _pottyEventSelectedIndex;
        
        public int PottyEventSelectedIndex {
            get
            {
                return _pottyEventSelectedIndex;
            }

            set
            {
                _pottyEventSelectedIndex = value;
                RaisePropertyChanged("PottyEventSelectedIndex");
            }
        }


        public bool NoPottyEvents
        {
            get
            {
                return _pottyEvents.Count == 0;
            }
        }
        
        public IList<Event> MedicineEvents
        {
            get
            {
                return _medicineEvents;
            }
        }

        private int _medicineEventSelectedIndex;

        public int MedicineEventSelectedIndex {
            get
            {
                return _medicineEventSelectedIndex;
            }

            set
            {
                _medicineEventSelectedIndex = value;
                RaisePropertyChanged("MedicineEventSelectedIndex");
            }
        }

        public bool NoMedicineEvents
        {
            get
            {
                return _medicineEvents.Count == 0;
            }
        }
        
        public IList<Event> MeasureEvents
        {
            get
            {
                return _measureEvents;
            }
        }

        private int _measureEventSelectedIndex;

        public int MeasureEventSelectedIndex {
            get
            {
                return _measureEventSelectedIndex;
            }

            set
            {
                _measureEventSelectedIndex = value;
                RaisePropertyChanged("MeasureEventSelectedIndex");
            }
        }

        public bool NoMeasureEvents
        {
            get
            {
                return _measureEvents.Count == 0;
            }
        }

        public IList<Event> NapEvents
        {
            get
            {
                return _napEvents;
            }
        }

        private int _napEventSelectedIndex;

        public int NapEventSelectedIndex {
            get
            {
                return _napEventSelectedIndex;
            }

            set
            {
                _napEventSelectedIndex = value;
                RaisePropertyChanged("NapEventSelectedIndex");
            }
        }

        public bool NoNapEvents
        {
            get
            {
                return _napEvents.Count == 0;
            }
        }

        public EventsViewModel(IDataService dataService, INavigationService navigationService)
        {
            _dataService = dataService;
            _navigationService = navigationService;

            NewEventCommand = new RelayCommand(CreateNewEvent);
            EditEventCommand = new RelayCommand<Event>(EditEvent);
            TimedEventCommand = new RelayCommand(CreateTimedEvent);
            ViewChartsCommand = new RelayCommand(ViewCharts);
            TodayCommand = new RelayCommand(GotoToday);

            if (IsInDesignMode)
                HandleShowBabyEventsEvent(1);
        }


        private void GotoToday()
        {
            DateTime now = DateTime.Now;

            FeedingEventSelectedIndex = _dataService.CountFeedingEvents(_baby, now) - 1;
            NapEventSelectedIndex = _dataService.CountEvents(_baby, Event.TYPE_NAP, now) - 1;
            PottyEventSelectedIndex = _dataService.CountEvents(_baby, Event.TYPE_POTTY, now) - 1;
            MedicineEventSelectedIndex = _dataService.CountEvents(_baby, Event.TYPE_MEDICINE, now) - 1;
            MeasureEventSelectedIndex = _dataService.CountEvents(_baby, Event.TYPE_MEASURE, now) - 1;
        }

        private void ViewCharts()
        {
            _navigationService.NavigateTo(new Uri(String.Format(ViewModelLocator.ChartsPageUri, _baby.Id), UriKind.Relative));
        }

        private void CreateTimedEvent()
        {
            _navigationService.NavigateTo(new Uri(String.Format(ViewModelLocator.TimerEventPageUri, _baby.Id), UriKind.Relative));
        }

        private void EditEvent(Event evt)
        {
        }


        public void HandleShowBabyEventsEvent(int babyId)
        {
            _baby = _dataService.GetBabyById(babyId);

            Title = _baby.Name + "'s diary";

            _feedingEvents = new DynamicEventList(_dataService.CountFeedingEvents(_baby), (index, count) => { return _dataService.ListFeedEvents(_baby, index, count); });
            _napEvents = new DynamicEventList(_dataService.CountEvents(_baby, Event.TYPE_NAP), (index, count) => { return _dataService.ListEvents(_baby, index, count, Event.TYPE_NAP); });
            _pottyEvents = new DynamicEventList(_dataService.CountEvents(_baby, Event.TYPE_POTTY), (index, count) => { return _dataService.ListEvents(_baby, index, count, Event.TYPE_POTTY); });
            _medicineEvents = new DynamicEventList(_dataService.CountEvents(_baby, Event.TYPE_MEDICINE), (index, count) => { return _dataService.ListEvents(_baby, index, count, Event.TYPE_MEDICINE); });
            _measureEvents = new DynamicEventList(_dataService.CountEvents(_baby, Event.TYPE_MEASURE), (index, count) => { return _dataService.ListEvents(_baby, index, count, Event.TYPE_MEASURE); });

            GotoToday();
        }

        private void CreateNewEvent()
        {
            _navigationService.NavigateTo(new Uri(String.Format(ViewModelLocator.CreateEventPageUri, _baby.Id), UriKind.Relative));
        }

    }
}
