using GalaSoft.MvvmLight;

namespace BabyFeed.ViewModel
{
    public class NotesStepViewModel : ViewModelBase, IValidableContent
    {
        public NotesStepViewModel()
        {
        }

        public bool IsValid()
        {
            return true;
        }
    }
}