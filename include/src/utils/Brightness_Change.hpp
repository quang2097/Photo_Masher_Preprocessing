#include "../../libs/core.hpp"

#ifndef BRIGHTNESS_CHANGE
#define BRIGHTNESS_CHANGE
namespace utils{
    cv::Mat Brightness_Change(const cv::Mat& INPUT_BGR, const int BRIGHTNESS_OFFSET = 10);
};
#endif