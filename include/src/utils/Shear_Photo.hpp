#pragma once
#ifndef SHEAR_PHOTO
#define SHEAR_PHOTO
#include "libs/opencv.hpp"
namespace utils{
    static cv::Mat Shear_Photo(const cv::Mat& INPUT, double Shear_X, double Shear_Y, const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0));
};
#endif