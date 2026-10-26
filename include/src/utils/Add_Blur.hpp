#include "../../libs/core.hpp"

#ifndef ADD_BLUR
#define ADD_BLUR
namespace utils{
    namespace add_blur{
        enum blur_type {
            GAUSSIAN,
            BOX,
            MEDIAN
        };
    };
    static cv::Mat Add_Blur(const cv::Mat& INPUT, const add_blur::blur_type TYPE, int Kernel_Size);
};
#endif