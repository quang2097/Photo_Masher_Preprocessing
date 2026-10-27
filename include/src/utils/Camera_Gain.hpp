#pragma once
#ifndef CAMERA_GAIN
#define CAMERA_GAIN
#include "libs/opencv.hpp"
namespace utils{
    static cv::Mat Apply_Gain(const cv::Mat& INPUT, const double GAIN_FACTOR);
};
#endif