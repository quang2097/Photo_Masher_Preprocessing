#pragma once
#ifndef LOAD_PHOTOS
#define LOAD_PHOTOS
#include "libs/opencv.hpp"
#include <string>
namespace utils{
    cv::Mat Get_Photo(const std::string PATH);
};
#endif