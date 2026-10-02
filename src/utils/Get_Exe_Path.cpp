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

string Get_Executable_Path() {
    vector<char> buffer(1024);
    uint32_t size = buffer.size();

    //windows
    #if defined(_WIN32)
        DWORD len = GetModuleFileNameA(NULL, buffer.data(), static_cast<DWORD>(buffer.size()));
        if (len == 0) throw runtime_error("Failed to get executable path (Windows).");
        return std::filesystem::absolute(buffer.data()).string();

    //linux
    #elif defined(__linux__)
        ssize_t len = readlink("/proc/self/exe", buffer.data(), buffer.size() - 1);
        if (len == -1) throw runtime_error("Failed to get executable path (Linux).");
        buffer[len] = '\0';
        return std::filesystem::absolute(buffer.data()).string();

    //mac OS
    #elif defined(__APPLE__)
        if (_NSGetExecutablePath(buffer.data(), &size) != 0) {
            buffer.resize(size);
            if (_NSGetExecutablePath(buffer.data(), &size) != 0)
                throw runtime_error("Failed to get executable path (macOS).");
        }
        return std::filesystem::absolute(buffer.data()).string();

    //temple OS and others
    #else
        throw runtime_error("Unsupported platform.");
    #endif
}

//find the path of the executable file
string Get_Executable_Directory() {
    return std::filesystem::path(Get_Executable_Path()).parent_path().string();
}