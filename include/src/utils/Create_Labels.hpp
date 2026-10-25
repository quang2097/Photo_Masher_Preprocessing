#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

#ifndef CREATE_LABELS
#define CREATE_LABELS
namespace utils{
    namespace create_labels{
        enum Dataset_Format{
            COCO_JSON, YOLO26, YOLOv8
        };
    };

    int Create_Labels_Photo_Masher(const vector<vector<fs::path>>& VALID_LABEL_PATHS, const string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                                    const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL, const create_labels::Dataset_Format FORMAT);
};
#endif