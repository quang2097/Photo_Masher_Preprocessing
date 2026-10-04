#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

#ifndef READ_TXT_FILE
#define READ_TXT_FILE
typedef enum{
    ADDRESS_TXT, LABEL_TXT, SETTING_TXT
} Read_Txt_File_Mode;

inline void Process_Address(string& address);

vector<string> Read_Txt_File(const string FILE_PATH);

vector<string> Read_Txt_File(const string FILE_PATH, const Read_Txt_File_Mode TYPE);
#endif