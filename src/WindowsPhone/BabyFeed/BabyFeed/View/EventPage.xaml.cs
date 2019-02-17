using Microsoft.Phone.Controls;
using BabyFeed.ViewModel;
using System.ComponentModel;
using Microsoft.Phone.Shell;

namespace BabyFeed.View
{
    /// <summary>
    /// Description for EventPage.
    /// </summary>
    public partial class EventPage : PhoneApplicationPage
    {
        private EventViewModel _vm;
        private ApplicationBarIconButton _cancelBtn;
        private ApplicationBarIconButton _nextBtn;
        private ApplicationBarIconButton _saveBtn;
        private PropertyChangedEventHandler _handler;
        private bool _firstLoad = true;

        /// <summary>
        /// Initializes a new instance of the EventPage class.
        /// </summary>
        public EventPage()
        {
            InitializeComponent();
            _vm = DataContext as EventViewModel;
        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            if (_firstLoad)
            {
                _firstLoad = false;

                _cancelBtn = ApplicationBar.Buttons[0] as ApplicationBarIconButton;
                _nextBtn = ApplicationBar.Buttons[1] as ApplicationBarIconButton;
                _saveBtn = ApplicationBar.Buttons[2] as ApplicationBarIconButton;
                ApplicationBar.Buttons.Clear();
                ApplicationBar.Buttons.Add(_nextBtn);

                if (NavigationContext.QueryString["event"] == "create")
                    _vm.HandleNewBabyEvent(int.Parse(NavigationContext.QueryString["baby"]));
                else
                    _vm.HandleEditBabyEvent(int.Parse(NavigationContext.QueryString["id"]));
            }

            _vm.RegisterWizardEventHandler(_handler = new PropertyChangedEventHandler(HandleWizardPropertyChange));
        }

        protected override void OnNavigatedFrom(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedFrom(e);

            _vm.UnRegisterWizardEventHandler(_handler);
        }

        private void NextBtn_Click(object sender, System.EventArgs e)
        {
            _vm.NextStep();
        }


        void HandleWizardPropertyChange(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "CurrentStep")
            {
                ApplicationBar.Buttons.Clear();
				
                if (_vm.CanNext)
                    ApplicationBar.Buttons.Add(_nextBtn);
                else
                    ApplicationBar.Buttons.Add(_saveBtn);

                if (_vm.CanPrevious)
                    ApplicationBar.Buttons.Add(_cancelBtn);

                _nextBtn.IsEnabled = _vm.CanNext;
                _saveBtn.IsEnabled = _vm.CanFinish;
            }
        }

        private void PhoneApplicationPage_BackKeyPress(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (_vm.CanPrevious)
            {
                _vm.PreviousStep();
                e.Cancel = true;
            }
        }

        private void CancelBtn_Click(object sender, System.EventArgs e)
        {
            _vm.CancelCommand.Execute(null);
        }
    }
}