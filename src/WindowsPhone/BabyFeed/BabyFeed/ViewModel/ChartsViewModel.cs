﻿using GalaSoft.MvvmLight;
using BabyFeed.Provider;
using BabyFeed.Domain;

namespace BabyFeed.ViewModel
{
    public class ChartsViewModel : ViewModelBase
    {
        private readonly IDataService _dataService;
        private readonly INavigationService _navigationService;
        private Baby _baby;

        // Measures in cm
        private double[] _maleHeight3per = { 44.9251, 47.97812, 52.19859, 55.26322, 57.73049, 59.82569, 61.66384, 63.31224, 64.81395, 66.19833, 67.48635, 68.6936, 69.832, 70.91088, 71.9377, 72.91853, 73.85839, 74.76147, 75.63132, 76.47096, 77.283, 78.06971, 78.83308, 79.57485, 80.29656, 80.99959, 81.74464, 82.47365, 83.18812, 83.88931, 84.57826, 85.25589, 85.92294, 86.58009, 87.22791, 87.86696, 88.49774 };
        private double[] _maleHeight50per = { 49.98888, 52.69598, 56.62843, 59.60895, 62.077, 64.21686, 66.12531, 67.86018, 69.45908, 70.94804, 72.34586, 73.66665, 74.9213, 76.11838, 77.2648, 78.36622, 79.42734, 80.45209, 81.44384, 82.40544, 83.33938, 84.24783, 85.1327, 85.99565, 86.83818, 87.66161, 88.45247, 89.22326, 89.97549, 90.71041, 91.42908, 92.13242, 92.82127, 93.49638, 94.15847, 94.80823, 95.44637 };
        private double[] _maleHeight97per = { 54.919, 57.62984, 61.62591, 64.69241, 67.2519, 69.48354, 71.48218, 73.30488, 74.98899, 76.56047, 78.03819, 79.43637, 80.76602, 82.03585, 83.25292, 84.42302, 85.55095, 86.64078, 87.69597, 88.7195, 89.71393, 90.68153, 91.62428, 92.54392, 93.44203, 94.31998, 95.24419, 96.13962, 97.00763, 97.84957, 98.66677, 99.46052, 100.2321, 100.9829, 101.7142, 102.4274, 103.1237 };

        private double[] _femaleHeight3per = { 45.0949, 47.4692, 50.9570, 53.6293, 55.8594, 57.8047, 59.5480, 61.1389, 62.6099, 63.9835, 65.2759, 66.4995, 67.6637, 68.7761, 69.8428, 70.8687, 71.8581, 72.8143, 73.7405, 74.6391, 75.5124, 76.3623, 77.1906, 77.9987, 78.7880, 79.5597, 80.3400, 81.1133, 81.8733, 82.6151, 83.3347, 84.0297, 84.6984, 85.3399, 85.9541, 86.5417, 87.1035 };
        private double[] _femaleHeight50per = { 49.2864, 51.6836, 55.2861, 58.0938, 60.4598, 62.5367, 64.4063, 66.1184, 67.7057, 69.1912, 70.5916, 71.9196, 73.1850, 74.3956, 75.5579, 76.6769, 77.7570, 78.8020, 79.8149, 80.7985, 81.7551, 82.6868, 83.5953, 84.4823, 85.3492, 86.1973, 87.0903, 87.9571, 88.7960, 89.6055, 90.3848, 91.1334, 91.8515, 92.5396, 93.1985, 93.8295, 94.43380 };
        private double[] _femaleHeight97per = { 54.4953, 56.6273, 60.0034, 62.7455, 65.1158, 67.2340, 69.1667, 70.9555, 72.6284, 74.2053, 75.7012, 77.1273, 78.4926, 79.8042, 81.0680, 82.2889, 83.4710, 84.6177, 85.7321, 86.8166, 87.8737, 88.9053, 89.9131, 90.8987, 91.8635, 92.8088, 93.8186, 94.7943, 95.7346, 96.6393, 97.5081, 98.3414, 99.1399, 99.9047, 100.6372, 101.3388, 102.0116 };

        private double[] _maleHead3per = { 31.4876, 33.2501, 35.7813, 37.5588, 38.8994, 39.9567, 40.8164, 41.5311, 42.1352, 42.6525, 43.1001, 43.4905, 43.8333, 44.1360, 44.4044, 44.6433, 44.8565, 45.0471, 45.2179, 45.3710, 45.5084, 45.6317, 45.7422, 45.8412, 45.9297, 46.0087, 46.0790, 46.1412, 46.1961, 46.2443, 46.2861, 46.3221, 46.3528, 46.3784, 46.3994, 46.4161, 46.4286, 46.4334 };
        private double[] _maleHead50per = { 35.8137, 37.1936, 39.2074, 40.6523, 41.7652, 42.6612, 43.4049, 44.0361, 44.5810, 45.0576, 45.4791, 45.8551, 46.1930, 46.4985, 46.7764, 47.0302, 47.2630, 47.4772, 47.6750, 47.8582, 48.0282, 48.1864, 48.3338, 48.4714, 48.6001, 48.7207, 48.8337, 48.9398, 49.0395, 49.1332, 49.2215, 49.3046, 49.3829, 49.4568, 49.5265, 49.5922, 49.6542, 49.6839 };
        private double[] _maleHead97per = { 38.8542, 40.1003, 41.9414, 43.2818, 44.3273, 45.1788, 45.8930, 46.5052, 47.0388, 47.5099, 47.9303, 48.3087, 48.6518, 48.9649, 49.2523, 49.5171, 49.7623, 49.9902, 50.2026, 50.4013, 50.5875, 50.7626, 50.9275, 51.0832, 51.2305, 51.3700, 51.5024, 51.6282, 51.7479, 51.8620, 51.9708, 52.0748, 52.1741, 52.2692, 52.3603, 52.4476, 52.5314, 52.5721 };

        private double[] _femaleHead3per = { 31.9302, 33.3807, 35.4863, 36.9855, 38.1311, 39.0462, 39.7996, 40.4338, 40.9767, 41.4477, 41.8606, 42.2258, 42.5511, 42.8426, 43.1053, 43.3429, 43.5588, 43.7556, 43.9354, 44.1001, 44.2514, 44.3905, 44.5186, 44.6368, 44.7459, 44.8468, 44.9401, 45.0263, 45.1062, 45.1801, 45.2485, 45.3118, 45.3704, 45.4244, 45.4744, 45.5205, 45.5629, 45.5828 };
        private double[] _femaleHead50per = { 34.7116, 36.0345, 37.9767, 39.3801, 40.4677, 41.3484, 42.0834, 42.7103, 43.2543, 43.7325, 44.1574, 44.5384, 44.8824, 45.1951, 45.4808, 45.7431, 45.9849, 46.2086, 46.4162, 46.6095, 46.7899, 46.9586, 47.1168, 47.2654, 47.4052, 47.5369, 47.6612, 47.7787, 47.8898, 47.9951, 48.0949, 48.1896, 48.2796, 48.3652, 48.4465, 48.5240, 48.5978, 48.6334 };
        private double[] _femaleHead97per = { 38.1211, 39.2701, 40.9748, 42.2232, 43.2026, 44.0049, 44.6818, 45.2656, 45.7775, 46.2322, 46.6405, 47.0104, 47.3478, 47.6577, 47.9437, 48.2091, 48.4563, 48.6874, 48.9042, 49.1081, 49.3005, 49.4824, 49.6548, 49.8185, 49.9743, 50.1227, 50.2644, 50.3998, 50.5294, 50.6536, 50.7728, 50.8873, 50.9974, 51.1034, 51.2055, 51.3039, 51.3989, 51.4452 };

        // Measures in kg
        private double[] _maleWeight3per = { 2.3555, 2.7995, 3.6147, 4.3423, 4.9929, 5.5752, 6.0968, 6.5644, 6.9841, 7.3612, 7.7006, 8.0067, 8.2834, 8.5343, 8.7626, 8.9714, 9.1632, 9.3403, 9.5050, 9.6590, 9.8040, 9.9416, 10.0731, 10.1996, 10.3221, 10.4414, 10.5585, 10.6738, 10.7880, 10.9015, 11.0147, 11.1279, 11.2414, 11.3553, 11.4699, 11.5852, 11.7014, 11.7598 };
        private double[] _maleWeight50per = { 3.5302, 4.0031, 4.8795, 5.6729, 6.3914, 7.0418, 7.6304, 8.1630, 8.6448, 9.0811, 9.4765, 9.8353, 10.1615, 10.4589, 10.7306, 10.9799, 11.2096, 11.4221, 11.6198, 11.8048, 11.9790, 12.1440, 12.3015, 12.4528, 12.5991, 12.7415, 12.8810, 13.0184, 13.1545, 13.2899, 13.4252, 13.5609, 13.6974, 13.8351, 13.9742, 14.1150, 14.2578, 14.3299 };
        private double[] _maleWeight97per = { 4.4465, 5.0326, 6.1219, 7.1063, 7.9939, 8.7934, 9.5133, 10.1614, 10.7449, 11.2708, 11.7454, 12.1744, 12.5631, 12.9165, 13.2389, 13.5346, 13.8072, 14.0602, 14.2966, 14.5191, 14.7303, 14.9326, 15.1278, 15.3178, 15.5042, 15.6884, 15.8717, 16.0551, 16.2397, 16.4261, 16.6151, 16.8072, 17.0029, 17.2026, 17.4065, 17.6150, 17.8280, 17.9363 };

        private double[] _femaleWeight3per = { 2.4141, 2.7569, 3.4023, 3.9978, 4.5474, 5.0545, 5.5225, 5.9543, 6.3527, 6.7203, 7.0597, 7.3732, 7.6630, 7.9310, 8.1794, 8.4097, 8.6239, 8.8234, 9.0097, 9.1842, 9.3481, 9.5028, 9.6492, 9.7884, 9.9213, 10.0488, 10.1717, 10.2908, 10.4066, 10.5199, 10.6311, 10.7408, 10.8494, 10.9572, 11.0648, 11.1723, 11.2800, 11.3340 };
        private double[] _femaleWeight50per = { 3.3992, 3.7975, 4.5448, 5.2306, 5.8600, 6.4376, 6.9679, 7.4549, 7.9024, 8.3142, 8.6934, 9.0433, 9.3666, 9.6661, 9.9442, 10.2033, 10.4454, 10.6725, 10.8864, 11.0887, 11.2809, 11.4644, 11.6404, 11.8101, 11.9745, 12.1346, 12.2910, 12.4447, 12.5962, 12.7462, 12.8952, 13.0436, 13.1918, 13.3402, 13.4891, 13.6388, 13.7894, 13.8651 };
        private double[] _femaleWeight97per = { 4.2549, 4.7436, 5.6574, 6.4926, 7.2562, 7.9547, 8.5944, 9.1809, 9.7196, 10.2154, 10.6728, 11.0961, 11.4891, 11.8554, 12.1983, 12.5208, 12.8256, 13.1153, 13.3920, 13.6580, 13.9150, 14.1647, 14.4086, 14.6481, 14.8843, 15.1184, 15.3512, 15.5836, 15.8163, 16.0499, 16.2849, 16.5218, 16.7609, 17.0025, 17.2468, 17.4941, 17.7445, 17.8709 };


        public double[] HeightSeries3Per 
        {
            get
            {
                return (_baby.Gender==Baby.Genders.Boy?_maleHeight3per:_femaleHeight3per);
            }
        }

        public double[] HeightSeries50Per
        {
            get 
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleHeight50per : _femaleHeight50per);
            }
        }

        public double[] HeightSeries97per
        { 
            get
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleHeight97per : _femaleHeight97per);
            }
        }


        public double[] WeightSeries3Per
        {
            get
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleWeight3per : _femaleWeight3per);
            }
        }

        public double[] WeightSeries50Per
        {
            get
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleWeight50per : _femaleWeight50per);
            }
        }

        public double[] WeightSeries97per
        {
            get
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleWeight97per : _femaleWeight97per);
            }
        }



        public double[] HeadSeries3Per
        {
            get
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleHead3per : _femaleHead3per);
            }
        }

        public double[] HeadSeries50Per
        {
            get
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleHead50per : _femaleHead50per);
            }
        }

        public double[] HeadSeries97per
        {
            get
            {
                return (_baby.Gender == Baby.Genders.Boy ? _maleHead97per : _femaleHead97per);
            }
        }


        public ChartsViewModel(IDataService dataService, INavigationService navigationService)
        {
            _dataService = dataService;
            _navigationService = navigationService;

            if (IsInDesignMode)
            {
                _baby = new Baby();
                _baby.Gender = Baby.Genders.Girl;
                _baby.Name = "Maria";
            }
        }

        public void HandleShowBabyChartsEvent(int babyId)
        {
            _baby = _dataService.GetBabyById(babyId);
        }
    }
}