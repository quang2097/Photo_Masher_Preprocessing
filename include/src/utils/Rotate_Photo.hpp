#pragma once
#ifndef ROTATE_PHOTO
#define ROTATE_PHOTO
#include "libs/opencv.hpp"
namespace utils{
    static cv::Mat rotate(const cv::Mat& INPUT, const double ANGLE_DEGREES, const bool EXPAND_CANVAS = true, 
                            const cv::Scalar& FILL_COLOR = cv::Scalar(0, 0, 0));
};
#endif