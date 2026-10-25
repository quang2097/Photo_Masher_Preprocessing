#include "../../libs/core.hpp"

using cv::Mat;

#ifndef BRIGHTNESS_CHANGE
#define BRIGHTNESS_CHANGE
namespace utils{
    Mat Brightness_Change(const Mat& INPUT_BGR, const int BRIGHTNESS_OFFSET = 10);
};
#endif