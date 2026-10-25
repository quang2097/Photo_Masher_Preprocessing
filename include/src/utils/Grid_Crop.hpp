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
    static std::vector<grid_crop::Tile> Crop_To_Grid(const Mat& INPUT, int Tile_Width, int Tile_Height, int Overlap_X, int Overlap_Y);
};
#endif