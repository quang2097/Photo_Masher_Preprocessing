#pragma once
#ifndef EXPOSURE_CHANGE
#define EXPOSURE_CHANGE
#include "libs/opencv.hpp"
namespace utils{
    static cv::Mat Adjust_Exposure(const cv::Mat& INPUT, const double EXPOSURE_FACTOR);
    static cv::Mat Adjust_Exposure_Percent(const cv::Mat& INPUT, const double PERCENTAGE);
};
#endif