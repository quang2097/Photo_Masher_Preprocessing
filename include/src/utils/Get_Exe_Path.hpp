#pragma once
#include <string>

#ifndef GET_EXE_PATH
#define GET_EXE_PATH
namespace utils{
    std::string Get_Executable_Path();
    std::string Get_Executable_Directory();
};
#endif