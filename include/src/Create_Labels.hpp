#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

int Create_Labels(const vector<vector<fs::path>>& VALID_LABEL_PATHS, const string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL);