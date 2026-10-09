// Include libraries.
#include "../include/libs/core.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

// Include big premade functions.
#include "../include/src/Create_Labels.hpp"
#include "../include/src/Mash_Photos.hpp"

// Include utilities.
#include "../include/src/utils/Get_Exe_Path.hpp"
#include "../include/src/utils/Load_Photos.hpp"
#include "../include/src/utils/Read_Txt_File.hpp"
#include "../include/src/utils/Resize_Photo.hpp"

namespace fs = std::filesystem;
using cv::Mat;
using std::cout;
using std::endl;
using std::string;
using std::vector;
    
namespace aliases{
    vector<string> Read_Txt_File_Alias(const string FILE_PATH){
        return Read_Txt_File(FILE_PATH);
    }

    vector<string> Read_Txt_File_Alias(const string FILE_PATH, const Read_Txt_File_Mode TYPE){
        return Read_Txt_File(FILE_PATH, TYPE);
    }

    Mat Resize_Photo_Alias(Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL){
        return Resize_Photo(Input_Photo, RESOLUTIONS_HORIZONTAL, RESOLUTIONS_VERTICAL);
    }

    int Mash_Photos_Alias(vector<fs::path>& In_Photo_Paths, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                        const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const Setting SET_MODE){
        return Mash_Photos(In_Photo_Paths, OUT_PHOTOS_PATH, RESOLUTIONS_HORIZONTAL, 
                    RESOLUTIONS_VERTICAL, PHOTOS_HORIZONTAL, PHOTOS_VERTICAL, SET_MODE);
    }

    int Create_Labels_Alias(const vector<vector<fs::path>>& VALID_LABEL_PATHS, const string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                            const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
        return Create_Labels(VALID_LABEL_PATHS, OUT_LABELS_PATH, RESOLUTIONS_HORIZONTAL, 
                            RESOLUTIONS_VERTICAL, PHOTOS_HORIZONTAL, PHOTOS_VERTICAL);
    }
};

namespace photo_masher{
    namespace utils{
        string Get_Exe_Path(){
            cout << "Getting executable path." << endl;
            
            string Exe_Path = Get_Executable_Path();

            if(Exe_Path.empty()){
                cout << "Failed getting executable path." << endl;
                return "";
            }

            cout << "Got executable path." << endl;

            return Exe_Path;
        }

        Mat Load_Photos(const string PATH){
            cout << "Loading photo from " << PATH << "." << endl;

            Mat Photo = Get_Photo(PATH);

            if(!Photo.empty()){
                cout << "Loaded photo from " << PATH << "." << endl;
            }

            return Photo;
        }

        vector<string> Read_Txt_File(const string PATH){
            cout << "Getting contents from " << PATH << "." << endl;

            const vector<string> TXT_CONTENTS = aliases::Read_Txt_File_Alias(PATH);
            
            if(TXT_CONTENTS.empty()){
                cout << "Failed to get contents from " << PATH << "." << endl;
                return {};
            }

            cout << "Getting contents from " << PATH << " successful." << endl; 

            return TXT_CONTENTS;
        }

        vector<string> Read_Txt_File(const string PATH, const Read_Txt_File_Mode TYPE){
            cout << "Getting contents from " << PATH << "." << endl;

            const vector<string> TXT_CONTENTS = aliases::Read_Txt_File_Alias(PATH, TYPE);
            
            if(TXT_CONTENTS.empty()){
                cout << "Failed to get contents from " << PATH << "." << endl;
                return {};
            }

            cout << "Getting contents from " << PATH << " successful." << endl; 

            return TXT_CONTENTS;
        }

        Mat Resize_Photo(Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL){
            cout << "Resizing photo." << endl;

            const Mat PHOTO = aliases::Resize_Photo_Alias(Input_Photo, RESOLUTIONS_HORIZONTAL, RESOLUTIONS_VERTICAL);

            if(PHOTO.empty()){
                cout << "Failed resizing photo." << endl;
                return Mat{};
            }

            cout << "Resize photo successful." << endl;

            return PHOTO;
        }
    };

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

        void Create_Labels(const vector<vector<fs::path>>& VALID_LABEL_PATHS, const string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                            const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
            cout << "Creating labels." << endl;

            int CHECK = aliases::Create_Labels_Alias(VALID_LABEL_PATHS, OUT_LABELS_PATH, RESOLUTIONS_HORIZONTAL, 
                                                    RESOLUTIONS_VERTICAL, PHOTOS_HORIZONTAL, PHOTOS_VERTICAL);

            if(CHECK == 1){
                cout << "Failed to create labels." << endl;
                return;
            }

            cout << "Labels created successfully." << endl;
        }
    };
};