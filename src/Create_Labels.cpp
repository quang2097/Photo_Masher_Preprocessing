#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../src/utils/Read_Txt_File.hpp"

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::cout;
using std::endl;

int Create_Labels(const vector<vector<fs::path>>& VALID_LABEL_PATHS, const string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
    cout << "Creating labels." << endl;

    if(VALID_LABEL_PATHS.empty() || VALID_LABEL_PATHS.front().empty()){
        cout << "No valid label paths were provided." << endl;
        return 1;
    }
                
    for(int Row = 0; Row < VALID_LABEL_PATHS.size(); Row += 1){
        
        // Derive a new filename based on the first valid photo in this mash row
        string base_name = "Mashed_Labels_" + std::to_string(Row);
        for (const auto& path : VALID_LABEL_PATHS[Row]) {
            if (!path.empty()) {
                base_name = "Mashed_" + path.stem().string();
                break;
            }
        }

        fs::path out_filepath = fs::path(OUT_LABELS_PATH) / (base_name + ".txt");
        std::ofstream outfile(out_filepath);

        if(!outfile.is_open()){
            cout << "Failed to create label output for row " << Row << endl;
            continue;
        }

        for(int Column = 0; Column < VALID_LABEL_PATHS[Row].size(); Column += 1){
            if(VALID_LABEL_PATHS[Row][Column].empty()){
                continue;
            }

            // Read the label text file corresponding to the current sub-image
            vector<string> Label = Read_Txt_File(VALID_LABEL_PATHS[Row][Column].string(), LABEL_TXT);

            // Determine X and Y placement in the grid based on the 1D index (Column)
            int grid_x = Column % PHOTOS_HORIZONTAL;
            int grid_y = Column / PHOTOS_HORIZONTAL;

            // Parse each line, scale, and save
            for (const string& line : Label) {
                std::stringstream ss(line);
                int class_id;
                float x_center, y_center, width, height;

                if (ss >> class_id >> x_center >> y_center >> width >> height) {
                    float new_x_center = (x_center + grid_x) / PHOTOS_HORIZONTAL;
                    float new_y_center = (y_center + grid_y) / PHOTOS_VERTICAL;
                    float new_width = width / PHOTOS_HORIZONTAL;
                    float new_height = height / PHOTOS_VERTICAL;

                    outfile << class_id << " " << new_x_center << " " << new_y_center << " " 
                            << new_width << " " << new_height << "\n";
                }
            }
        }
        
        outfile.close();
    }
    
    return 0;
}