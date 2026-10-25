#include "../../include/libs/core.hpp"
#include <iostream>

using cv::Mat;
using std::cout;
using std::endl;

namespace utils{
    // Function to apply auto-orientation based on the EXIF orientation tag (1-8)
    Mat Auto_Orient(const Mat& SRC, int Exif_Orientation = 1){
        // Check for empty images.
        if(SRC.empty()){
            cout << "Error: Could not apply auto orient to empty image file." <<  endl;
            return Mat{};
        }

        Mat Dst;

        switch (Exif_Orientation) {
            case 1: // Normal
                return SRC.clone();
                
            case 2: // Mirrored horizontal
                cv::flip(SRC, Dst, 1);
                return Dst;
                
            case 3: // Rotated 180 degrees
                cv::rotate(SRC, Dst, cv::ROTATE_180);
                return Dst;
                
            case 4: // Mirrored vertical
                cv::flip(SRC, Dst, 0);
                return Dst;
                
            case 5: // Mirrored horizontal and rotated 90 CCW
                cv::flip(SRC, Dst, 1);
                cv::rotate(Dst, Dst, cv::ROTATE_90_COUNTERCLOCKWISE);
                return Dst;
                
            case 6: // Rotated 90 degrees clockwise
                cv::rotate(SRC, Dst, cv::ROTATE_90_CLOCKWISE);
                return Dst;
                
            case 7: // Mirrored horizontal and rotated 90 CW
                cv::flip(SRC, Dst, 1);
                cv::rotate(Dst, Dst, cv::ROTATE_90_CLOCKWISE);
                return Dst;
                
            case 8: // Rotated 90 degrees counter-clockwise
                cv::rotate(SRC, Dst, cv::ROTATE_90_COUNTERCLOCKWISE);
                return Dst;
                
            default: // Unknown / Default fallback
                return SRC.clone();
        }
    }
};