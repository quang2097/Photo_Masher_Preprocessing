#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::fstream;

typedef enum{
    ADDRESS_TXT, LABEL_TXT, SETTING_TXT
} Read_Txt_File_Mode;

inline void Process_Address(string& Address){
    for(char& c:Address){
        if(c == '\\'){ 
            c = '/';
        }
    }
}

vector<string> Read_Txt_File(const string FILE_PATH){
    vector<string> Txt_Lines;
    fstream file(FILE_PATH);

    if(!file.is_open()){
        cout << "Failed to find \'" << FILE_PATH << "\'" << endl;
        return {};
    }

    string Line;
    while(getline(file, Line)){
        Txt_Lines.emplace_back(Line);
    }

    file.close();

    return Txt_Lines;
}

vector<string> Read_Txt_File(const string FILE_PATH, const Read_Txt_File_Mode TYPE){
    vector<string> Txt_Lines;
    fstream file(FILE_PATH);

    if(!file.is_open()){
        cout << "Failed to open \'" << FILE_PATH << "\'" << endl;
        return {};
    }

    string Line;
    while(getline(file, Line)){
        switch(TYPE){
            case ADDRESS_TXT:case SETTING_TXT:{
                if(Line.front() != '#'){
                    Txt_Lines.emplace_back(Line);
                }

                break;
            }
            
            case LABEL_TXT:{
                Txt_Lines.emplace_back(Line);

                break;
            }
        }
    }

    file.close();

    return Txt_Lines;
}