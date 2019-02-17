using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using BabyFeed.Provider;
using BabyFeed.Domain;
using System.ComponentModel;

namespace BabyFeed.ViewModel
{
    public class EventViewModel : ViewModelBase
    {
        private readonly IDataService _dataService;
        private readonly INavigationService _navigationService;
        private Baby _baby;
        private Event _event;
        private Wizard Wizard { get; set; }

        public string Title { get; set; }

        public RelayCommand CancelCommand { get; set; }

        public EventViewModel(IDataService dataService, INavigationService navigationService)
        {
            _dataService = dataService;
            _navigationService = navigationService;

            if (IsInDesignMode)
            {
                Wizard = new Wizard();

                Wizard.Title = "new event";
                Wizard.AddStep("test", new WhatStepViewModel());
                Title = "Maria's event";
            }

            CancelCommand = new RelayCommand(HandleCancelCommand);
        }


        private void InitWizard(string title)
        {
            Wizard = new Wizard();

            Wizard.Title = title;

            Wizard.AddStep("What?", new WhatStepViewModel());
            Wizard.AddStep("When?", new WhenStepViewModel());

            Wizard.PropertyChanged += new PropertyChangedEventHandler(Wizard_PropertyChanged);
        }

        void Wizard_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "CurrentStep")
            {
                RaisePropertyChanged("CurrentStep");
            }
        }

        public void HandleNewBabyEvent(int babyId)
        {
            _event = null;
            _baby = _dataService.GetBabyById(babyId);
            Title = _baby.Name + "'s event";
            InitWizard("new event");
        }

        public void HandleEditBabyEvent(int eventId)
        {
            _event = _dataService.GetEventById(eventId);
            _baby = _dataService.GetBabyById(_event.BabyId);
            Title = _baby.Name + "'s event";
            InitWizard("edit event");
        }

        public void HandleCancelCommand()
        {
            _navigationService.GoBack();
        }

        public void NextStep()
        {
            if (!Wizard.CanPrevious)
            {

            }
            Wizard.Next();
        }

        public void PreviousStep()
        {
            Wizard.Previous();
        }

        public bool CanNext
        {
            get
            {
                return Wizard.CanNext;
            }
        }

        public bool CanPrevious
        {
            get
            {
                return Wizard.CanPrevious;
            }
        }

        public bool CanFinish
        {
            get
            {
                return Wizard.CanFinish;
            }
        }

        public void RegisterWizardEventHandler(PropertyChangedEventHandler handler)
        {
            Wizard.PropertyChanged += handler;
        }

        public void UnRegisterWizardEventHandler(PropertyChangedEventHandler handler)
        {
            Wizard.PropertyChanged -= handler;
        }

        public string WizardTitle
        {
            get
            {
                return Wizard.Title;
            }
        }

        public WizardStep CurrentStep
        {
            get
            {
                return Wizard.CurrentStep;
            }
        }
    }

}