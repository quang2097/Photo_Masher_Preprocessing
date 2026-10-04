#include "../include/src/utils/Load_Photos.hpp"
#include "../include/src/utils/Resize_Photo.hpp"
#include "../include/src/Mash_Photos.hpp"
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

typedef enum{
    CONSTANT_PATH, VARIABLE_PATH
} Setting;

int Mash_Photos(vector<fs::path>& In_Photo_Paths, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const Setting SET_MODE){
    // Mash photos
    int Current_Index = 0;
    int Count_Mashed = 0;
    const int NUMBER_OF_PHOTOS_PER_PHOTO = PHOTOS_HORIZONTAL * PHOTOS_VERTICAL;
    const int RESOLUTIONS_HORIZONTAL_PER_PHOTO = round(RESOLUTIONS_HORIZONTAL/PHOTOS_HORIZONTAL);
    const int RESOLUTIONS_VERTICAL_PER_PHOTO = round(RESOLUTIONS_VERTICAL/PHOTOS_VERTICAL);
    vector<fs::path> Valid_Photo_Paths;

    cout << "Mashing photos." << endl;

    while(Current_Index < In_Photo_Paths.size() - NUMBER_OF_PHOTOS_PER_PHOTO){
        // Gather resized photos.
        vector<Mat> Photos;

        int Index = 0;
        while(Index < NUMBER_OF_PHOTOS_PER_PHOTO && Current_Index < In_Photo_Paths.size()){
            // Get actual photo from path.
            Mat Photo;

            Photo = Get_Photo(In_Photo_Paths[Current_Index].string());

            Current_Index += 1;

            // Resize photo.
            Photo = Resize_Photo(Photo, RESOLUTIONS_HORIZONTAL_PER_PHOTO, RESOLUTIONS_VERTICAL_PER_PHOTO);

            if(Photo.empty()){
                cout << "Failed resizing a photo, skipping photo." << endl;

                continue;
            }

            Index += 1;

            if(SET_MODE == VARIABLE_PATH){
                Valid_Photo_Paths.push_back(In_Photo_Paths[Current_Index - 1]); 
            }

            Photos.push_back(Photo);
        }

        // Mash photo.
        if(Photos.size() < NUMBER_OF_PHOTOS_PER_PHOTO){
            cout << "Not enough photos to mash, skipping the rest.";

            delete Index;

            break;
        }
        
        Mat Mashed_Photo(RESOLUTIONS_VERTICAL_PER_PHOTO * PHOTOS_VERTICAL, 
                         RESOLUTIONS_HORIZONTAL_PER_PHOTO * PHOTOS_HORIZONTAL, 
                         Photos[0].type());

        Index = 0;
        while(Index < NUMBER_OF_PHOTOS_PER_PHOTO){
            int x = Index % PHOTOS_HORIZONTAL;
            int y = Index / PHOTOS_HORIZONTAL;
            
            cv::Rect ROI(x * RESOLUTIONS_HORIZONTAL_PER_PHOTO, 
                         y * RESOLUTIONS_VERTICAL_PER_PHOTO, 
                         RESOLUTIONS_HORIZONTAL_PER_PHOTO, 
                         RESOLUTIONS_VERTICAL_PER_PHOTO);
                         
            Photos[Index].copyTo(Mashed_Photo(ROI));
            
            Index += 1;
        }
        
        fs::path Out_File = fs::path(OUT_PHOTOS_PATH)/("Mashed_" + std::to_string(Index) + In_Photo_Paths[Index].extension().string());
        cv::imwrite(Out_File.string(), Mashed_Photo);

        delete Index;
        Count_Mashed += 1;
    }

    if(SET_MODE == VARIABLE_PATH){
        In_Photo_Paths = Valid_Photo_Paths;
    }

    if(Count_Mashed == 0){
        cout << "No photos have been mashed, check the photo directory for valid files." << endl;
        return 1;
    }

    cout << "There are " << In_Photo_Paths.size() - (Count_Mashed * NUMBER_OF_PHOTOS_PER_PHOTO) << " un mashed photos." << endl;

    return 0;
}

int Mash_Photos(const vector<fs::path> IN_PHOTO_PATHS, vector<vector<fs::path>>& Valid_Photo_Paths, const string OUT_PHOTOS_PATH, 
                const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, 
                const int PHOTOS_VERTICAL, const Setting SET_MODE){
    // Mash photos
    int Current_Index = 0;
    int Count_Mashed = 0;
    const int NUMBER_OF_PHOTOS_PER_PHOTO = PHOTOS_HORIZONTAL * PHOTOS_VERTICAL;
    const int RESOLUTIONS_HORIZONTAL_PER_PHOTO = round(RESOLUTIONS_HORIZONTAL/PHOTOS_HORIZONTAL);
    const int RESOLUTIONS_VERTICAL_PER_PHOTO = round(RESOLUTIONS_VERTICAL/PHOTOS_VERTICAL);
    vector<vector<fs::path>> Valid_Photo_Paths_Local;

    cout << "Mashing photos." << endl;

    while(Current_Index < IN_PHOTO_PATHS.size() - NUMBER_OF_PHOTOS_PER_PHOTO){
        // Gather resized photos.
        vector<fs::path> Photo_Paths;
        vector<Mat> Photos;

        int Index = new int(0);
        while(Index < NUMBER_OF_PHOTOS_PER_PHOTO && Current_Index < IN_PHOTO_PATHS.size()){
            // Get actual photo from path.
            Mat Photo;

            Photo = Get_Photo(IN_PHOTO_PATHS[Current_Index].string());

            Current_Index += 1;

            // Resize photo.
            Photo = Resize_Photo(Photo, RESOLUTIONS_HORIZONTAL_PER_PHOTO, RESOLUTIONS_VERTICAL_PER_PHOTO);

            if(Photo.empty()){
                cout << "Failed resizing a photo, skipping photo." << endl;

                continue;
            }

            if(SET_MODE == VARIABLE_PATH){
                Photo_Paths.push_back(IN_PHOTO_PATHS[Index]);
            }

            Index += 1;

            if(SET_MODE == VARIABLE_PATH){
                Photo_Paths.push_back(IN_PHOTO_PATHS[Current_Index - 1]); 
            }

            Photos.push_back(Photo);
        }

        // Mash photo.
        if(Photos.size() < NUMBER_OF_PHOTOS_PER_PHOTO){
            cout << "Not enough photos to mash, skipping the rest.";
            delete Index;

            break;
        } else if(Photos.size() > NUMBER_OF_PHOTOS_PER_PHOTO){
            cout << "There is something wrong with the mashing program fetching too many photos.";
            delete Index;

            break;
        }
        
        Mat Mashed_Photo(RESOLUTIONS_VERTICAL_PER_PHOTO * PHOTOS_VERTICAL, 
                         RESOLUTIONS_HORIZONTAL_PER_PHOTO * PHOTOS_HORIZONTAL, 
                         Photos[0].type());

        Index = 0;
        while(Index < NUMBER_OF_PHOTOS_PER_PHOTO){
            int x = Index % PHOTOS_HORIZONTAL;
            int y = Index / PHOTOS_HORIZONTAL;
            
            cv::Rect ROI(x * RESOLUTIONS_HORIZONTAL_PER_PHOTO, 
                         y * RESOLUTIONS_VERTICAL_PER_PHOTO, 
                         RESOLUTIONS_HORIZONTAL_PER_PHOTO, 
                         RESOLUTIONS_VERTICAL_PER_PHOTO);
                         
            Photos[Index].copyTo(Mashed_Photo(ROI));
            
            Index += 1;
        }

        if(SET_MODE == VARIABLE_PATH){
            Valid_Photo_Paths_Local.push_back(Photo_Paths);
        }
        
        fs::path Out_File = fs::path(OUT_PHOTOS_PATH) / ("Mashed_" + IN_PHOTO_PATHS[Index].filename().string());
        cv::imwrite(Out_File.string(), Mashed_Photo);

        delete Index;
        Count_Mashed += 1;
    }

    if(Count_Mashed == 0){
        cout << "No photos have been mashed, check the photo directory for valid files." << endl;
        return 1;
    }

    if(SET_MODE == VARIABLE_PATH){
        Valid_Photo_Paths = Valid_Photo_Paths_Local;
    }

    cout << "There are " << IN_PHOTO_PATHS.size() - (Count_Mashed * NUMBER_OF_PHOTOS_PER_PHOTO) << " un mashed photos." << endl;

    return 0;
}