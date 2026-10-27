#include "libs/opencv.hpp"
#include <vector>
#include <iostream>

using cv::Mat;
using std::vector;
using std::endl;
using std::cout;

namespace utils{
    /**
     * Applies a shear transformation to an image.
     * 
     * @param INPUT Source image
     * @param Shear_X Horizontal shear factor (shifts X based on Y)
     * @param Shear_Y Vertical shear factor (shifts Y based on X)
     * @param Fill_Color Color used for background padding of expanded areas (default black)
     * @return Processed cv::Mat
     */
    static cv::Mat Shear_Photo(const cv::Mat& INPUT, double Shear_X, double Shear_Y, const cv::Scalar& Fill_Color = cv::Scalar(0, 0, 0)) {
        if (INPUT.empty()) {
            cout << "Cannot apply shear preprocessing to an empty photo." << endl;
            return Mat{};
        }

        double w = INPUT.cols;
        double h = INPUT.rows;
        double cx = w / 2.0;
        double cy = h / 2.0;

        // Construct the affine shear matrix using a standard 2D array to avoid comma-initializer parsing issues
        double shearData[2][3] = {
            {1.0,    Shear_X, -Shear_X * cy},
            {Shear_Y, 1.0,    -Shear_Y * cx}
        };
        cv::Mat Warp_Mat(2, 3, CV_64F, shearData);

        // Calculate the new bounding box of the four Corners to prevent clipping
        std::vector<cv::Point2f> Corners = {
            cv::Point2f(0, 0),  
            cv::Point2f(w, 0),
            cv::Point2f(w, h),
            cv::Point2f(0, h)
        };

        std::vector<cv::Point2f> transformedCorners(4);
        for (int i = 0; i < 4; ++i) {
            double x = Corners[i].x;
            double y = Corners[i].y;
            transformedCorners[i].x = static_cast<float>(Warp_Mat.at<double>(0, 0) * x + Warp_Mat.at<double>(0, 1) * y + Warp_Mat.at<double>(0, 2));
            transformedCorners[i].y = static_cast<float>(Warp_Mat.at<double>(1, 0) * x + Warp_Mat.at<double>(1, 1) * y + Warp_Mat.at<double>(1, 2));
        }

        // Find bounding rect of the transformed shape
        cv::Rect2f bbox = cv::boundingRect(transformedCorners);

        // Adjust the transformation matrix translation to fit inside the new canvas bounds
        Warp_Mat.at<double>(0, 2) += -bbox.x;
        Warp_Mat.at<double>(1, 2) += -bbox.y;

        Mat output;
        cv::warpAffine(
            INPUT, 
            output, 
            Warp_Mat, 
            cv::Size(static_cast<int>(bbox.width), static_cast<int>(bbox.height)), 
            cv::INTER_LINEAR, 
            cv::BORDER_CONSTANT, 
            Fill_Color
        );

        return output;
    }
};