using GalaSoft.MvvmLight;
using BabyFeed.Provider;
using GalaSoft.MvvmLight.Messaging;
using GalaSoft.MvvmLight.Command;
using Microsoft.Phone.Tasks;
using System;
using System.Windows.Media.Imaging;
using BabyFeed.Domain;
using System.IO.IsolatedStorage;
using System.Windows.Threading;
using System.Windows;
using System.ComponentModel;
using BabyFeed.Events;

namespace BabyFeed.ViewModel
{
    public class BabyViewModel : ViewModelBase
    {
        private readonly IDataService _dataService;
        private readonly INavigationService _navigationService;
        private Baby _baby;

        public RelayCommand CapturePhotoCommand { get; set; }

        public BabyViewModel(IDataService dataService, INavigationService navigationService)
        {
            _dataService = dataService;
            _navigationService = navigationService;

            BirthDay = DateTime.Now;
            MinutesBetweenFeeds = "";

            CapturePhotoCommand = new RelayCommand(HandleCapturePhoto);
        }

        private string _title = "";

        public string Title
        {
            get
            {
                return _title;
            }

            set
            {
                _title = value;
                RaisePropertyChanged("Title");
            }
        }

        private string _photo = "";

        public string Photo
        {
            get
            {
                return _photo;
            }

            set
            {
                _photo = value;
                RaisePropertyChanged("Photo");
            }
        }

        private string _name = "";

        public string Name
        {
            get
            {
                return _name;
            }

            set
            {
                _name = value;
                RaisePropertyChanged("Name");
                RaisePropertyChanged("IsNameInvalid");
                RaisePropertyChanged("IsFormValid");
            }
        }

        public bool IsNameInvalid
        {
            get
            {
                return Name.Trim().Length == 0;
            }
        }

        public bool EnableTimerAlarms { get; set; }

        public string MinutesBetweenFeeds { get; set; }

        public DateTime BirthDay { get; set; }

        private int _genderIndex = 0;

        public int GenderIndex 
        {
            get
            {
                return _genderIndex;
            }

            set
            {
                _genderIndex = value;
                if (!Photo.StartsWith("isostore"))
                {
                    if (_genderIndex == 0)
                        Photo = "/icons/baby_boy_icon.png";
                    else
                        Photo = "/icons/baby_girl_icon.png";
                }
            }

        }

        public string[] Genders
        {
            get
            {
                return new string[] { AppResx.boy, AppResx.girl };
            }
        }

        public bool IsFormValid
        {
            get
            {
                return (Name.Trim().Length > 0);
            }
        }

        public void HandleSave()
        {
            _baby.Name = Name;
            _baby.BirthDate = BirthDay.Date;
            _baby.FeedAlarmActive = EnableTimerAlarms;
            if (MinutesBetweenFeeds.Trim() == "")
                _baby.TimeBetweenFeeds = 0;
            else
                _baby.TimeBetweenFeeds = int.Parse(MinutesBetweenFeeds);
            _baby.Photo = Photo;

            _navigationService.GoBack();

            Messenger.Default.Send<BabySavedEvent>(new BabySavedEvent(_baby.Persist(_dataService)));
        }


        public void HandleNewBabyEvent()
        {
            _baby = new Baby();

            Title = AppResx.newbaby;
            Photo = "/icons/baby_boy_icon.png";
            Name = "";
            Photo = "/icons/baby_boy_icon.png";
            BirthDay = DateTime.Now;
            GenderIndex = 0;
            MinutesBetweenFeeds = "60";
            EnableTimerAlarms = true;
        }

        public void HandleEditBabyEvent(int babyId)
        {
            _baby = _dataService.GetBabyById(babyId);

            Title = _baby.Name + "'s file";
            Photo = _baby.Photo;
            Name = _baby.Name;
            BirthDay = _baby.BirthDate;
            GenderIndex = (int)_baby.Gender;
            MinutesBetweenFeeds = _baby.TimeBetweenFeeds.ToString();
            EnableTimerAlarms = _baby.FeedAlarmActive;
        }

        private void HandleCapturePhoto()
        {
            CameraCaptureTask photoCameraCapture;

            photoCameraCapture = new CameraCaptureTask();
            photoCameraCapture.Completed += new EventHandler<PhotoResult>(HandlePhotoResult);
            photoCameraCapture.Show();
        }

        private void HandlePhotoResult(object sender, PhotoResult e)
        {
            if (e.TaskResult == TaskResult.OK)
            {
                String tempJPEG = ""+_baby.Id+ ".jpeg";
                IsolatedStorageFile store = IsolatedStorageFile.GetUserStoreForApplication();

                if (store.FileExists(tempJPEG))
                {
                    store.DeleteFile(tempJPEG);
                }

                IsolatedStorageFileStream fileStream = store.CreateFile(tempJPEG);
                BitmapImage bitmap = new BitmapImage();

                bitmap.SetSource(e.ChosenPhoto);
                WriteableBitmap wb = new WriteableBitmap(bitmap);

                Extensions.SaveJpeg(wb, fileStream, wb.PixelWidth, wb.PixelHeight, 0, 85);
                fileStream.Close();

                Deployment.Current.Dispatcher.BeginInvoke(delegate()
                {
                    Photo = "isostore:/" + tempJPEG;
                });
            }
        }

    }
}