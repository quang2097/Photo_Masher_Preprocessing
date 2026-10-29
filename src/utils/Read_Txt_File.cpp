#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "utils/Read_Txt_File.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::fstream;

namespace utils{
    inline void Process_Address(string& Address){
        for(char& c:Address){
            if(c == '\\'){ 
                c = '/';
            }
        }
    }

    std::vector<std::string> Read_Txt_File(const std::string FILE_PATH){
        vector<string> Txt_Lines;
        fstream file(FILE_PATH);

        if(!file.is_open()){
            cout << "\tFailed to find \'" << FILE_PATH << "\'" << endl;
            return {};
        }

        string Line;
        while(getline(file, Line)){
            Txt_Lines.emplace_back(Line);
        }

        file.close();

        return Txt_Lines;
    }

    std::vector<std::string> Read_Txt_File(const std::string FILE_PATH, const read_txt_file::Read_Txt_File_Mode TYPE){
        vector<string> Txt_Lines;
        fstream file(FILE_PATH);

        if(!file.is_open()){
            cout << "\tFailed to open \'" << FILE_PATH << "\'" << endl;
            return {};
        }

        string Line;
        while(getline(file, Line)){
            switch(TYPE){
                case read_txt_file::ADDRESS_TXT:case read_txt_file::SETTING_TXT:{
                    if(Line.front() != '#'){
                        Txt_Lines.emplace_back(Line);
                    }

                    break;
                }
                
                case read_txt_file::LABEL_TXT:{
                    Txt_Lines.emplace_back(Line);

                    break;
                }
            }
        }

        file.close();

        return Txt_Lines;
    }
};