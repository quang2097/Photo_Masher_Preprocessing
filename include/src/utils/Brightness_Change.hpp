#include "../../libs/core.hpp"

using cv::Mat;

#ifndef BRIGHTNESS_CHANGE
#define BRIGHTNESS_CHANGE
namespace utils{
    Mat Brightness_Change(const Mat& INPUT_BGR, int Brightness_Offset = 10);
};
#endif