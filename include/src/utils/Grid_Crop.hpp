#include "../../libs/core.hpp"

using cv::Mat;

#ifndef GRID_CROP
#define GRID_CROP
namespace utils{
    namespace grid_crop{
        struct Tile{
            Mat Image;
            int x;
            int y;
        };
    };
    static std::vector<grid_crop::Tile> Crop_To_Grid(const Mat& INPUT, const int TILE_WIDTH, const int TILE_HEIGHT, const int OVERLAP_X, int OVERLAP_Y);
};
#endif