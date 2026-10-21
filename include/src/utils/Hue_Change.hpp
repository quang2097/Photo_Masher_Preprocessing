#include "../../libs/core.hpp"
#include <iostream>

using std::cout;
using std::endl;
using cv::Mat;

#ifndef HUE_CHANGE
#define HUE_CHANGE
Mat Hue_Change(const Mat& INPUT_BGR, int Hue_Shift = 18);
#endif