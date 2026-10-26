#include "../../include/libs/core.hpp"
#include <iostream>

using cv::Mat;
using std::cout;
using std::endl;

namespace utils{
    /**
     * Rotates an image by any arbitrary angle.
     * 
     * @param INPUT Source image
     * @param ANGLE_DEGREES Rotation angle in degrees (positive is counter-clockwise, negative is clockwise)
     * @param EXPAND_CANVAS If true, the Output canvas expands to fit the rotated image without cropping corners.
     *                     If false, keeps the original image dimensions (corners will be cut off).
     * @param FILL_COLOR Color used for background padding if canvas expands (default is black)
     * @return Processed Mat
     */
    static Mat rotate(const Mat& INPUT, const double ANGLE_DEGREES, const bool EXPAND_CANVAS = true, const cv::Scalar& FILL_COLOR = cv::Scalar(0, 0, 0)) {
        if (INPUT.empty()) {
            cout << "Cannot rotate an empty photo." << endl;
            return Mat{};
        }

        // CENTER of rotation
        const cv::Point2f CENTER(INPUT.cols / 2.0f, INPUT.rows / 2.0f);

        // Get the rotation matrix for the specified angle
        Mat Rot_Mat = cv::getRotationMatrix2D(CENTER, ANGLE_DEGREES, 1.0);

        if (EXPAND_CANVAS) {
            // Compute the bounding box of the rotated image to prevent corner clipping
            cv::Rect2f Bbox = cv::RotatedRect(cv::Point2f(), INPUT.size(), ANGLE_DEGREES).boundingRect2f();

            // Adjust the transformation matrix to account for the translation shift
            Rot_Mat.at<double>(0, 2) += Bbox.width / 2.0 - CENTER.x;
            Rot_Mat.at<double>(1, 2) += Bbox.height / 2.0 - CENTER.y;

            Mat Output;
            cv::warpAffine(INPUT, Output, Rot_Mat, Bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, FILL_COLOR);
            return Output;
        } else {
            // Keep original image dimensions
            Mat Output;
            cv::warpAffine(INPUT, Output, Rot_Mat, INPUT.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, FILL_COLOR);
            return Output;
        }
    }
};