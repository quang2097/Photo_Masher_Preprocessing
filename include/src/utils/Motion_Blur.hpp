#pragma once
#ifndef MOTION_BLUR
#define MOTION_BLUR
#include "libs/opencv.hpp"
namespace utils{
    static cv::Mat applyMotionBlur(const cv::Mat& INPUT, int Kernel_Size, const double ANGLE);
};
#endif