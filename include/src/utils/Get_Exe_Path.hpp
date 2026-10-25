#include <string>

using std::string;

#ifndef GET_EXE_PATH
#define GET_EXE_PATH
namespace utils{
    string Get_Executable_Path();
    string Get_Executable_Directory();
};
#endif