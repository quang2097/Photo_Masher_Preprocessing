#include "libs/opencv.hpp"
#include <iostream>
#include <cmath>

using cv::Mat;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Applies camera gain to an image using a linear multiplier factor.
     * 
     * @param INPUT Source image
     * @param GAIN_FACTOR Linear gain multiplier (1.0 = no change, >1.0 = amplify signal)
     * @return Processed cv::Mat
     */
    static cv::Mat Apply_Gain(const cv::Mat& INPUT, const double GAIN_FACTOR){
        if (INPUT.empty()) {
            cout << "Cannot apply camera gain to an empty photo." << endl;
            return Mat{};
        }

        if (GAIN_FACTOR < 0.0){
            cout << "Warning: Gain factor cannot be negative. Returning original image." << endl;
            return INPUT.clone();
        }

        Mat Output;
        // cv::convertScaleAbs multiplies each pixel by GAIN_FACTOR and automatically saturates to 0-255
        cv::convertScaleAbs(INPUT, Output, GAIN_FACTOR, 0.0);

        return Output;
    }

    /**
     * Applies camera gain specified in decibels (dB), common in industrial/machine vision cameras.
     * Formula: Linear Gain = 10^(dB / 20)
     * 
     * @param INPUT Source image
     * @param Gain_dB Gain value in decibels (e.g., 6.0 dB, 12.0 dB)
     * @return Processed cv::Mat
     */
    static cv::Mat Apply_Gain_DB(const cv::Mat& INPUT, double Gain_dB) {
        // Convert dB to a linear gain factor: Factor = 10^(dB / 20)
        double gainFactor = std::pow(10.0, Gain_dB / 20.0);
        return Apply_Gain(INPUT, gainFactor);
    }
};