#include "../../include/libs/core.hpp"
#include <iostream>

using std::cout;
using std::endl;
using cv::Mat;

namespace utils{
    Mat Saturation_Change(const Mat& INPUT_BGR, float Saturation_Scale = 10){
        // Check for empty images.
        if(INPUT_BGR.empty()){
            cout << "Error: Could not add noise to empty image file." <<  endl;
            return Mat{};
        }

        cv::Mat Hsv_Image, Output_Bgr;

        // 1. Convert BGR to HSV color space
        cv::cvtColor(INPUT_BGR, Hsv_Image, cv::COLOR_BGR2HSV);

        // 2. Split the HSV Channels
        std::vector<cv::Mat> Channels;
        cv::split(Hsv_Image, Channels);

        // Channels[0] = Hue (0-179)
        // Channels[1] = Saturation (0-255)
        // Channels[2] = Value (0-255)

        // 3. Scale the Saturation channel
        // convertTo applies a multiplier (alpha) and an optional offset (beta): pixel = pixel * alpha + beta
        // It also automatically clamps values to stay within the valid 0-255 8-bit range.
        Channels[1].convertTo(Channels[1], -1, Saturation_Scale, 0);

        // 4. Merge Channels back together
        cv::merge(Channels, Hsv_Image);

        // 5. Convert back to BGR color space
        cv::cvtColor(Hsv_Image, Output_Bgr, cv::COLOR_HSV2BGR);

        return Output_Bgr;
    }
};