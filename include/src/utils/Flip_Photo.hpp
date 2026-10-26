#include "../../libs/core.hpp"

using cv::Mat;

#ifndef FLIP_PHOTO
#define FLIP_PHOTO
namespace utils{
    namespace flip_photo{
        enum flip_direction{
            HORIZONTAL,
            VERTICAL,
            BOTH
        };
    }
    static Mat flip(const Mat& INPUT, const flip_photo::flip_direction DIRECTION);
};
#endif