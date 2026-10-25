#include "../../libs/core.hpp"
#include <iostream>

using cv::Mat;

#ifndef SATURATION_CHANGE
#define SATURATION_CHANGE
namespace utils{
    Mat Saturation_Change(const Mat& INPUT_BGR, float Saturation_Scale = 10);
};
#endif