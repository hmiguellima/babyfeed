using Microsoft.Phone.Controls;
using GalaSoft.MvvmLight.Messaging;
using BabyFeed.ViewModel;

namespace BabyFeed.View
{
    /// <summary>
    /// Description for BabyPage.
    /// </summary>
    public partial class EventsPage : PhoneApplicationPage
    {
        EventsViewModel _vm;

        public EventsPage()
        {
            InitializeComponent();
            _vm = DataContext as EventsViewModel;
        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e) 
        {
            base.OnNavigatedTo(e);

            _vm.HandleShowBabyEventsEvent(int.Parse(NavigationContext.QueryString["baby"]));
        }

        private void NewEventButton_Click(object sender, System.EventArgs e)
        {
            _vm.NewEventCommand.Execute(null);
        }

        private void TimedEventBtn_Click(object sender, System.EventArgs e)
        {
            _vm.TimedEventCommand.Execute(null);        	
        }

        private void ChartsBtn_Click(object sender, System.EventArgs e)
        {
            _vm.ViewChartsCommand.Execute(null);
        }

        private void TodayBtn_Click(object sender, System.EventArgs e)
        {
        	_vm.TodayCommand.Execute(null);
        }

    }
}