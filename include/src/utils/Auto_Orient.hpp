#include "../../libs/core.hpp"

using cv::Mat;

#ifndef AUTO_ORIENT
#define AUTO_ORIENT
namespace utils{
    Mat Auto_Orient(const Mat& SRC, const int EXIF_ORIENTATION = 1);
};
#endif