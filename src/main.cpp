#include <iostream>
#include <string>
#include <vector>
#include "../include/src/utils/Read_Txt_File.hpp"
#include "../include/src/utils/Get_Exe_Path.hpp"
#include "../include/src/Mash_Photos.hpp"
#include <filesystem>
#include <unordered_set>

namespace fs = std::filesystem;
using std::vector;
using std::cout;
using std::cin;
using std::string; 
using std::stoi;
using std::endl;
using std::unordered_set;

string Exe_File_Path;
string Path_Txt_Location;
string Settings_Txt_Location;
string Exe_Directory_Path;

string In_Labels_Path;
string In_Photos_Path;
string Out_Labels_Path;
string Out_Photos_Path;

vector<fs::path> In_Photo_Paths;
vector<fs::path> In_Label_Paths;

vector<vector<fs::path>> Valid_Photo_Paths;
vector<vector<fs::path>> Valid_Label_Paths;

// const float DUMMY = 0.7071067;

int Resolution_Horizontal = -1;
int Resolution_Vertical = -1;
int Number_Of_Photos_Horizontal = -1;
int Number_Of_Photos_Vertical = -1;

int Get_Exe_File_Path(){
    cout<< endl << "Getting exe file path." << endl;

    Exe_File_Path = Get_Executable_Path();

    Exe_Directory_Path = Get_Executable_Directory();

    if(Exe_File_Path.empty()){
        cout << "Cannot get exe path." << endl;
        cout << "Exit with error." << endl;

        return 1;
    }

    cout << "Exe file path found: " + Exe_File_Path << endl;

    return 0;
}

int Get_Paths(const string& TXT_PATH){
    cout << "Getting paths from txt" << endl;

    vector<string> In_Out_Paths = Read_Txt_File(TXT_PATH, ADDRESS_TXT);;

    if(In_Out_Paths.empty() || In_Out_Paths.size() < 4){
        cout << "Cannot get paths from txt file." << endl;

        return 1;
    }

    In_Labels_Path = In_Out_Paths[0];
    In_Photos_Path = In_Out_Paths[1];
    Out_Labels_Path = In_Out_Paths[2];
    Out_Photos_Path = In_Out_Paths[3];

    cout << "Get paths from txt successful." << endl;

    return 0;
}

int Get_Settings(const string& TXT_PATH){
    cout << "Getting settings from txt" << endl;

    vector<string> Settings = Read_Txt_File(TXT_PATH, SETTING_TXT);
    vector<int> Settings_Integer;

    if(Settings.empty() || Settings.size() < 4){
        cout << "Cannot get settings from txt file." << endl;

        return 1;
    }

    for(int Index = 0;Index < 4;Index += 1){
        Settings_Integer.push_back(stoi(Settings[Index]));
    }

    Resolution_Horizontal = Settings_Integer[0];
    Resolution_Vertical = Settings_Integer[1];
    Number_Of_Photos_Horizontal = Settings_Integer[2];
    Number_Of_Photos_Vertical = Settings_Integer[3];

    cout << "Get settings from txt successful." << endl;

    return 0;
}

int Look_For_Input_Photo_Directory(){
    cout << "Looking for input photo directory." << endl;
    
    if(!fs::exists(In_Photos_Path)){
        cout << "Failed to find input photo directory." << endl;
        cout << "Check Paths.txt." << endl;

        return 1;
    }

    cout << "Found input photo directory" << endl;

    return 0;
}

int Get_Photo_Paths(){
    cout << "Gathering valid images from directory." << endl;

    vector<fs::path> Photo_Paths;

    for(const auto& PATH : fs::directory_iterator(In_Photos_Path)){
        if (PATH.is_regular_file() && (PATH.path().extension() == ".jpg" || PATH.path().extension() == ".jpeg")) {
            Photo_Paths.push_back(PATH);
        } else{
            cout << "Failed to input file \'" << PATH.path().string() << "\' " << "because of invalid file type, continuing." << endl;
        }
    }

    if(Photo_Paths.empty()){
        cout << "Found no valid photo files in directory.";

        return 1;
    }

    In_Photo_Paths = Photo_Paths;

    cout << "Found " << Photo_Paths.size() << " valid photo files from directory." << endl;

    return 0;
}

int Look_For_Output_Photo_Directory(){
    cout << "Looking for output photo directory." << endl;
    
    if(!fs::exists(Out_Photos_Path)){
        cout << "Failed to find output photo directory." << endl;
        cout << "Check Paths.txt." << endl;

        return 1;
    }

    cout << "Found output photo directory" << endl;

    return 0;
}

int Get_Label_Paths(){
    cout << "Gathering valid labels from directory." << endl;

    vector<fs::path> Label_Paths;

    for(const auto& PATH : fs::directory_iterator(In_Labels_Path)){
        if (PATH.is_regular_file() && (PATH.path().extension() == ".txt")) {
            Label_Paths.push_back(PATH);
        } else{
            cout << "Failed to input file \'" << PATH.path().string() << "\' " << "because of invalid file type, continuing." << endl;
        }
    }

    if(Label_Paths.empty()){
        cout << "Found no valid label files in directory.";

        return 1;
    }

    In_Label_Paths = Label_Paths;

    cout << "Found " << Label_Paths.size() << " valid label files from directory." << endl;

    return 0;
}

int Get_Valid_Label_Paths(){
    cout << "Getting valid label paths." << endl;

    if(Valid_Photo_Paths.empty() || Valid_Photo_Paths.front().empty()){
        cout << "No valid paths exists to compare." << endl;

        return 1;
    }

    vector<vector<fs::path>> Label_Paths;
    unordered_set<fs::path> In_Label_Paths_Umap(In_Label_Paths.begin(), In_Label_Paths.end());

    for(int Row = 0;Row < Valid_Photo_Paths.size();Row += 1){
        vector<fs::path> Paths;

        for(int Column = 0; Column < Valid_Photo_Paths.front().size();Column += 1){
            const fs::path PATH = fs::path(In_Labels_Path)/(Valid_Photo_Paths[Row][Column].stem().string() + ".txt");

            if(In_Label_Paths_Umap.find(PATH) == In_Label_Paths_Umap.end()){
                cout << "There are no labels for " << Valid_Photo_Paths[Row][Column].string() << "." << endl;
                Paths.push_back(fs::path{});

                continue;
            }

            Paths.push_back(PATH);
        }

        Label_Paths.push_back(Paths);
    }

    if(Label_Paths.empty()){
        cout << "Failed fo get valid label paths." << endl;

        return 1;
    }

    Valid_Label_Paths = Label_Paths;

    cout << "Found " << Valid_Label_Paths.size() * Valid_Label_Paths.front().size() << " valid label paths." << endl;

    return 0;
}

int Look_For_Input_Label_Directory(){
    cout << "Looking for input label directory." << endl;
    
    if(!fs::exists(In_Label_Paths)){
        cout << "Failed to find input label directory." << endl;
        cout << "Check Paths.txt." << endl;

        return 1;
    }

    cout << "Found input label directory" << endl;

    return 0;
}

int Look_For_Output_Label_Directory(){
    cout << "Looking for output label directory." << endl;
    
    if(!fs::exists(Out_Labels_Path)){
        cout << "Failed to find output label directory." << endl;
        cout << "Check Paths.txt." << endl;

        return 1;
    }

    cout << "Found output label directory" << endl;

    return 0;
}

int main(void){
    // Get path for exe file and it's directory to find the needed txt file.
    int Check = Get_Exe_File_Path();

    if(Check == 1){
        return 1;
    }

    // Get paths from the Paths.txt file
    Path_Txt_Location = Exe_Directory_Path + "../Paths.txt";

    Check = Get_Paths(Path_Txt_Location);

    if(Check == 1){
        return 1;
    }

    // Get settings from the Settings.txt file
    Settings_Txt_Location = Exe_Directory_Path + "../Settings.txt";

    Check = Get_Settings(Settings_Txt_Location);
    
    if(Check == 1){
        return 1;
    }

    // Look for input photo directory
    Check = Look_For_Input_Photo_Directory();
    
    if(Check == 1){
        return 1;
    }

    // Look for output photo directory
    Check = Look_For_Output_Photo_Directory();

    if(Check == 1){
        return 1;
    }

    // Gathering valid image file paths
    Check = Get_Photo_Paths();

    if(Check == 1){
        return 1;
    }

    // Look for input label directory
    Check = Look_For_Input_Label_Directory();
    
    if(Check == 1){
        return 1;
    }

    // Look for outout label directory.
    Check = Look_For_Output_Label_Directory();

    if(Check == 1){
        return 1;
    }

    // Gathering valid label paths
    Check = Get_Label_Paths();

    if(Check == 1){
        return 1;
    }

    // Mash photo
    Check = Mash_Photos(In_Photo_Paths, Valid_Photo_Paths, Out_Photos_Path, Resolution_Horizontal, Resolution_Vertical
                            , Number_Of_Photos_Horizontal, Number_Of_Photos_Vertical, VARIABLE_PATH);

    if(Check == 1){
        cout << "Failed to mash photos." << endl;
        return 1;
    }

    // Get valid label paths from the valid photo paths
    Check = Get_Valid_Label_Paths();

    if(Check == 1){
        return 1;
    }

    // Create labels
    Check = Create_Labels(Valid_Label_Paths, Out_Labels_Path, Resolution_Horizontal, Resolution_Vertical, 
                          Number_Of_Photos_Horizontal, Number_Of_Photos_Vertical);

    if(Check == 1){
        cout << "Failed to create scaled labels." << endl;
        return 1;
    }

    return 0;
}