// Include libraries.
#include "../include/libs/core.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

// Include big premade functions.
#include "../include/src/utils/Create_Labels.hpp"
#include "../include/src/features/Mash_Photos.hpp"

namespace fs = std::filesystem;
using cv::Mat;
using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace features{
    void Mash_Photos(vector<fs::path>& In_Photo_Paths, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                    const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const Setting SET_MODE){
        cout << "Starting photo masher." << endl;

        const int CHECK = aliases::Mash_Photos_Alias(In_Photo_Paths, OUT_PHOTOS_PATH, RESOLUTIONS_HORIZONTAL, 
                                    RESOLUTIONS_VERTICAL, PHOTOS_HORIZONTAL, PHOTOS_VERTICAL, SET_MODE);

        if(CHECK == 1){
            cout << "failed to mash photos." << endl;
            return; 
        }

        cout << "Mashing photos successful." << endl;
    }

    void Create_Labels_Photo_Masher(const vector<vector<fs::path>>& VALID_LABEL_PATHS, const string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                        const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const Dataset_Format FORMAT){
        cout << "Creating labels." << endl;

        int CHECK = utils::Create_Labels_Photo_Masher(VALID_LABEL_PATHS, OUT_LABELS_PATH, RESOLUTIONS_HORIZONTAL, 
                                                RESOLUTIONS_VERTICAL, PHOTOS_HORIZONTAL, PHOTOS_VERTICAL, FORMAT);

        if(CHECK == 1){
            cout << "Failed to create labels." << endl;
            return;
        }

        cout << "Labels created successfully." << endl;
    }
};