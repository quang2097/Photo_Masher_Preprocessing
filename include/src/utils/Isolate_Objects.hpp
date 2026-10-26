#include "../../libs/core.hpp" 
#include <vector>
#include <string>

using std::string;
using std::vector;
using cv::Mat;

#ifndef ISOLATE_OBJECTS
#define ISOLATE_OBJECTS
namespace utils{
    Mat Isolate_YOLO_Objects(const Mat INPUT_PHOTO, const vector<string>& YOLO26_LABELS);
};
#endif