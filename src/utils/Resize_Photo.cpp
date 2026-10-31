#include "libs/opencv.hpp"
#include<iostream>
#include <algorithm>

using cv::Mat;
using std::cout;
using std::endl;
using std::min;

cv::Mat utils::resize_photo::Resize_Photo_No_Border(const cv::Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, 
                                                    const int RESOLUTIONS_VERTICAL);

namespace utils{
    cv::Mat Resize_Photo(const cv::Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL){
        if (Input_Photo.empty()) {
            cout << "\tEntered empty photo. Abort resizing." << endl; 
            return Mat{}; 
        }

        else if(RESOLUTIONS_HORIZONTAL <= 0){
            cout << "\tCannot resize a photo to horizontal resolution of " << RESOLUTIONS_HORIZONTAL << endl;
            return Mat{};
        }

        else if(RESOLUTIONS_VERTICAL <= 0){
            cout << "\tCannot resize a photo to vertical resolution of " << RESOLUTIONS_VERTICAL << endl;
            return Mat{};
        }

        int Current_Width = Input_Photo.cols;
        int Current_Height = Input_Photo.rows;

        double Scale_X = (double)RESOLUTIONS_HORIZONTAL / Current_Width;
        double Scale_Y = (double)RESOLUTIONS_VERTICAL / Current_Height;
        double Scale = min(Scale_X, Scale_Y);

        int New_Width = (int)(Current_Width * Scale);
        int New_Height = (int)(Current_Height * Scale);

        Mat Resized_Photo;
        cv::resize(Input_Photo, Resized_Photo, cv::Size(New_Width, New_Height), 0, 0, cv::INTER_AREA);

        int Top_Pad = (RESOLUTIONS_VERTICAL - New_Height) / 2;
        int Bottom_Pad = RESOLUTIONS_VERTICAL - New_Height - Top_Pad;
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

    namespace resize_photo{
        cv::Mat Resize_Photo_No_Border(const cv::Mat Input_Photo, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL){
            Mat Output;

            int Current_Width = Input_Photo.cols;
            int Current_Height = Input_Photo.rows;

            double Scale_X = (double)RESOLUTIONS_HORIZONTAL / Current_Width;
            double Scale_Y = (double)RESOLUTIONS_VERTICAL / Current_Height;
            double Scale = min(Scale_X, Scale_Y);

            int New_Width = (int)(Current_Width * Scale);
            int New_Height = (int)(Current_Height * Scale);


            // Remember to check

            cv::resize(Input_Photo, Output, cv::Size(New_Width, New_Height), 0, 0, cv::INTER_AREA);

            return Output;
        }
    }
};