#include "../libs/core.hpp"

using std::string;
using std::vector;

typedef enum{
    CONSTANT_PATH, VARIABLE_PATH
} Setting;

int Mash_Photos(vector<fs::path>& In_Photo_Paths, const string OUT_PHOTOS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const Setting SET_MODE);