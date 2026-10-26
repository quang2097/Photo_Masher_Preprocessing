#include "../../libs/core.hpp"

#ifndef MOSEIC
#define MOSEIC
namespace utils{
    static cv::Mat applyMosaic(const cv::Mat& INPUT, const int BLOCK_SIZE);
};
#endif