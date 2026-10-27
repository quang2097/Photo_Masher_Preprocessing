#pragma once
#ifndef AUTO_ORIENT
#define AUTO_ORIENT
#include "libs/opencv.hpp"
namespace utils{
    cv::Mat Auto_Orient(const cv::Mat& SRC, const int EXIF_ORIENTATION = 1);
};
#endif