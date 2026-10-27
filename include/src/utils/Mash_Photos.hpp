#pragma once
#ifndef MASH_PHOTOS
#define MASH_PHOTOS
#include <filesystem>
#include <vector>
namespace utils{
    namespace mash_photos{
        enum Setting {
            CONSTANT_PATH,
            VARIABLE_PATH
        };
    }
    cv::Mat Mash_Photos(std::vector<cv::Mat> Inputs, const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL, 
                        const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL);
};
#endif