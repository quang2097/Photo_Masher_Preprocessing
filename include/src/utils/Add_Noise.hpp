#include "../../libs/core.hpp"
#include <random>

using cv::Mat;

#ifndef NOISE_PREPROCESSING
#define NOISE_PREPROCESSING
class Noise_Preprocessor {
public:
    static Mat applyNoise(const Mat& INPUT, const NoiseTYPE TYPE, const double PERCENTAGE);
private:
    static void addSaltAndPepper(Mat& Img, const double PERCENTAGE);
    static void addGaussian(Mat& Img, double PERCENTAGE);
};
#endif