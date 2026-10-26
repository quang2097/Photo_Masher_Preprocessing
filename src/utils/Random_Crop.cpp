#include "../../include/libs/core.hpp"
#include <random>
#include <iostream>

using std::cout;
using std::endl;
using cv::Mat;

namespace utils{
    /**
     * Crops a random region of the image based on exact pixel dimensions.
     * 
     * @param INPUT Source image
     * @param CROP_WIDTH Width of the crop window in pixels
     * @param CROP_HEIGHT Height of the crop window in pixels
     * @return Cropped Mat
     */
    static cv::Mat cropByPixels(const cv::Mat& INPUT, const int CROP_WIDTH, const int CROP_HEIGHT) {
        if (INPUT.empty()) {
            cout << "Cannot apply random crop to emty Photo." << endl; 
            return Mat{};
        }

        if (CROP_WIDTH <= 0 || CROP_HEIGHT <= 0) {
            cout << "Cannot apply random crop with width " << CROP_WIDTH << " and height " << CROP_HEIGHT << endl; 
            return Mat{};
        }

        if (CROP_WIDTH > INPUT.cols || CROP_HEIGHT > INPUT.rows) {
            cout << "Cannot apply random crop with width and/or height larger than the photo dimensions." << endl;
            return Mat{};
        }

        // Setup random number generators for top-left coordinates
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> Dis_X(0, INPUT.cols - CROP_WIDTH);
        std::uniform_int_distribution<> Dis_Y(0, INPUT.rows - CROP_HEIGHT);

        int x = Dis_X(gen);
        int y = Dis_Y(gen);

        cv::Rect Roi(x, y, CROP_WIDTH, CROP_HEIGHT);
        return INPUT(Roi).clone(); // Clone to ensure memory independence
    }

    /**
     * Crops a random region of the image based on a PERCENTAGE while preserving the original aspect ratio.
     * 
     * @param INPUT Source image
     * @param PERCENTAGE PERCENTAGE of the original size (e.g., 50.0 means 50% of width and height)
     * @return Cropped Mat
     */
    static cv::Mat cropByPERCENTAGE(const cv::Mat& INPUT, const double PERCENTAGE) {
        if (INPUT.empty()) {
            cout << "Cannot apply random crop to empty Photo." << endl;
            return Mat{};
        }

        if (PERCENTAGE <= 0.0 || PERCENTAGE > 100.0) {
            cout << "Cannot apply random crop to photo with a percentage value of " << PERCENTAGE << endl;
            return Mat{};
        }

        // Compute new dimensions based on the PERCENTAGE, preserving the original ratio
        int Crop_Width = static_cast<int>(INPUT.cols * (PERCENTAGE / 100.0));
        int Crop_Height = static_cast<int>(INPUT.rows * (PERCENTAGE / 100.0));

        // Fallback safety to ensure valid dimensions
        Crop_Width = std::max(1, Crop_Width);
        Crop_Height = std::max(1, Crop_Height);

        // Delegate to the pixel-based cropper
        return cropByPixels(INPUT, Crop_Width, Crop_Height);
    }
};