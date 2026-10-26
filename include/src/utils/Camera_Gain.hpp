#pragma once
#include "../../libs/core.hpp"

#ifndef CAMERA_GAIN
#define CAMERA_GAIN
namespace utils{
    static cv::Mat Apply_Gain(const cv::Mat& INPUT, const double GAIN_FACTOR);
};
#endif