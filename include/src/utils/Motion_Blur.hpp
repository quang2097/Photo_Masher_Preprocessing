#include "../../libs/core.hpp"

#ifndef MOTION_BLUR
#define MOTION_BLUR
namespace utils{
    static cv::Mat applyMotionBlur(const cv::Mat& INPUT, int Kernel_Size, const double ANGLE);
};
#endif