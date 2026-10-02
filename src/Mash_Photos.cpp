#include "../include/src/utils/Load_Photos.hpp"
#include "../include/libs/core.hpp"
#include <filesystem>
#include <string>
#include <iterator>
#include <execution>
#include <vector>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using cv::Mat;
using std::floor;
using std::round;
using std::ceil;

int Mash_Photos(const vector<fs::path> IN_PHOTO_PATHS, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
    // Mash photos
    int Current_Index = 0;
    int Count_Mashed = 0;
    const int NUMBER_OF_PHOTOS_PER_PHOTO = PHOTOS_HORIZONTAL * PHOTOS_VERTICAL;
    const int RESOLUTIONS_HORIZONTAL_PER_PHOTO = (RESOLUTIONS_HORIZONTAL)

    while(Current_Index < IN_PHOTO_PATHS.size() - NUMBER_OF_PHOTOS_PER_PHOTO){
        vector<Mat> Photos;

        for(int Index = 0;Index < NUMBER_OF_PHOTOS_PER_PHOTO;Index += 1){
            Mat Photo;

            Photo = Get_Photo(IN_PHOTO_PATHS[Index].string());

            Photos.push_back(Photo);
        }

        for(int Index_Horizontal = 0;Index_Horizontal < PHOTOS_HORIZONTAL;Index_Horizontal += 1){
            for(int Index_Vertical = 0;Index_Vertical < PHOTOS_VERTICAL;Index_Vertical += 1){
                
            }
        }
        
        Current_Index += NUMBER_OF_PHOTOS_PER_PHOTO;

        Count_Mashed += 1;
    }

    if(Count_Mashed == 0){
        cout << "No photos have been mashed, check the photo directory for valid files." << endl;
        return 1;
    }

    cout << "There are " << IN_PHOTO_PATHS.size() - (Count_Mashed * NUMBER_OF_PHOTOS_PER_PHOTO) << " un mashed photos." << endl;

    return 0;
}