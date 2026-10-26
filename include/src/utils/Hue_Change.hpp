#pragma once
#include "../../libs/core.hpp"

#ifndef HUE_CHANGE
#define HUE_CHANGE
namespace utils{
    cv::Mat Hue_Change(const cv::Mat& INPUT_BGR, const int HUE_SHIFT = 18);
};
#endif