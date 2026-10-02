#include "../../include/libs/core.hpp"
#include<iostream>

using cv::Mat;
using std::cout;
using std::endl;

Mat Resize_Photo(Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL) {
    if (Input_Photo.empty()) {
        cout << "Entered empty photo. Abort resizing." << endl; 

        return Input_Photo; 
    }

    int Current_Width = Input_Photo.cols;
    int Current_Height = Input_Photo.rows;

    double scale_x = (double)RESOLUTIONS_HORIZONTAL / Current_Width;
    double scale_y = (double)RESOLUTIONS_VERTICAL / Current_Height;

    int New_Width = (int)(Current_Width * scale);
    int New_Height = (int)(Current_Height * scale);

    Mat Resized_Photo;
    cv::resize(Input_Photo, Resized_Photo, cv::Size(New_Width, New_Height), 0, 0, cv::INTER_AREA);

    int Top_Pad = (RESOLUTIONS_VERTICAL - New_Height) / 2;
    int Bottom_Pad = RESOLUTIONS_VERTICAL - New_Height - ;
    int Left_Pad = (RESOLUTIONS_HORIZONTAL - New_Width) / 2;
    int Right_Pad = RESOLUTIONS_HORIZONTAL - New_Width - Left_Pad;

    Mat Final_Photo;
    cv::copyMakeBorder(
        Resized_Photo, 
        Final_Photo, 
        Top_Pad, 
        Bottom_Pad, 
        Left_Pad, 
        Right_Pad, 
        cv::BORDER_CONSTANT, 
        cv::Scalar(255, 255, 255)
    );

    return Final_Photo;
}