#include "../../include/libs/core.hpp"
#include <iostream>

using cv::Mat;
using std::cout;
using std::endl;

namespace utils{
    Mat Brightness_Change(const Mat& INPUT_BGR, const int BRIGHTNESS_OFFSET = 10){
        // Check for empty images.
        if(INPUT_BGR.empty()){
            cout << "Error: Could not apply brightness change to empty image file." <<  endl;
            return Mat{};
        }

        Mat Hsv_Image, Output_Bgr;

        // 1. Convert BGR to HSV color space
        cv::cvtColor(INPUT_BGR, Hsv_Image, cv::COLOR_BGR2HSV);

        // 2. Split the HSV Channels
        std::vector<Mat> Channels;
        cv::split(Hsv_Image, Channels);

        // Channels[0] = Hue (0-179)
        // Channels[1] = Saturation (0-255)
        // Channels[2] = Value / Brightness (0-255)

        // 3. Adjust the Value channel
        // cv::add handles saturating arithmetic automatically (clamps values between 0 and 255)
        cv::add(Channels[2], BRIGHTNESS_OFFSET, Channels[2]);

        // 4. Merge Channels back together
        cv::merge(Channels, Hsv_Image);

        // 5. Convert back to BGR color space
        cv::cvtColor(Hsv_Image, Output_Bgr, cv::COLOR_HSV2BGR);

        return Output_Bgr;
    }
};