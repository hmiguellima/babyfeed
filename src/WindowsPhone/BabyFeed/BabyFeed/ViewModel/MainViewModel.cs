using GalaSoft.MvvmLight;
using BabyFeed.Domain;
using GalaSoft.MvvmLight.Command;
using System.Windows;
using BabyFeed.Provider;
using System;
using System.Windows.Controls;
using System.Windows.Input;
using GalaSoft.MvvmLight.Messaging;
using Microsoft.Phone.Controls;
using System.Collections.Generic;
using BabyFeed.Events;
using System.Windows.Threading;

namespace BabyFeed.ViewModel
{
    public class MainViewModel : ViewModelBase
    {
        private readonly IDataService _dataService;
        private readonly INavigationService _navigationService;

        public RelayCommand NewBabyCommand { get; set; }
        public RelayCommand<Baby> EditBabyCommand { get; set; }
        public RelayCommand<Baby> DeleteBabyCommand { get; set; }
        public RelayCommand<Baby> ManageBabyEventsCommand { get; set; }

        public BabiesList Babies { get; set; }

        public List<BabyEventGroup> LastEventsByBaby
        {
            get
            {
                return _dataService.ListBabyEventGroups(5);
            }
        }

        public bool LastEventsEmpty
        {
            get
            {
                return LastEventsByBaby.Count == 0;
            }
        }

        public MainViewModel(IDataService dataService, INavigationService navigationService)
        {
            _dataService = dataService;
            _navigationService = navigationService;

            Babies = new BabiesList();

            var babies = dataService.ListBabies();
            
            foreach (Baby baby in babies)
                Babies.Add(baby);

            NewBabyCommand = new RelayCommand(CreateNewBaby);
            EditBabyCommand = new RelayCommand<Baby>(EditBaby);
            DeleteBabyCommand = new RelayCommand<Baby>(DeleteBaby);
            ManageBabyEventsCommand = new RelayCommand<Baby>(ManageBabyEvents);

            Messenger.Default.Register<BabySavedEvent>(this, (evt) => { 
                HandleBabiesChanged();
            });
        }

        private void HandleBabiesChanged()
        {
            var babies = _dataService.ListBabies();

            Babies.Clear();
            foreach (Baby baby in babies)
                Babies.Add(baby);
        }

        private void ManageBabyEvents(Baby baby)
        {
            if (baby is NoBaby)
                CreateNewBaby();
            else
                _navigationService.NavigateTo(new Uri(String.Format(ViewModelLocator.BabyEventsPageQuery, baby.Id), UriKind.Relative));
        }

        private void EditBaby(Baby baby)
        {
            if (baby is NoBaby)
                MessageBox.Show("Sorry, the new baby isn't editable");
            else
                _navigationService.NavigateTo(new Uri(String.Format(ViewModelLocator.EditBabyPageQuery, baby.Id), UriKind.Relative));
        }

        private void DeleteBaby(Baby baby)
        {
            if (baby is NoBaby)
                MessageBox.Show("Sorry, the new baby isn't deletable");
            else
            {
                baby.Delete(_dataService);
                HandleBabiesChanged();
            }
        }

        private void CreateNewBaby()
        {
            _navigationService.NavigateTo(ViewModelLocator.CreateBabyPageUri);
        }
    }
}