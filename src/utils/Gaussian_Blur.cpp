#include "../../include/libs/core.hpp"
#include <iostream>

using cv::Mat;
using std::cout;
using std::endl;

namespace utils{
    Mat Apply_Gaussian_Blur(const Mat GRAYED_IMAGE){
        if(GRAYED_IMAGE.empty()){
            cout << "Error: Could not apply Gaussian blur to empty image file." <<  endl;
            return Mat{};
        }

        // Apply Gaussian Blur to reduce noise.
        Mat Blurred_Gray;
        cv::GaussianBlur(GRAYED_IMAGE, Blurred_Gray, cv::Size(3, 3), 0);

        return Blurred_Gray;
    }

    Mat Apply_Gaussian_Blur(const Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2){
        if(GRAYED_IMAGE.empty()){
            cout << "Error: Could not apply Gaussian blur to empty image file." <<  endl;
            return Mat{};
        }

        // Apply Gaussian Blur to reduce noise.
        Mat Blurred_Gray;
        cv::GaussianBlur(GRAYED_IMAGE, Blurred_Gray, cv::Size(SIZE1, SIZE2), 0);

        return Blurred_Gray;
    }

    Mat Apply_Gaussian_Blur(Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2, const int SIGMA_X){
        if(GRAYED_IMAGE.empty()){
            cout << "Error: Could not apply Gaussian blur to empty image file." <<  endl;
            return Mat{};
        }

        // Apply Gaussian Blur to reduce noise.
        Mat Blurred_Gray;
        cv::GaussianBlur(GRAYED_IMAGE, Blurred_Gray, cv::Size(SIZE1, SIZE2), SIGMA_X);

        return Blurred_Gray;
    }

    Mat Apply_Gaussian_Blur(Mat GRAYED_IMAGE, const int SIZE1, const int SIZE2, const int SIGMA_X, const int SIGMA_Y){
        // Check for empty images.
        if(GRAYED_IMAGE.empty()){
            cout << "Error: Could not apply Gaussian blur to empty image file." <<  endl;
            return Mat{};
        }

        // Apply Gaussian Blur to reduce noise.
        Mat Blurred_Gray;
        cv::GaussianBlur(GRAYED_IMAGE, Blurred_Gray, cv::Size(SIZE1, SIZE2), SIGMA_X, SIGMA_Y);

        return Blurred_Gray;
    }
};