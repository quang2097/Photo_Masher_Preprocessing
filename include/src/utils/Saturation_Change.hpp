#include "../../libs/core.hpp"
#include <iostream>

using std::cout;

#ifndef SATURATION_CHANGE
#define SATURATION_CHANGE
Mat Saturation_Change(const Mat& INPUT_BGR, float Saturation_Scale = 10);
#endif