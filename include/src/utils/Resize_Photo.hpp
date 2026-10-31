#pragma once
#ifndef RESIZE_PHOTO
#define RESIZE_PHOTO
#include "libs/opencv.hpp"
namespace utils{
    namespace resize_photo{
        enum setting{
            RESIZE, WHITE_BORDER, BLACK_BORDER, CUSTOM_COLORED_BORDER
        };
    };
    cv::Mat Resize_Photo(const cv::Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL);
};
#endif