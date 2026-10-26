#include "../../libs/core.hpp"

using cv::Mat;

#ifndef ADD_NOISE
#define ADD_NOISE
namespace utils{
    static Mat applyShear(const Mat& INPUT, double Shear_X, double Shear_Y, const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0));
};
#endif