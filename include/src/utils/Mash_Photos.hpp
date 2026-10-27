#pragma once
#include <filesystem>
#include <string>
#include <vector>

#ifndef MASH_PHOTOS
#define MASH_PHOTOS
namespace utils{
    namespace mash_photos{
        enum Setting {
            CONSTANT_PATH,
            VARIABLE_PATH
        };
    }
    int Mash_Photos(std::vector<std::filesystem::path>& In_Photo_Paths, const std::string OUT_PHOTOS_PATH, 
                    const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, 
                    const int PHOTOS_VERTICAL, const mash_photos::Setting SET_MODE);
    int Mash_Photos_Save_Valid_Photo_Paths(const std::vector<std::filesystem::path> IN_PHOTO_PATHS, 
                    std::vector<std::vector<std::filesystem::path>>& Valid_Photo_Paths, const std::string OUT_PHOTOS_PATH, 
                    const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, 
                    const int PHOTOS_VERTICAL, const mash_photos::Setting SET_MODE);
};
#endif