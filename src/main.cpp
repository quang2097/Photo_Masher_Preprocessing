#include <iostream>
#include <string>
#include <vector>
#include "../include/src/utils/Read_Txt_File.hpp"
#include "../include/src/utils/Get_Exe_Path.hpp"

using std::vector;
using std::cout;
using std::cin;
using std::string; 

string Exe_File_Path;
string Exe_Directory_Path;

string In_Labels_Path;
string In_Photos_Path;
string Out_Lables_Path;
string Out_Photos_Path;

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
    vector<string> In_Out_Paths = Read_Txt_File(TXT_PATH, SETTING_TXT);;

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

    int Check = Get_Settings(SETTINGS_TXT_LOCATION)

    // Get photos for mashing.


    return 0;
}   