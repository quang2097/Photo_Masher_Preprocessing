#include "../../libs/core.hpp"
#include <iostream>

using cv::Mat;

#ifndef BRIGHTNESS_CHANGE
#define BRIGHTNESS_CHANGE
Mat Brightness_Change(const Mat& INPUT_BGR, int Brightness_Offset = 10);
#endif