#include "../../include/libs/core.hpp"
#include <iostream>

using std::cout;
using std::endl;
using cv::Mat;

namespace utils{
    Mat Hue_Change(const Mat& INPUT_BGR, int Hue_Shift = 18){
        // Check for empty images.
        if(INPUT_BGR.empty()){
            cout << "Error: Could not apply hue change to empty image file." <<  endl;
            return Mat{};
        }

        Mat Hsv_Image, Modified_Hsv, Output_Bgr;

        // 1. Convert BGR to HSV color space
        cv::cvtColor(INPUT_BGR, Hsv_Image, cv::COLOR_BGR2HSV);

        // 2. Split the HSV Channels so we can modify Hue independently
        std::vector<Mat> Channels;
        cv::split(Hsv_Image, Channels);

        // Channels[0] is Hue, Channels[1] is Saturation, Channels[2] is Value
        // Note: OpenCV uses 0-179 for Hue because 360 degrees fits into an 8-bit unsigned char (0-255).
        // We use cv::add to handle automatic saturation/wrapping at boundaries (0 and 179).
        cv::add(Channels[0], Hue_Shift, Channels[0]);

        // 3. Merge the Channels back together
        cv::merge(Channels, Modified_Hsv);

        // 4. Convert back to BGR color space for saving or model ingestion
        cv::cvtColor(Modified_Hsv, Output_Bgr, cv::COLOR_HSV2BGR);

        return Output_Bgr;
    }
};