#include "../../include/src/utils/Load_Photos.hpp"
#include "../../include/src/utils/Resize_Photo.hpp"
#include "../../include/libs/core.hpp"
#include <filesystem>
#include <string>
#include <iterator>
#include <execution>
#include <vector>
#include <iostream>
#include <algorithm>

#include "../../include/src/utils/Mash_Photos.hpp"

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using cv::Mat;
using std::floor;
using std::round;
using std::ceil;

namespace utils{
    cv::Mat Mash_Photos(std::vector<cv::Mat> Inputs, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL, 
                        const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
        if(PHOTOS_HORIZONTAL <= 0){
            cout << "Cannot apply mash photo preprocessing with number of horizontal photos equals " << PHOTOS_HORIZONTAL << endl;
            return;
        }

        else if(PHOTOS_VERTICAL <= 0){
            cout << "Cannot apply mash photo preprocessing with number of vertical photos equals " << PHOTOS_VERTICAL << endl;
            return;
        }

        else if(RESOLUTIONS_HORIZONTAL <= 0){
            cout << "Cannot apply mash photo preprocessing with horizontal resolution equals " << RESOLUTIONS_HORIZONTAL << endl;
            return;
        }

        else if(RESOLUTIONS_VERTICAL <= 0){
            cout << "Cannot apply mash photo preprocessing with vertical resolution queals " << RESOLUTIONS_VERTICAL << endl;
            return;
        }

        else if(RESOLUTIONS_HORIZONTAL < PHOTOS_HORIZONTAL){
            cout << "Cannot apply mash photo preprocessing with horizontal resolution less than the number of photos available horizontally" << endl;
            return;
        }

        else if(RESOLUTIONS_VERTICAL < PHOTOS_VERTICAL){
            cout << "Cannot apply mash photo preprocessing with vertical resolution less than the number of photos available vertically" << endl;
            return;
        }

        const int NUMBER_OF_PHOTOS_PER_PHOTO = PHOTOS_HORIZONTAL * PHOTOS_VERTICAL;
        const int RESOLUTIONS_HORIZONTAL_PER_PHOTO = round(RESOLUTIONS_HORIZONTAL/PHOTOS_HORIZONTAL);
        const int RESOLUTIONS_VERTICAL_PER_PHOTO = round(RESOLUTIONS_VERTICAL/PHOTOS_VERTICAL);

        if(Inputs.size() < NUMBER_OF_PHOTOS_PER_PHOTO){
            cout << "Not enough photos to mash." << endl;
            return Mat{};
        }

        else if(Inputs.size() > NUMBER_OF_PHOTOS_PER_PHOTO){
            cout << "Too many photos to mash skipping " << Inputs.size() - NUMBER_OF_PHOTOS_PER_PHOTO << " photos if not needed." << endl;
        }
            
        Mat Mashed_Photo(RESOLUTIONS_VERTICAL_PER_PHOTO * PHOTOS_VERTICAL, 
                        RESOLUTIONS_HORIZONTAL_PER_PHOTO * PHOTOS_HORIZONTAL, 
                        Inputs[0].type());

        int Count_Failed_Mash = 0;
        for(int Index = 0;Index < NUMBER_OF_PHOTOS_PER_PHOTO;Index += 1){
            Inputs.at(Index) = utils::Resize_Photo(Inputs.at(Index), RESOLUTIONS_HORIZONTAL_PER_PHOTO, RESOLUTIONS_VERTICAL_PER_PHOTO);

            if(Inputs.at(Index).empty()){
                Count_Failed_Mash += 1;

                if(Inputs.size() < NUMBER_OF_PHOTOS_PER_PHOTO + Count_Failed_Mash){
                    cout << "Failed resizing a photo, skipping photo." << endl;
                    continue;
                }

                cout << "Failed resizing a photo. Not enough photos to mash. Exit Mashing photo." << endl;
                return;
            }
        }

        for(int Index = 0;Index < NUMBER_OF_PHOTOS_PER_PHOTO;Index += 1){
            int x = Index % PHOTOS_HORIZONTAL;
            int y = Index / PHOTOS_HORIZONTAL;
            
            cv::Rect Roi(x * RESOLUTIONS_HORIZONTAL_PER_PHOTO, 
                        y * RESOLUTIONS_VERTICAL_PER_PHOTO, 
                        RESOLUTIONS_HORIZONTAL_PER_PHOTO, 
                        RESOLUTIONS_VERTICAL_PER_PHOTO);
                        
            Inputs[Index].copyTo(Mashed_Photo(Roi));
            
            Index += 1;
        }

        if(Mashed_Photo.empty()){
            cout << "Failed to mash photos." << endl;
            return Mat{};
        }

        return Mashed_Photo;
    }
};