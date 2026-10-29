#include "libs/opencv.hpp" 
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using cv::Mat;
using cv::Rect;
using std::vector;
using std::string;

namespace utils{
    cv::Mat Isolate_YOLO_Objects(const cv::Mat INPUT_PHOTO, const std::vector<std::string>& YOLO26_LABELS) {
        if (INPUT_PHOTO.empty()) {
            cout << "Found no objects for this photo. Continuing." << endl;
            return INPUT_PHOTO;
        }

        // 1. Create a solid white canvas of the exact same size and type as the input
        Mat Final_Photo(INPUT_PHOTO.size(), INPUT_PHOTO.type(), cv::Scalar(255, 255, 255));

        int Image_Width = INPUT_PHOTO.cols;
        int Image_Height = INPUT_PHOTO.rows;

        // 2. Iterate through each Line in the YOLO label file
        for (const string& Line : YOLO26_LABELS) {
            if (Line.empty()){
                continue;
            }

            std::stringstream ss(Line);
            int Class_Id;
            float X_Center, Y_Center, Width, Height;

            // YOLO format: <Class_Id> <X_Center> <Y_Center> <Width> <Height>
            if (ss >> Class_Id >> X_Center >> Y_Center >> Width >> Height) {
                
                // 3. Convert normalized YOLO floats (0.0 to 1.0) into absolute pixel coordinates
                int Pixel_Width = static_cast<int>(Width * Image_Width);
                int Pixel_Height = static_cast<int>(Height * Image_Height);
                
                // Calculate top-left corner from the center coordinates
                int Pixel_X = static_cast<int>((X_Center * Image_Width) - (Pixel_Width / 2.0f));
                int Pixel_Y = static_cast<int>((Y_Center * Image_Height) - (Pixel_Height / 2.0f));

                // 4. Create the OpenCV Rectangle
                Rect Bbox(Pixel_X, Pixel_Y, Pixel_Width, Pixel_Height);

                // 5. Safety check: intersect with image boundaries to prevent out-of-bounds crashes
                Rect Image_Bounds(0, 0, Image_Width, Image_Height);
                Rect Safe_Bbox = Bbox & Image_Bounds;

                // 6. Copy ONLY the pixels inside this bounding box from the original to the white canvas
                if (Safe_Bbox.area() > 0) {
                    INPUT_PHOTO(Safe_Bbox).copyTo(Final_Photo(Safe_Bbox));
                }
            }
        }

        return Final_Photo;
    }
};