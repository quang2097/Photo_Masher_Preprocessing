#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include "../src/utils/Read_Txt_File.hpp"

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::cout;
using std::endl;

vector<vector<string>> Current_Label_Group;

int Get_Label_Group(const vector<fs::path> VALID_LABEL_GROUP_PATHS){
    vector<vector<string>> Current_Label_Group;

    for(int Index = 0;Index < VALID_LABEL_GROUP_PATHS.size();Index += 1){
        if(VALID_LABEL_GROUP_PATHS[Index].empty()){
            Current_Label_Group.push_back({});
            continue;
        }

        vector<string> Label = Read_Txt_File(VALID_LABEL_GROUP_PATHS[Index].string());

        if(Label.empty()){
            cout << "Empty label file at " << VALID_LABEL_GROUP_PATHS[Index].string(); << " continuing." << endl
        }

        Current_Label_Group.push_back(Label);
    }

    if(Current_Label_Group.empty()){
        cout << "No labels available for "
    }
}

int Create_Labels(const vector<vector<fs::path>> VALID_LABEL_PATHS, const string OUT_LABELS_PATH,const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
    
}