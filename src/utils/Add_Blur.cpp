#include <iostream>

#include "utils/Add_Blur.hpp"

using cv::Mat;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Applies a blur transformation to an image.
     * 
     * @param INPUT Source image
     * @param TYPE blur_type (GAUSSIAN, BOX, or MEDIAN)
     * @param Kernel_Size Size of the kernel filter (must be an odd number, e.g., 3, 5, 7)
     * @return Processed cv::Mat
     */

    static cv::Mat Add_Blur(const cv::Mat& INPUT, const add_blur::blur_type TYPE, int Kernel_Size) {
        if (INPUT.empty()) {
            cout << "Cannot apply blur preprocessing to an empty photo." << endl;
            return Mat{};
        }

        if (Kernel_Size <= 0) {
            cout << "Warning: Kernel size must be greater than 0. Returning original image." << endl;
            return INPUT.clone();
        }

        // Kernel size must be odd for Gaussian and Median blur
        if (Kernel_Size % 2 == 0) {
            Kernel_Size += 1;
            cout << "Warning: Kernel size must be an odd number. Adjusted to " << Kernel_Size << "." << endl;
        }

        Mat Output;
        switch (TYPE) {
            case add_blur::GAUSSIAN:
                cv::GaussianBlur(INPUT, Output, cv::Size(Kernel_Size, Kernel_Size), 0);
                break;
            case add_blur::BOX:
                cv::blur(INPUT, Output, cv::Size(Kernel_Size, Kernel_Size));
                break;
            case add_blur::MEDIAN:
                cv::medianBlur(INPUT, Output, Kernel_Size);
                break;
        }

        return Output;
    }
};