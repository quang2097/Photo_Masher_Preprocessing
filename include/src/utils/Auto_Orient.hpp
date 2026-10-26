#include "../../libs/core.hpp"

#ifndef AUTO_ORIENT
#define AUTO_ORIENT
namespace utils{
    cv::Mat Auto_Orient(const cv::Mat& SRC, const int EXIF_ORIENTATION = 1);
};
#endif