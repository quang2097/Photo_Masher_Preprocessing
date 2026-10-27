#pragma once
#ifndef ISOLATE_OBJECTS
#define ISOLATE_OBJECTS
#include "libs/opencv.hpp" 
#include <vector>
#include <string>
namespace utils{
    cv::Mat Isolate_YOLO_Objects(const cv::Mat INPUT_PHOTO, const std::vector<std::string>& YOLO26_LABELS);
};
#endif