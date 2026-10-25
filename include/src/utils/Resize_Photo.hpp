#include "../../libs/core.hpp"

using cv::Mat;

#ifndef RESIZE_PHOTO
#define RESIZE_PHOTO
namespace utils{
    Mat Resize_Photo(const Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL);
};
#endif