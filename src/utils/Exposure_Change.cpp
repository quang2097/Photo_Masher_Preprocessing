#include "libs/opencv.hpp"
#include <iostream>

using cv::Mat;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Adjusts the exposure of an image using a scaling factor.
     * 
     * @param INPUT Source image
     * @param EXPOSURE_FACTOR Multiplier for pixel values (1.0 = original, >1.0 = brighter, <1.0 = darker)
     * @return Processed cv::Mat
     */
    static cv::Mat Adjust_Exposure(const cv::Mat& INPUT, const double EXPOSURE_FACTOR) {
        if (INPUT.empty()) {
            cout << "\tCannot adjust exposure of an empty photo." << endl;
            return Mat{};
        }

        if (EXPOSURE_FACTOR <= 0.0) {
            cout << "\tWarning: Exposure factor must be greater than 0. Returning original image." << endl;
            return INPUT.clone();
        }

        Mat Output;
        // cv::convertScaleAbs multiplies each pixel by EXPOSURE_FACTOR and automatically saturates to 0-255
        cv::convertScaleAbs(INPUT, Output, EXPOSURE_FACTOR, 0.0);

        return Output;
    }

    /**
     * Adjusts the exposure of an image using a percentage change.
     * 
     * @param INPUT Source image
     * @param Percentage Percentage change (e.g., +50.0 for 50% brighter, -30.0 for 30% darker)
     * @return Processed cv::Mat
     */
    static cv::Mat Adjust_Exposure_Percent(const cv::Mat& INPUT, const double PERCENTAGE) {
        // Convert percentage to a scaling factor (e.g., +50% -> 1.5, -50% -> 0.5)
        const double EXPOSURE_FACTOR = 1.0 + (PERCENTAGE / 100.0);
        return Adjust_Exposure(INPUT, EXPOSURE_FACTOR);
    }
};