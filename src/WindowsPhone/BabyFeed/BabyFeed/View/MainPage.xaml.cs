using Microsoft.Phone.Controls;
using System;
using GalaSoft.MvvmLight.Command;
using BabyFeed.ViewModel;
using GalaSoft.MvvmLight.Messaging;

namespace BabyFeed.View
{
    /// <summary>
    /// Description for MainPage.
    /// </summary>
    public partial class MainPage : PhoneApplicationPage
    {
        /// <summary>
        /// Initializes a new instance of the MainPage class.
        /// </summary>
        public MainPage()
        {
            InitializeComponent();

        }


        private void NewBabyButton_Click(object sender, EventArgs e)
        {
            ((MainViewModel)DataContext).NewBabyCommand.Execute(null);
        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            BabiesList.SelectedIndex = -1;
        }

    }
}