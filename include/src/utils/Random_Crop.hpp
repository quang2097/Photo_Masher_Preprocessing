#include "../../libs/core.hpp"

using cv::Mat;

#ifndef RANDOM_CROP
#define RANDOM_CROP
namespace utils{
    static Mat cropByPixels(const Mat& INPUT, const int CROP_WIDTH, const int CROP_HEIGHT);
    static Mat cropByPERCENTAGE(const Mat& INPUT, const double PERCENTAGE);
};
#endif