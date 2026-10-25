#include "../../libs/core.hpp"

using cv::Mat;

#ifndef HUE_CHANGE
#define HUE_CHANGE
namespace utils{
    Mat Hue_Change(const Mat& INPUT_BGR, int Hue_Shift = 18);
};
#endif