cmake_minimum_required(VERSION 3.10)

project(ObjectSeparator CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(ObjectSeparator_program
    src/main.cpp
    src/Create_Labels.cpp
    src/Mash_Photos.cpp
    src//utils/Read_Txt_File.cpp
    src/utils/Resize_Photo.cpp
    src/utils/Load_Photos.cpp
    src/utils/Get_Exe_Path.cpp
)

target_include_directories(ObjectSeparator_program PRIVATE
    include
)

find_package(OpenCV REQUIRED PATHS libs/opencv_cpp/build_linux)

target_link_libraries(ObjectSeparator_program PRIVATE ${OpenCV_LIBS})