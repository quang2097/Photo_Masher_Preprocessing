#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../include/src/utils/Read_Txt_File.hpp"

#include "../../include/src/utils/Create_Labels.hpp";

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace utils{
    int Create_Labels_Photo_Masher(const std::vector<std::vector<std::filesystem::path>>& VALID_LABEL_PATHS, 
                                    const std::string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                                    const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL,
                                    const int PHOTOS_VERTICAL, const create_labels::Dataset_Format FORMAT){
        int Check = 0;
        // Backwards and forwards compatibility.
        if(FORMAT == create_labels::YOLO26){
            Check = Create_Labels_YOLO26(VALID_LABEL_PATHS, OUT_LABELS_PATH, RESOLUTIONS_HORIZONTAL, 
                                       RESOLUTIONS_VERTICAL, PHOTOS_HORIZONTAL, PHOTOS_VERTICAL);
        }
        else if(FORMAT == create_labels::YOLOv8){
            Check = Create_Labels_YOLOv8();
        }
        else if(FORMAT == create_labels::COCO_JSON){
            Check = Create_Labels_COCO_JSON();
        }

        if(Check == 1){
            cout << "Creating labels for photo masher failed." << endl;
            return 1;
        }

        return 0;
    }

    int Create_Labels_YOLO26(const std::vector<std::vector<std::filesystem::path>>& VALID_LABEL_PATHS, 
                            const std::string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
                            const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
        cout << "Creating labels." << endl;

        if(VALID_LABEL_PATHS.empty() || VALID_LABEL_PATHS.front().empty()){
            cout << "No valid label paths were provided." << endl;
            return 1;
        }
                    
        for(int Row = 0; Row < VALID_LABEL_PATHS.size(); Row += 1){
            
            // Derive a new filename based on the first valid photo in this mash row
            string Base_Name = "Mashed_Labels_" + std::to_string(Row);
            for (int Column = 0;Column < VALID_LABEL_PATHS[Row].size();Column += 1) {
                if (!VALID_LABEL_PATHS[Row][Column].empty()) {
                    Base_Name = "Mashed_" + std::to_string(Row + 1);
                    break;
                }
            }

            fs::path Out_Filepath = fs::path(OUT_LABELS_PATH) / (Base_Name + ".txt");
            std::ofstream outfile(Out_Filepath);

            if(!outfile.is_open()){
                cout << "Failed to create label output for row " << Row << endl;
                continue;
            }

            for(int Column = 0; Column < VALID_LABEL_PATHS[Row].size(); Column += 1){
                if(VALID_LABEL_PATHS[Row][Column].empty()){
                    continue;
                }

                // Read the label text file corresponding to the current sub-image
                vector<string> Label = Read_Txt_File(VALID_LABEL_PATHS[Row][Column].string(), read_txt_file::Read_Txt_File_Mode::LABEL_TXT);

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

    int Create_Labels_COCO_JSON(){
        return 0;
    }

    int Create_Labels_YOLOv8(){
        return 0;
    }
};