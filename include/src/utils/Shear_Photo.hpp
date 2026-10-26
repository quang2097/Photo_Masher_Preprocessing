#include "../../libs/core.hpp"

#ifndef SHEAR_PHOTO
#define SHEAR_PHOTO
namespace utils{
    static cv::Mat applyShear(const cv::Mat& INPUT, double Shear_X, double Shear_Y, const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0));
};
#endif