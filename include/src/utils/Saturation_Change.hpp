#pragma once
#ifndef SATURATION_CHANGE
#define SATURATION_CHANGE
#include "libs/opencv.hpp"
namespace utils{
    cv::Mat Saturation_Change(const cv::Mat& INPUT_BGR, const float SATURATION_SCALE = 10);
};
#endif