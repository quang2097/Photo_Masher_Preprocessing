#include "../include/src/utils/Load_Photos.hpp"
#include "../include/libs/core.hpp"
#include <filesystem>
#include <string>
#include <iterator>
#include <execution>
#include <vector>
#include <iostream>

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using cv::Mat;

int Mash_Photos(const vector<fs::path> IN_PHOTO_PATHS, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
    // Mash photos
    int Current_Index = 0;
    const int NUMBER_OF_PHOTOS_PER_PHOTO = PHOTOS_HORIZONTAL * PHOTOS_VERTICAL;

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
    }
    

    return 0;
}