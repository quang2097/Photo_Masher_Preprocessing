// Include libraries.
#include "../include/libs/core.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

// Include utilities.
#include "../include/src/utils/Get_Exe_Path.hpp"
#include "../include/src/utils/Load_Photos.hpp"
#include "../include/src/utils/Read_Txt_File.hpp"
#include "../include/src/utils/Resize_Photo.hpp"

using std::cout;
using std::endl;
using std::string;

namespace utils{
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

        string Get_Executable_Path_Alias(){
            return Get_Executable_Path();
        }
    };

    namespace features{
        string Get_Executable_Path(){
            cout << "Getting executable path." << endl;
            
            const string EXE_PATH = aliases::Get_Executable_Path_Alias();

            if(EXE_PATH.empty()){
                cout << "Failed getting executable path." << endl;
                return "";
            }

            cout << "Got executable path." << endl;

            return EXE_PATH;
        }

        Mat Load_Photos(const string PATH){
            cout << "Loading photo from " << PATH << "." << endl;

            const Mat PHOTO = Get_Photo(PATH);

            if(!PHOTO.empty()){
                cout << "Loaded photo from " << PATH << "." << endl;
                return Mat{};
            }

            return PHOTO;
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
};