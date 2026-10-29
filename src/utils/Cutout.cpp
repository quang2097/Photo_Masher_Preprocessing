#include "libs/opencv.hpp"
#include <random>
#include <iostream>

using cv::Mat;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Applies a random cutout (erases a rectangular region) using exact pixel dimensions.
     * 
     * @param INPUT Source image
     * @param CUTOUT_WIDTH Width of the cutout box in pixels
     * @param CUTOUT_HEIGHT Height of the cutout box in pixels
     * @param Fill_Color Color used to fill the cutout box (default black)
     * @return Processed cv::Mat
     */
    static cv::Mat Apply_Cutout_Pixels(const cv::Mat& INPUT, const int CUTOUT_WIDTH, const int CUTOUT_HEIGHT, 
                                    const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0)) {
        if (INPUT.empty()) {
            cout << "\tCannot apply cutout preprocessing to an empty photo." << endl;
            return Mat{};
        }

        if (CUTOUT_WIDTH <= 0 || CUTOUT_HEIGHT <= 0) {
            cout << "\tWarning: Cutout dimensions must be greater than zero. Returning original image." << endl;
            return INPUT.clone();
        }

        if (CUTOUT_WIDTH > INPUT.cols || CUTOUT_HEIGHT > INPUT.rows) {
            cout << "\tWarning: Cutout dimensions cannot be larger than the image dimensions. Returning original image." << endl;
            return INPUT.clone();
        }

        Mat Output = INPUT.clone();

        // Setup random number generators for top-left coordinates within valid bounds
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> Dis_X(0, INPUT.cols - CUTOUT_WIDTH);
        std::uniform_int_distribution<> Dis_Y(0, INPUT.rows - CUTOUT_HEIGHT);

        int x = Dis_X(gen);
        int y = Dis_Y(gen);

        // Define the rectangular region of interest and fill it
        cv::Rect Roi(x, y, CUTOUT_WIDTH, CUTOUT_HEIGHT);
        Output(Roi).setTo(Fill_Color);

        return Output;
    }

    /**
     * Applies a random cutout using percentages of the original image dimensions.
     * 
     * @param INPUT Source image
     * @param WIDTH_PERCENT Percentage of image width for the cutout (0.0 to 100.0)
     * @param HEIGHT_PERCENT Percentage of image height for the cutout (0.0 to 100.0)
     * @param Fill_Color Color used to fill the cutout box (default black)
     * @return Processed cv::Mat
     */
    static cv::Mat Apply_Cutout_Percent(const cv::Mat& INPUT, const double WIDTH_PERCENT, const double HEIGHT_PERCENT, const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0)) {
        if (INPUT.empty()) {
            cout << "\tCannot apply cutout preprocessing to an empty photo." << endl;
            return Mat{};
        }

        if (WIDTH_PERCENT <= 0.0 || WIDTH_PERCENT > 100.0 || HEIGHT_PERCENT <= 0.0 || HEIGHT_PERCENT > 100.0) {
            cout << "\tWarning: Percentages must be between 0.0 and 100.0. Returning original image." << endl;
            return INPUT.clone();
        }

        int cutoutWidth = static_cast<int>(INPUT.cols * (WIDTH_PERCENT / 100.0));
        int cutoutHeight = static_cast<int>(INPUT.rows * (HEIGHT_PERCENT / 100.0));

        return Apply_Cutout_Pixels(INPUT, cutoutWidth, cutoutHeight, Fill_Color);
    }
};