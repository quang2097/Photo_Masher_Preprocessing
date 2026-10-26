#pragma once
#include "../../libs/core.hpp"

#ifndef CUTOUT
#define CUTOUT
namespace utils{
    static cv::Mat Apply_Cutout_Pixels(const cv::Mat& INPUT, const int CUTOUT_WIDTH, const int CUTOUT_HEIGHT, 
                                    const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0));
    static cv::Mat Apply_Cutout_Percent(const cv::Mat& INPUT, const double WIDTH_PERCENT, const double HEIGHT_PERCENT, 
                                        const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0));
};
#endif