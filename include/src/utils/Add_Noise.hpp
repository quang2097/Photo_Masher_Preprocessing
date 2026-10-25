#include "../../libs/core.hpp"

using cv::Mat;

#ifndef NOISE_PREPROCESSING
#define NOISE_PREPROCESSING
namespace utils{
    namespace noise_preprocessor{
        enum Noise_Type{
            SALT_AND_PEPPER, GAUSSIAN
        };
    };
    static Mat Add_Noise(const Mat& INPUT, const noise_preprocessor::Noise_Type TYPE, const double PERCENTAGE);
};
#endif