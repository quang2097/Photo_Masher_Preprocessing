#pragma once
#ifndef MOSEIC
#define MOSEIC
#include "libs/opencv.hpp"
namespace utils{
    static cv::Mat applyMosaic(const cv::Mat& INPUT, const int BLOCK_SIZE);
};
#endif