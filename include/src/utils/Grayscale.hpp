#pragma once
#include "../../libs/core.hpp"

#ifndef GRAYSCALE
#define GRAYSCALE
namespace utils{
    namespace grayscale{
        enum Grayscale_Setting{
            NO_GAUSSIAN, GAUSSIAN_DEFAULT, GAUSSIAN_CUSTOM
        };
    };

    cv::Mat Grayscale(const cv::Mat IMAGE);
    cv::Mat Grayscale_With_Gaussian(const cv::Mat IMAGE, int Size1 = 3, int Size2 = 3, int Sigma_X = 0, int Sigma_Y = 0, 
                                    const grayscale::Grayscale_Setting SETTING);
};
#endif