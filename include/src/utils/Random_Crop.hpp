#include "../../libs/core.hpp"

#ifndef RANDOM_CROP
#define RANDOM_CROP
namespace utils{
    static cv::Mat cropByPixels(const cv::Mat& INPUT, const int CROP_WIDTH, const int CROP_HEIGHT);
    static cv::Mat cropByPERCENTAGE(const cv::Mat& INPUT, const double PERCENTAGE);
};
#endif