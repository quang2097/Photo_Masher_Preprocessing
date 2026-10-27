#pragma once
#ifndef HUE_CHANGE
#define HUE_CHANGE
#include "libs/opencv.hpp"
namespace utils{
    cv::Mat Hue_Change(const cv::Mat& INPUT_BGR, const int HUE_SHIFT = 18);
};
#endif