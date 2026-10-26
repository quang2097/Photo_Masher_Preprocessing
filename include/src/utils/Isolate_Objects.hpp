#pragma once
#include "../../libs/core.hpp" 
#include <vector>
#include <string>

#ifndef ISOLATE_OBJECTS
#define ISOLATE_OBJECTS
namespace utils{
    cv::Mat Isolate_YOLO_Objects(const cv::Mat INPUT_PHOTO, const std::vector<std::string>& YOLO26_LABELS);
};
#endif