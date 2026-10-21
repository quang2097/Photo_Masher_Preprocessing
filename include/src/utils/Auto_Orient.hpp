#include "../../libs/core.hpp"
#include <iostream>

using cv::Mat;

#ifndef AUTO_ORIENT
#define AUTO_ORIENT
Mat Auto_Orient(const Mat& SRC, int Exif_Orientation = 1);
#endif