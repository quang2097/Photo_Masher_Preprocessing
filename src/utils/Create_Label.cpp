#include <string>
#include <filesystem>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "utils/Read_Txt_File.hpp"

#include "utils/create_label.hpp"

namespace fs = std::filesystem;
using std::string;
using std::vector;
using std::cout;
using std::endl;

std::vector<std::string> utils::resize_photo::Create_Label_YOLO26(const std::vector<string> INPUT, 
                                                                    const create_label::pair RESOLUTIONS_HORIZONTAL, 
                                                                    const create_label::pair RESOLUTIONS_VERTICAL);

namespace utils{
    namespace resize_photo{
        std::vector<std::string> create_label(const std::vector<std::string> INPUT, 
                                                const create_label::pair RESOLUTIONS_HORIZONTAL, 
                                                const create_label::pair RESOLUTIONS_VERTICAL,
                                                const create_label::Dataset_Format FORMAT){
            if(INPUT.empty()){
                cout << "Cannot create label from an empty label input." << endl;
                return vector<string>{};
            }

            else if(RESOLUTIONS_HORIZONTAL.first <= 0 || RESOLUTIONS_HORIZONTAL.second <= 0){
                cout << "Cannot create label because of an invalid horizontal resolution input." << endl;
                return vector<string>{};
            }

            else if(RESOLUTIONS_VERTICAL.first <= 0 || RESOLUTIONS_VERTICAL.second <= 0){
                cout << "Cannot create label because of an invalid vertical resolution input." << endl;
                return vector<string>{};
            }

            vector<string> Output;

            if(FORMAT == create_label::YOLO26){
                Output = Create_Label_YOLO26(INPUT, RESOLUTIONS_HORIZONTAL, RESOLUTIONS_VERTICAL);
            }

            if(Output.empty()){
                cout << "Failed to mash lanbel." << endl;
                return vector<string>{};
            }

            return Output;
        }

        std::vector<std::string> Create_Label_YOLO26(const std::vector<string> INPUT, const create_label::pair RESOLUTIONS_HORIZONTAL, 
                                                    const create_label::pair RESOLUTIONS_VERTICAL){
            vector<string> Output;
            
            if (INPUT.empty()) {
                cout << "Input label list is empty. Returning empty labels." << endl;
                return vector<string>{};
            }

            // Calculate scaling factors based on resolutions (new / old)
            double Scale_X = static_cast<double>(RESOLUTIONS_HORIZONTAL.second) / static_cast<double>(RESOLUTIONS_HORIZONTAL.first);
            double Scale_Y = static_cast<double>(RESOLUTIONS_VERTICAL.second) / static_cast<double>(RESOLUTIONS_VERTICAL.first);

            vector<string> Output;

            for (const string& Label_Line : INPUT) {
                std::stringstream ss(Label_Line);
                int Class_Id;
                double x, y, Width, Height;

                // Assuming format: class_id x y Width Height (adjust if your format differs, e.g., x1 y1 x2 y2)
                if (ss >> Class_Id >> x >> y >> Width >> Height) {
                    // Apply resolution scaling
                    double Final_X = x * Scale_X;
                    double Final_Y = y * Scale_Y;
                    double Final_Width = Width * Scale_X;
                    double Final_Height = Height * Scale_Y;

                    // Reconstruct the label line
                    std::stringstream New_String_Stream;
                    New_String_Stream << Class_Id << " " << Final_X << " " << Final_Y << " " << Final_Width << " " << Final_Height;
                    Output.push_back(New_String_Stream.str());
                } else {
                    // If the string format doesn't match standard numeric boxes, keep it as-is or log
                    Output.push_back(Label_Line);
                }
            }

            return Output;
        }
    };
};
//     namespace photo_masher{

//     };

//     int create_label_YOLO26(const std::vector<std::vector<std::filesystem::path>>& VALID_LABEL_PATHS, 
//                             const std::string OUT_LABELS_PATH, const int RESOLUTIONS_HORIZONTAL, 
//                             const int RESOLUTIONS_VERTICAL, const int PHOTOS_HORIZONTAL, const int PHOTOS_VERTICAL){
//         cout << "Creating labels." << endl;

//         if(VALID_LABEL_PATHS.empty() || VALID_LABEL_PATHS.front().empty()){
//             cout << "No valid label paths were provided." << endl;
//             return 1;
//         }
                    
//         for(int Row = 0; Row < VALID_LABEL_PATHS.size(); Row += 1){
            
//             // Derive a new filename based on the first valid photo in this mash row
//             string Base_Name = "Mashed_Labels_" + std::to_string(Row);
//             for (int Column = 0;Column < VALID_LABEL_PATHS[Row].size();Column += 1) {
//                 if (!VALID_LABEL_PATHS[Row][Column].empty()) {
//                     Base_Name = "Mashed_" + std::to_string(Row + 1);
//                     break;
//                 }
//             }

//             fs::path Out_Filepath = fs::path(OUT_LABELS_PATH) / (Base_Name + ".txt");
//             std::ofstream outfile(Out_Filepath);

//             if(!outfile.is_open()){
//                 cout << "Failed to create label output for row " << Row << endl;
//                 continue;
//             }

//             for(int Column = 0; Column < VALID_LABEL_PATHS[Row].size(); Column += 1){
//                 if(VALID_LABEL_PATHS[Row][Column].empty()){
//                     continue;
//                 }

//                 // Read the label text file corresponding to the current sub-image
//                 vector<string> Label = Read_Txt_File(VALID_LABEL_PATHS[Row][Column].string(), read_txt_file::Read_Txt_File_Mode::LABEL_TXT);

//                 // Determine X and Y placement in the grid based on the 1D index (Column)
//                 int grid_x = Column % PHOTOS_HORIZONTAL;
//                 int grid_y = Column / PHOTOS_HORIZONTAL;

//                 // Parse each line, scale, and save
//                 for (const string& line : Label) {
//                     std::stringstream ss(line);
//                     int class_id;
//                     float x_center, y_center, width, height;

//                     if (ss >> class_id >> x_center >> y_center >> width >> height) {
//                         float new_x_center = (x_center + grid_x) / PHOTOS_HORIZONTAL;
//                         float new_y_center = (y_center + grid_y) / PHOTOS_VERTICAL;
//                         float new_width = width / PHOTOS_HORIZONTAL;
//                         float new_height = height / PHOTOS_VERTICAL;

//                         outfile << class_id << " " << new_x_center << " " << new_y_center << " " 
//                                 << new_width << " " << new_height << "\n";
//                     }
//                 }
//             }
            
//             outfile.close();
//         }
        
//         return 0;
//     }
// };