#include "../../include/libs/core.hpp"
#include <vector>
#include <iostream>

#include "../../include/src/utils/Grid_Crop.hpp"

using std::cout;
using std::endl;
using cv::Mat;

namespace utils{
/**
     * Cuts an Image into overlapping grid Tiles of a fixed size.
     * 
     * @param INPUT Source Image
     * @param Tile_Width Width of each tile in pixels
     * @param Tile_Height Height of each tile in pixels
     * @param Overlap_X Number of overlapping pixels horizontally
     * @param Overlap_Y Number of overlapping pixels vertically
     * @return Vector of Tile structures
     */
    static std::vector<grid_crop::Tile> Crop_To_Grid(const Mat& INPUT, int Tile_Width, int Tile_Height, int Overlap_X, int Overlap_Y) {
        std::vector<grid_crop::Tile> Tiles;

        if (INPUT.empty() || Tile_Width <= 0 || Tile_Height <= 0) {
            cout << "Error: Invalid INPUT Image or tile dimensions!" << endl;
            return Tiles;
        }

        int Step_X = Tile_Width - Overlap_X;
        int Step_Y = Tile_Height - Overlap_Y;

        if (Step_X <= 0 || Step_Y <= 0) {
            cout << "Error: Overlap must be strictly smaller than the tile dimensions!" << endl;
            return Tiles;
        }

        int Img_W = INPUT.cols;
        int Img_H = INPUT.rows;

        if (Img_W < Tile_Width || Img_H < Tile_Height) {
            cout << "Error: Image dimensions are smaller than the requested tile size!" << endl;
            return Tiles;
        }

        // Loop through rows with step stride
        for (int y = 0; y < Img_H; y += Step_Y) {
            int Current_Y = y;
            
            // Snap the last row to the bottom edge to maintain uniform tile size
            if (Current_Y + Tile_Height > Img_H) {
                Current_Y = Img_H - Tile_Height;
            }

            // Loop through columns with step stride
            for (int x = 0; x < Img_W; x += Step_X) {
                int Current_X = x;
                
                // Snap the last column to the right edge to maintain uniform tile size
                if (Current_X + Tile_Width > Img_W) {
                    Current_X = Img_W - Tile_Width;
                }

                // Extract the tile using cv::Rect (x, y, width, height)
                cv::Rect roi(Current_X, Current_Y, Tile_Width, Tile_Height);
                Tiles.push_back({INPUT(roi).clone(), Current_X, Current_Y});

                // Break out of column loop if we hit the right edge
                if (Current_X == Img_W - Tile_Width) {
                    break;
                }
            }

            // Break out of row loop if we hit the bottom edge
            if (Current_Y == Img_H - Tile_Height) {
                break;
            }
        }

        return Tiles;
    }
};