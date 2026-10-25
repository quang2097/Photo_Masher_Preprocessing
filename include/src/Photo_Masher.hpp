// Include libraries.
#include "../libs/core.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

// Include big premade functions.
#include "./Create_Labels.hpp"
#include "./Mash_Photos.hpp"

// Include utilities.
#include "./utils/Get_Exe_Path.hpp"
#include "./utils/Load_Photos.hpp"
#include "./utils/Read_Txt_File.hpp"
#include "./utils/Resize_Photo.hpp"

namespace fs = std::filesystem;
using cv::Mat;
using std::string;
using std::vector;

namespace photo_masher{
    namespace features{
        void Mash_Photos(vector<fs::path>& In_Photo_Paths, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                        const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const Setting SET_MODE);
                        
        void Create_Labels_Photo_Masher(const vector<vector<fs::path>>& VALID_LABEL_PATHS, const string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                            const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL);
    };
};