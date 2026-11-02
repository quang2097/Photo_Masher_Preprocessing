#pragma once
#ifndef AUTO_ORIENT
#define AUTO_ORIENT
#include "libs/opencv.hpp"
namespace utils{
    namespace auto_orient{
        enum Orientation{
            NORMAL, MIRRORED_HORIZONTAL, ROTATE_180, MIRRORED_VERTICAL, MIRRORED_HORIZONTAL_AND_ROTATE_90_COUNTERCLOCKWISE, 
            ROTATE_90_CLOCKWISE, MIRRORED_HORIZONTAL_AND_ROTATE_90_CLOCKWISE, ROTATE_90_COUNTERCLOCKWISE
        };
    };
    cv::Mat Auto_Orient(const cv::Mat& SRC, const int EXIF_ORIENTATION = 1);
};
#endif