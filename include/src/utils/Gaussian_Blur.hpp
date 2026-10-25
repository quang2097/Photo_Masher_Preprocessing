#include "../../libs/core.hpp"

using cv::Mat;

#ifndef GAUSSIAN_BLUR
#define GAUSSIAN_BLUR

namespace utils{
    Mat Apply_Gaussian_Blur(Mat GRAYED_IMAGE);
    Mat Apply_Gaussian_Blur(Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2);
    Mat Apply_Gaussian_Blur(Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2, const int SIGMA_X);
    Mat Apply_Gaussian_Blur(Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2, const int SIGMA_X, const int SIGMA_Y);
};
#endif