#pragma once
#ifndef FLIP_PHOTO
#define FLIP_PHOTO
#include "libs/opencv.hpp"
namespace utils{
    namespace flip_photo{
        enum flip_direction{
            HORIZONTAL,
            VERTICAL,
            UPSIDE_DOWN
        };
    }
    static cv::Mat flip(const cv::Mat& INPUT, const flip_photo::flip_direction DIRECTION);
};
#endif