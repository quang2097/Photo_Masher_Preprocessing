#pragma once
#ifndef READ_TXT_FILE
#define READ_TXT_FILE
#include <string>
namespace utils{
    namespace read_txt_file{
        enum Read_Txt_File_Mode{
            ADDRESS_TXT, LABEL_TXT, SETTING_TXT
        };
    };

    std::vector<std::string> Read_Txt_File(const std::string FILE_PATH);
    std::vector<std::string> Read_Txt_File(const std::string FILE_PATH, const read_txt_file::Read_Txt_File_Mode TYPE);
};
#endif