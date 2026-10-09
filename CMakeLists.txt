cmake_minimum_required(VERSION 3.10)

project(Photo_Masher_Preprocessing CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Create a library for your utility and helper sources
add_library(Photo_Masher_Utils STATIC
    src/Create_Labels.cpp
    src/Mash_Photos.cpp
    src/utils/Read_Txt_File.cpp
    src/utils/Resize_Photo.cpp
    src/utils/Load_Photos.cpp
    src/utils/Get_Exe_Path.cpp
)

# Attach include directories directly to the utility library target
target_include_directories(Photo_Masher_Utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 2. Create the main executable (containing only entry point main.cpp)
add_executable(Photo_Masher_Program
    src/main.cpp
)

# 3. Find external dependencies
find_package(OpenCV REQUIRED PATHS libs/opencv_cpp/build)

# Link your internal library AND external OpenCV library to the main target
# CMake will compile Photo_Masher_Utils before Photo_Masher_Program automatically
target_link_libraries(Photo_Masher_Program PRIVATE
    Photo_Masher_Utils
    ${OpenCV_LIBS}
)