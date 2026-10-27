#pragma once
#ifndef BRIGHTNESS_CHANGE
#define BRIGHTNESS_CHANGE
#include "libs/opencv.hpp"
namespace utils{
    cv::Mat Brightness_Change(const cv::Mat& INPUT_BGR, const int BRIGHTNESS_OFFSET = 10);
};
#endif