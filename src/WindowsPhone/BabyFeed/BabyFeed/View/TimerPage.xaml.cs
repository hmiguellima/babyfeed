using Microsoft.Phone.Controls;
using BabyFeed.ViewModel;
using System.Windows.Threading;
using System;
using Microsoft.Phone.Shell;

namespace BabyFeed.View
{
    public partial class TimerPage : PhoneApplicationPage
    {
        private TimerViewModel _vm;
        private DispatcherTimer _timer;
        private ApplicationBarIconButton _startBtn;
        private ApplicationBarIconButton _pauseBtn;
        private ApplicationBarIconButton _saveBtn;
        
        public TimerPage()
        {
            InitializeComponent();
            _vm = DataContext as TimerViewModel;
        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            _vm.HandleNewTimerEvent(int.Parse(NavigationContext.QueryString["baby"]));

            _timer = new DispatcherTimer();            
            _timer.Interval = TimeSpan.FromSeconds(1);
            _timer.Tick += new EventHandler(RefreshTimer);
        }

        protected override void OnNavigatedFrom(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedFrom(e);

            if (_timer != null)
            {
                _timer.Stop();
            }
        }

        private void RefreshTimer(object sender, EventArgs e)
        {
            _vm.UpdateTime();
        }

        private void StartBtn_Click(object sender, System.EventArgs e)
        {
        	_timer.Start();
            ApplicationBar.Buttons.Clear();
            ApplicationBar.Buttons.Add(_pauseBtn);
        }

        private void PhoneApplicationPage_Loaded(object sender, System.Windows.RoutedEventArgs e)
        {
            _startBtn = ApplicationBar.Buttons[0] as ApplicationBarIconButton;
            _pauseBtn = ApplicationBar.Buttons[1] as ApplicationBarIconButton;
            _saveBtn = ApplicationBar.Buttons[2] as ApplicationBarIconButton;

            ApplicationBar.Buttons.Clear();
            ApplicationBar.Buttons.Add(_startBtn);
        }

        private void PauseBtn_Click(object sender, System.EventArgs e)
        {
            _timer.Start();
            ApplicationBar.Buttons.Clear();
            ApplicationBar.Buttons.Add(_saveBtn);
            ApplicationBar.Buttons.Add(_startBtn);
        }

        private void SaveBtn_Click(object sender, System.EventArgs e)
        {
        	// TODO: Add event handler implementation here.
        }
    }
}