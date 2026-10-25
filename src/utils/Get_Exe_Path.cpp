#include <string>
#include <vector>
#include <filesystem>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#endif

using std::string;
using std::runtime_error;
using std::vector;

namespace utils{
    string Get_Executable_Path(){
        vector<char> Buffer(1024);
        uint32_t size = Buffer.size();

        //windows
        #if defined(_WIN32)
            DWORD len = GetModuleFileNameA(NULL, Buffer.data(), static_cast<DWORD>(Buffer.size()));
            if (len == 0) throw runtime_error("Failed to get executable path (Windows).");
            return std::filesystem::absolute(Buffer.data()).string();

        //linux
        #elif defined(__linux__)
            ssize_t len = readlink("/proc/self/exe", Buffer.data(), Buffer.size() - 1);
            if (len == -1) throw runtime_error("Failed to get executable path (Linux).");
            Buffer[len] = '\0';
            return std::filesystem::absolute(Buffer.data()).string();

        //mac OS
        #elif defined(__APPLE__)
            if (_NSGetExecutablePath(Buffer.data(), &size) != 0) {
                Buffer.resize(size);
                if (_NSGetExecutablePath(Buffer.data(), &size) != 0)
                    throw runtime_error("Failed to get executable path (macOS).");
            }
            return std::filesystem::absolute(Buffer.data()).string();

        //temple OS and others
        #else
            throw runtime_error("Unsupported platform.");
        #endif
    }

    //find the path of the executable file
    string Get_Executable_Directory(){
        return std::filesystem::path(Get_Executable_Path()).parent_path().string();
    }
};