using Microsoft.Phone.Controls;
using BabyFeed.ViewModel;

namespace BabyFeed.View
{
    /// <summary>
    /// Description for ChartsPage.
    /// </summary>
    public partial class ChartsPage : PhoneApplicationPage
    {
        private ChartsViewModel _vm;

        /// <summary>
        /// Initializes a new instance of the ChartsPage class.
        /// </summary>
        public ChartsPage()
        {
            InitializeComponent();
            _vm = DataContext as ChartsViewModel;
        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            _vm.HandleShowBabyChartsEvent(int.Parse(NavigationContext.QueryString["baby"]));
        }

    }
}