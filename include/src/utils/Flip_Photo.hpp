#pragma once
#include "../../libs/core.hpp"

#ifndef FLIP_PHOTO
#define FLIP_PHOTO
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