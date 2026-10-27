#include "libs/opencv.hpp"
#include <vector>
#include <iostream>

#include "utils/Grid_Crop.hpp"

using std::cout;
using std::endl;
using cv::Mat;

namespace utils{
/**
     * Cuts an Image into overlapping grid Tiles of a fixed size.
     * 
     * @param INPUT Source Image
     * @param TILE_WIDTH Width of each tile in pixels
     * @param TILE_HEIGHT Height of each tile in pixels
     * @param OVERLAP_X Number of overlapping pixels horizontally
     * @param OVERLAP_Y Number of overlapping pixels vertically
     * @return Vector of Tile structures
     */
    static std::vector<grid_crop::Tile> Crop_To_Grid(const cv::Mat& INPUT, const int TILE_WIDTH, const int TILE_HEIGHT, 
                                                    const int OVERLAP_X, int OVERLAP_Y){
        std::vector<grid_crop::Tile> Tiles;

        if (INPUT.empty() || TILE_WIDTH <= 0 || TILE_HEIGHT <= 0){
            cout << "Error: Invalid INPUT Image or tile dimensions!" << endl;
            return Tiles;
        }

        int Step_X = TILE_WIDTH - OVERLAP_X;
        int Step_Y = TILE_HEIGHT - OVERLAP_Y;

        if (Step_X <= 0 || Step_Y <= 0){
            cout << "Error: Overlap must be strictly smaller than the tile dimensions!" << endl;
            return Tiles;
        }

        int Img_W = INPUT.cols;
        int Img_H = INPUT.rows;

        if (Img_W < TILE_WIDTH || Img_H < TILE_HEIGHT){
            cout << "Error: Image dimensions are smaller than the requested tile size!" << endl;
            return Tiles;
        }

        // Loop through rows with step stride
        for (int y = 0; y < Img_H; y += Step_Y){
            int Current_Y = y;
            
            // Snap the last row to the bottom edge to maintain uniform tile size
            if (Current_Y + TILE_HEIGHT > Img_H){
                Current_Y = Img_H - TILE_HEIGHT;
            }

            // Loop through columns with step stride
            for (int x = 0; x < Img_W; x += Step_X){
                int Current_X = x;
                
                // Snap the last column to the right edge to maintain uniform tile size
                if (Current_X + TILE_WIDTH > Img_W){
                    Current_X = Img_W - TILE_WIDTH;
                }

                // Extract the tile using cv::Rect (x, y, width, height)
                cv::Rect roi(Current_X, Current_Y, TILE_WIDTH, TILE_HEIGHT);
                Tiles.push_back({INPUT(roi).clone(), Current_X, Current_Y});

                // Break out of column loop if we hit the right edge
                if (Current_X == Img_W - TILE_WIDTH){
                    break;
                }
            }

            // Break out of row loop if we hit the bottom edge
            if (Current_Y == Img_H - TILE_HEIGHT){
                break;
            }
        }

        return Tiles;
    }
};