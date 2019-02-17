using Microsoft.Phone.Controls;
using GalaSoft.MvvmLight.Messaging;
using BabyFeed.ViewModel;
using System.ComponentModel;
using Microsoft.Phone.Shell;

namespace BabyFeed.View
{
    public partial class BabyPage : PhoneApplicationPage
    {
        BabyViewModel _vm;
        ApplicationBarIconButton _saveBtn;

        /// <summary>
        /// Initializes a new instance of the BabyPage class.
        /// </summary>
        public BabyPage()
        {
            InitializeComponent();
            _vm = DataContext as BabyViewModel;
            _vm.PropertyChanged += HandlePropertyChanged;
        }

        private void HandlePropertyChanged(object o, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "IsFormValid")
                _saveBtn.IsEnabled = _vm.IsFormValid;
        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e) 
        {
            base.OnNavigatedTo(e);

            if (e.NavigationMode == System.Windows.Navigation.NavigationMode.Back)
                return;

            _saveBtn = ApplicationBar.Buttons[0] as ApplicationBarIconButton;


            if (NavigationContext.QueryString["event"] == "create")
                _vm.HandleNewBabyEvent();
            else
                _vm.HandleEditBabyEvent(int.Parse(NavigationContext.QueryString["baby"]));
        }

        private void SaveBtn_Click(object sender, System.EventArgs e)
        {
            _vm.HandleSave();
        }

    }
}