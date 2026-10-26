#pragma once
#include "../../libs/core.hpp"

#ifndef SATURATION_CHANGE
#define SATURATION_CHANGE
namespace utils{
    cv::Mat Saturation_Change(const cv::Mat& INPUT_BGR, const float SATURATION_SCALE = 10);
};
#endif