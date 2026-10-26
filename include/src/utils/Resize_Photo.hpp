#include "../../libs/core.hpp"

#ifndef RESIZE_PHOTO
#define RESIZE_PHOTO
namespace utils{
    cv::Mat Resize_Photo(const cv::Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL);
};
#endif