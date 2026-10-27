#include "libs/opencv.hpp"
#include <iostream>
#include <cmath>

using cv::Mat;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Applies a motion blur transformation to an image.
     * 
     * @param INPUT Source image
     * @param Kernel_Size Size of the kernel filter (determines blur length/strength, e.g., 15)
     * @param ANGLE ANGLE of the motion blur in degrees (e.g., 0.0, 45.0, 90.0)
     * @return Processed cv::Mat
     */
    static cv::Mat applyMotionBlur(const cv::Mat& INPUT, int Kernel_Size, const double ANGLE) {
        if (INPUT.empty()) {
            cout << "Cannot apply motion blur preprocessing to an empty photo." << endl;
            return Mat{};
        }

        if (Kernel_Size <= 1) {
            return INPUT.clone();
        }

        // Ensure kernel size is odd for accurate center alignment
        if (Kernel_Size % 2 == 0) {
            Kernel_Size += 1;
        }

        // Create an empty kernel filled with zeros
        Mat KERNEL = Mat::zeros(Kernel_Size, Kernel_Size, CV_32F);
        const int CENTER = Kernel_Size / 2;

        // Convert ANGLE to radians
        const double RAD = ANGLE * CV_PI / 180.0;
        const double COS_A = std::cos(RAD);
        const double SIN_A = std::sin(RAD);

        // Draw a directional line inside the kernel matrix to simulate motion
        for (int i = 0; i < Kernel_Size; ++i) {
            double offset = i - CENTER;
            int x = cvRound(CENTER + offset * COS_A);
            int y = cvRound(CENTER + offset * SIN_A);

            if (x >= 0 && x < Kernel_Size && y >= 0 && y < Kernel_Size) {
                KERNEL.at<float>(y, x) = 1.0f;
            }
        }

        // Normalize the kernel so image brightness remains balanced
        double sum = cv::sum(KERNEL)[0];
        if (sum > 0) {
            KERNEL /= sum;
        } else {
            KERNEL.at<float>(CENTER, CENTER) = 1.0f;
        }

        Mat output;
        // Apply the custom kernel convolution
        cv::filter2D(INPUT, output, -1, KERNEL);

        return output;
    }
};