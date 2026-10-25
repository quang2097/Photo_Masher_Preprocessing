#include "../../libs/core.hpp"

using cv::Mat;

#ifndef HUE_CHANGE
#define HUE_CHANGE
namespace utils{
    Mat Hue_Change(const Mat& INPUT_BGR, const int HUE_SHIFT = 18);
};
#endif