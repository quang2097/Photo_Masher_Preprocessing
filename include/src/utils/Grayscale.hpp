#include "../../libs/core.hpp"
#include <iostream>
#include "./Gaussian_Blur.hpp"

using cv::Mat;

#ifndef GRAYSCALE
#define GRAYSCALE
Mat Grayscale(const Mat IMAGE);
Mat Grayscale(const Mat IMAGE, int Size1 = 3, int Size2 = 3, int Sigma_X = 0, int Sigma_Y = 0, const Grayscale_Setting SETTING);
#endif