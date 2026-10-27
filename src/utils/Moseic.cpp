#include "libs/opencv.hpp"
#include <iostream>

using cv::Mat;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Applies a mosaic (pixelation) effect to an image.
     * 
     * @param INPUT Source image
     * @param BLOCK_SIZE Size of each mosaic block in pixels (e.g., 10 for 10x10 blocks)
     * @return Processed cv::Mat
     */
    static cv::Mat applyMosaic(const cv::Mat& INPUT, const int BLOCK_SIZE) {
        if (INPUT.empty()) {
            cout << "Cannot apply mosaic preprocessing to an empty photo." << endl;
            return Mat{};
        }

        if (BLOCK_SIZE <= 1) {
            return INPUT.clone();
        }

        int Width = INPUT.cols;
        int Height = INPUT.rows;

        // Calculate reduced dimensions for pixelation
        int Target_Width = std::max(1, Width / BLOCK_SIZE);
        int Target_Height = std::max(1, Height / BLOCK_SIZE);

        Mat Small, Output;
        
        // Step 1: Downscale using nearest-neighbor interpolation
        cv::resize(INPUT, Small, cv::Size(Target_Width, Target_Height), 0, 0, cv::INTER_NEAREST);
        
        // Step 2: Upscale back to original dimensions to create blocky mosaic pixels
        cv::resize(Small, Output, cv::Size(Width, Height), 0, 0, cv::INTER_NEAREST);

        return Output;
    }
};