#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

using std::string;
using std::vector;

enum Setting {
    CONSTANT_PATH,
    VARIABLE_PATH
};

#ifndef MASH_PHOTOS
#define MASH_PHOTOS
int Mash_Photos(vector<fs::path>& In_Photo_Paths, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const Setting SET_MODE);

int Mash_Photos_2(const vector<fs::path> IN_PHOTO_PATHS, vector<vector<fs::path>>& Valid_Photo_Paths, const string OUT_PHOTOS_PATH, 
                const int RESOLUTIONS_HORIZONTAL, const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, 
                const int PHOTOS_VERTICAL, const Setting SET_MODE);
#endif