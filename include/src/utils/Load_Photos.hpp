#include "../../libs/core.hpp"
#include <string>

#ifndef LOAD_PHOTOS
#define LOAD_PHOTOS
namespace utils{
    cv::Mat Get_Photo(const std::string PATH);
};
#endif