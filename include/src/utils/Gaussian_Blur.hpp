#pragma once
#ifndef GAUSSIAN_BLUR
#define GAUSSIAN_BLUR
#include "libs/opencv.hpp"
namespace utils{
    cv::Mat Apply_Gaussian_Blur(const cv::Mat GRAYED_IMAGE);
    cv::Mat Apply_Gaussian_Blur(const cv::Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2);
    cv::Mat Apply_Gaussian_Blur(const cv::Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2, const int SIGMA_X);
    cv::Mat Apply_Gaussian_Blur(const cv::Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2, const int SIGMA_X, const int SIGMA_Y);
};
#endif