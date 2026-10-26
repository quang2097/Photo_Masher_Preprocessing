#include "../../libs/core.hpp"
#include <iostream>

using cv::Mat;

#ifndef ROTATE_PHOTO
#define ROTATE_PHOTO
namespace utils{
    static Mat rotate(const Mat& INPUT, const double ANGLE_DEGREES, const bool EXPAND_CANVAS = true, const cv::Scalar& FILL_COLOR = cv::Scalar(0, 0, 0));
};
#endif