#include "../../libs/core.hpp"

using cv::Mat;

#ifndef GRAYSCALE
#define GRAYSCALE
namespace utils{
    namespace grayscale{
        enum Grayscale_Setting{
            NO_GAUSSIAN, GAUSSIAN_DEFAULT, GAUSSIAN_CUSTOM
        };
    };

    Mat Grayscale(const Mat IMAGE);
    Mat Grayscale_With_Gaussian(const Mat IMAGE, int Size1 = 3, int Size2 = 3, int Sigma_X = 0, int Sigma_Y = 0, const grayscale::Grayscale_Setting SETTING);
};
#endif