/*
  In App.xaml:
  <Application.Resources>
      <vm:ViewModelLocatorTemplate xmlns:vm="clr-namespace:BabyFeed.ViewModel"
                                   x:Key="Locator" />
  </Application.Resources>
  
  In the View:
  DataContext="{Binding Source={StaticResource Locator}, Path=ViewModelName}"
*/

using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Ioc;
using Microsoft.Practices.ServiceLocation;
using BabyFeed.Domain;
using BabyFeed.Provider;
using System;

namespace BabyFeed.ViewModel
{
    public class ViewModelLocator
    {
        public static readonly Uri MainPageUri = new Uri("/View/MainPage.xaml", UriKind.Relative);
        public static readonly Uri CreateBabyPageUri = new Uri("/View/BabyPage.xaml?event=create", UriKind.Relative);
        public static readonly string EditBabyPageQuery = "/View/BabyPage.xaml?event=edit&baby={0}";
        public static readonly string BabyEventsPageQuery = "/View/EventsPage.xaml?baby={0}";
        public static readonly string CreateEventPageUri = "/View/EventPage.xaml?event=create&baby={0}";
        public static readonly string TimerEventPageUri = "/View/TimerPage.xaml?baby={0}";
        public static readonly string ChartsPageUri = "/View/ChartsPage.xaml?baby={0}";

        static ViewModelLocator()
        {
            ServiceLocator.SetLocatorProvider(() => SimpleIoc.Default);

            if (ViewModelBase.IsInDesignModeStatic)
            {
                SimpleIoc.Default.Register<IDataService, Design.DesignDataService>();
            }
            else
            {
                SimpleIoc.Default.Register<IDataService, SqlDataService>();
            }

            SimpleIoc.Default.Register<INavigationService, WPNavigationService>();
            SimpleIoc.Default.Register<MainViewModel>();
            SimpleIoc.Default.Register<BabyViewModel>();
            SimpleIoc.Default.Register<EventsViewModel>();
            SimpleIoc.Default.Register<EventViewModel>();
            SimpleIoc.Default.Register<TimerViewModel>();
            SimpleIoc.Default.Register<ChartsViewModel>();
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance",
            "CA1822:MarkMembersAsStatic",
            Justification = "This non-static member is needed for data binding purposes.")]
        public MainViewModel Main
        {
            get
            {
                return ServiceLocator.Current.GetInstance<MainViewModel>();
            }
        }


        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance",
            "CA1822:MarkMembersAsStatic",
            Justification = "This non-static member is needed for data binding purposes.")]
        public BabyViewModel BabyModel
        {
            get
            {
                return ServiceLocator.Current.GetInstance<BabyViewModel>();
            }
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance",
            "CA1822:MarkMembersAsStatic",
            Justification = "This non-static member is needed for data binding purposes.")]
        public EventsViewModel EventsModel
        {
            get
            {
                return ServiceLocator.Current.GetInstance<EventsViewModel>();
            }
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance",
            "CA1822:MarkMembersAsStatic",
            Justification = "This non-static member is needed for data binding purposes.")]
        public EventViewModel EventModel
        {
            get
            {
                return ServiceLocator.Current.GetInstance<EventViewModel>();
            }
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance",
            "CA1822:MarkMembersAsStatic",
            Justification = "This non-static member is needed for data binding purposes.")]
        public TimerViewModel TimerModel
        {
            get
            {
                return ServiceLocator.Current.GetInstance<TimerViewModel>();
            }
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance",
            "CA1822:MarkMembersAsStatic",
            Justification = "This non-static member is needed for data binding purposes.")]
        public ChartsViewModel ChartsModel
        {
            get
            {
                return ServiceLocator.Current.GetInstance<ChartsViewModel>();
            }
        }

        /// <summary>
        /// Cleans up all the resources.
        /// </summary>
        public static void Cleanup()
        {
        }
    }
}