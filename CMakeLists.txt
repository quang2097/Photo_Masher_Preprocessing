cmake_minimum_required(VERSION 3.10)

project(Photo_Masher_Preprocessing CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Photo_Masher_Program
    src/main.cpp
    src/Create_Labels.cpp
    src/Mash_Photos.cpp
    src//utils/Read_Txt_File.cpp
    src/utils/Resize_Photo.cpp
    src/utils/Load_Photos.cpp
    src/utils/Get_Exe_Path.cpp
)

target_include_directories(Photo_Masher_Program PRIVATE
    include
)

find_package(OpenCV REQUIRED PATHS libs/opencv_cpp/build)

target_link_libraries(Photo_Masher_Program PRIVATE ${OpenCV_LIBS})