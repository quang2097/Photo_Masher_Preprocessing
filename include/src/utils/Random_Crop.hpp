#pragma once
#ifndef RANDOM_CROP
#define RANDOM_CROP
#include "libs/opencv.hpp"
namespace utils{
    static cv::Mat cropByPixels(const cv::Mat& INPUT, const int CROP_WIDTH, const int CROP_HEIGHT);
    static cv::Mat cropByPERCENTAGE(const cv::Mat& INPUT, const double PERCENTAGE);
};
#endif