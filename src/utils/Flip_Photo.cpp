#include "libs/opencv.hpp"
#include <iostream>

#include "utils/Flip_Photo.hpp"

using cv::Mat;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Flips an image horizontally, vertically, or both.
     * 
     * @param INPUT Source image
     * @param direction FlipDirection (HORIZONTAL, VERTICAL, or BOTH)
     * @return Processed cv::Mat
     */
    static cv::Mat flip(const cv::Mat& INPUT, const flip_photo::flip_direction DIRECTION){
        Mat Output;
        if (INPUT.empty()) {
            cout << "Can't apply flip photo preprocessing for an empty photo." << endl;
            return Mat{};
        }

        int Flip_Code = 0;
        switch (DIRECTION) {
            case flip_photo::HORIZONTAL:
                Flip_Code = 1;  // Positive value flips around the y-axis
                break;
            case flip_photo::VERTICAL:
                Flip_Code = 0;  // Zero flips around the x-axis
                break;
            case flip_photo::UPSIDE_DOWN:
                Flip_Code = 2; // Negative value flips around both axes
                break;
        }

        cv::flip(INPUT, Output, Flip_Code); // Note: cv::flip is standard
        return Output;
    }
};