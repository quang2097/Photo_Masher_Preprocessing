#include "libs/opencv.hpp"
#include <iostream>

#include "utils/Auto_Orient.hpp"

using cv::Mat;
using std::cout;
using std::endl;

namespace utils{
    /**
     * Auto orient preprocessing function.
     * cv::Mat Auto_Orient(const cv::Mat& SRC, const auto_orient::Orientation EXIF_ORIENTATION)
     * enum auto_orient::Orientation{
     *  NORMAL, MIRRORED_HORIZONTAL, ROTATE_180, MIRRORED_VERTICAL, MIRRORED_HORIZONTAL_AND_ROTATE_90_COUNTERCLOCKWISE, 
     *  ROTATE_90_CLOCKWISE, MIRRORED_HORIZONTAL_AND_ROTATE_90_CLOCKWISE, ROTATE_90_COUNTERCLOCKWISE
     * }
     * 
     * @param SRC input the image in Mat datatype.
     * @param EXIF_ORIENTATION Pick the desired orientation.
     */
    // Function to apply auto-orientation based on the EXIF orientation tag (1-8)
    cv::Mat Auto_Orient(const cv::Mat& SRC, const auto_orient::Orientation EXIF_ORIENTATION){
        // Check for empty images.
        if(SRC.empty()){
            cout << "\tError: Could not apply auto orient to empty image file." <<  endl;
            return Mat{};
        }

        Mat Dst;

        switch (EXIF_ORIENTATION) {
            case auto_orient::NORMAL: // Normal
                return SRC.clone();
                
            case auto_orient::MIRRORED_HORIZONTAL: // Mirrored horizontal
                cv::flip(SRC, Dst, 1);
                return Dst;
                
            case auto_orient::ROTATE_180: // Rotated 180 degrees
                cv::rotate(SRC, Dst, cv::ROTATE_180);
                return Dst;

            case auto_orient::MIRRORED_VERTICAL: // Mirrored vertical
                cv::flip(SRC, Dst, 0);
                return Dst;
                
            case auto_orient::MIRRORED_HORIZONTAL_AND_ROTATE_90_COUNTERCLOCKWISE: // Mirrored horizontal and rotated 90 CCW
                cv::flip(SRC, Dst, 1);
                cv::rotate(Dst, Dst, cv::ROTATE_90_COUNTERCLOCKWISE);
                return Dst;
                
            case auto_orient::ROTATE_90_CLOCKWISE: // Rotated 90 degrees clockwise
                cv::rotate(SRC, Dst, cv::ROTATE_90_CLOCKWISE);
                return Dst;
                
            case auto_orient::MIRRORED_HORIZONTAL_AND_ROTATE_90_CLOCKWISE: // Mirrored horizontal and rotated 90 CW
                cv::flip(SRC, Dst, 1);
                cv::rotate(Dst, Dst, cv::ROTATE_90_CLOCKWISE);
                return Dst;
                
            case auto_orient::ROTATE_90_COUNTERCLOCKWISE: // Rotated 90 degrees counter-clockwise
                cv::rotate(SRC, Dst, cv::ROTATE_90_COUNTERCLOCKWISE);
                return Dst;
                
            default: // Unknown / Default fallback
                return SRC.clone();
        }
    }
};