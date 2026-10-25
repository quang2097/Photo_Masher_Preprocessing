#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

#ifndef READ_TXT_FILE
#define READ_TXT_FILE
namespace utils{
    namespace read_txt_file{
        enum Read_Txt_File_Mode{
            ADDRESS_TXT, LABEL_TXT, SETTING_TXT
        };
    };

    vector<string> Read_Txt_File(const string FILE_PATH);
    vector<string> Read_Txt_File(const string FILE_PATH, const read_txt_file::Read_Txt_File_Mode TYPE);
};
#endif