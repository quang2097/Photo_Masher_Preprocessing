#include <iostream>
#include <string>
#include <vector>
#include "../include/src/utils/Read_Txt_File.hpp"
#include "../include/src/utils/Get_Exe_Path.hpp"
#include "../include/src/Mash_Photos.hpp"
#include <filesystem>

namespace fs = std::filesystem;
using std::vector;
using std::cout;
using std::cin;
using std::string; 
using std::stoi;

string Exe_File_Path;
string Exe_Directory_Path;

string In_Labels_Path;
string In_Photos_Path;
string Out_Lables_Path;
string Out_Photos_Path;

vector<fs::path> In_Photo_Paths;

int Resolution_Horizontal = -1;
int Resolution_Vertical = -1;
int Number_Of_Photos_Horizontal = -1;
int Number_Of_Photos_Vertical = -1;

int Get_Paths(const string& TXT_PATH){
    vector<string> In_Out_Paths = Read_Txt_File(TXT_PATH, ADDRESS_TXT);;

    if(In_Out_Paths.empty() || In_Out_Paths.size() < 4){
        cout << "Cannot get paths from txt file." << endl;

        return 1;
    }

    In_Labels_Path = In_Out_Paths[0];
    In_Photos_Path = In_Out_Paths[1];
    Out_Lables_Path = In_Out_Paths[2];
    Out_Photos_Path = In_Out_Paths[3];

    return 0;
}

int Get_Settings(const string& TXT_PATH){
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
    Number_Of_Photos_Horizontal = Settings_Integer[3];

    return 0;
}

int Get_Photo_Paths(){
    vector<fs::path> Photo_Paths;

    for(const auto& PATH : fs::directory_iterator(In_Photo_Paths)){
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

int main(void){
    // Get path for exe file and it's directory to find the needed txt file.
    cout<< endl << "Getting exe file path." << endl;

    Exe_File_Path = Get_Executable_Path();

    Exe_Directory_Path = Get_Executable_Directory();

    if(Exe_File_Path.empty()){
        cout << "Cannot get exe path." << endl;
        cout << "Exit with error." << endl;

        return 1;
    }

    cout << "Exe file path found: " + Exe_File_Path << endl;

    // Get paths from the Paths.txt file
    const string PATH_TXT_LOCATION = Exe_Directory_Path + "../Paths.txt";

    cout << "Getting paths from txt" << endl;

    int Check = Get_Paths(PATH_TXT_LOCATION);

    if(!Check){
        return 1;
    }

    cout << "Get paths from txt successful." << endl;

    // Get settings from the Settings.txt file
    const string SETTINGS_TXT_LOCATION = Exe_Directory_Path + "../Settings.txt";

    cout << "Getting settings from txt" << endl;

    int Check = Get_Settings(SETTINGS_TXT_LOCATION);

    if(!Check){
        return 1;
    }

    cout << "Get settings from txt successful." << endl;

    // Look for input photo directory
    cout << "Looking for photo directory." << endl;
    
    if(!fs::exists(In_Photos_Path)){
        cout << "Failed to find input photo directory." << endl;
        cout << "Check Paths.txt." << endl;

        return 1;
    }

    cout << "Found input photo directory" << endl;

    // Gathering valid image file paths
    cout << "Gathering valid images from directory." << endl;

    int check = Get_Photo_Paths();

    if(check == 1){
        return 1;
    }

    // Look for output photo directory
    cout << "Looking for photo directory." << endl;
    
    if(!fs::exists(In_Photos_Path)){
        cout << "Failed to find output photo directory." << endl;
        cout << "Check Paths.txt." << endl;

        return 1;
    }

    cout << "Found output photo directory" << endl;

    //Mash photo
    

    return 0;
}   