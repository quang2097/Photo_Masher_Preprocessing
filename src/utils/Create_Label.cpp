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

std::vector<std::string> utils::mash_photo::Create_Label_YOLO26(const std::vector<std::vector<std::string>>& INPUT,
                                                                const std::vector<int> ORIGINAL_RESOLUTIONS,
                                                                const int RESOLUTIONS_HORIZONTAL, 
                                                                const int RESOLUTIONS_VERTICAL, 
                                                                const int PHOTOS_HORIZONTAL, 
                                                                const int PHOTOS_VERTICAL);

std::vector<std::string> utils::resize_photo::Create_Label_YOLO26(const std::vector<std::string> INPUT, 
                                                                    const create_label::Pair RESOLUTIONS_HORIZONTAL, 
                                                                    const create_label::Pair RESOLUTIONS_VERTICAL);

std::vector<std::string> utils::flip_photo::Create_Label_YOLO26(const std::vector<std::string> INPUT, 
                                                                    const create_label::Pair RESOLUTIONS_HORIZONTAL, 
                                                                    const create_label::Pair RESOLUTIONS_VERTICAL);

std::vector<std::string> utils::rotate_photo::Create_Label_YOLO26(const std::vector<std::string> INPUT, 
                                                                    const create_label::Pair RESOLUTIONS_HORIZONTAL, 
                                                                    const create_label::Pair RESOLUTIONS_VERTICAL);

namespace utils{
    // Create label function for preprocessing methods that require more than 1 photo {Mash_Photo}.
    std::vector<std::string> create_label(const std::vector<std::vector<std::string>>& INPUT,
                                            const std::vector<int> ORIGINAL_RESOLUTIONS,
                                            const int RESOLUTIONS_HORIZONTAL, 
                                            const int RESOLUTIONS_VERTICAL,
                                            const int PHOTOS_HORIZONTAL,
                                            const int PHOTOS_VERTICAL,
                                            const utils::create_label::Create_Label_Type TYPE){
        if(INPUT.empty()){
            cout << "\tCannot create label from an empty label input." << endl;
            return vector<string>{};
        }

        else if(RESOLUTIONS_HORIZONTAL <= 0){
            cout << "\tCannot create label because of an invalid horizontal resolution input." << endl;
            return vector<string>{};
        }

        else if(RESOLUTIONS_VERTICAL <= 0){
            cout << "\tCannot create label because of an invalid vertical resolution input." << endl;
            return vector<string>{};
        }

        vector<string> Output;

        switch(TYPE){
            default:{
                cout << "\tCannot create label because format is not yet supported." << endl;
                break;
            }

            case(create_label::YOLO26):{
                Output = mash_photo::Create_Label_YOLO26(INPUT, ORIGINAL_RESOLUTIONS, RESOLUTIONS_HORIZONTAL, RESOLUTIONS_VERTICAL, 
                                                        PHOTOS_HORIZONTAL, PHOTOS_VERTICAL);
                break;
            }
        }

        if(Output.empty()){
            cout << "\tFailed to mash lanbel." << endl;
            return vector<string>{};
        }

        return Output;
    }

    namespace mash_photo{
        std::vector<std::string> Create_Label_YOLO26(const std::vector<std::vector<std::string>>& INPUT,
                                                    const std::vector<int> ORIGINAL_RESOLUTIONS,
                                                    const int RESOLUTIONS_HORIZONTAL, 
                                                    const int RESOLUTIONS_VERTICAL, 
                                                    const int PHOTOS_HORIZONTAL, 
                                                    const int PHOTOS_VERTICAL){
            if(INPUT.empty()){
                cout << "\tCannot create label for mash photo preprocessing with empty label input." << endl;
                return vector<string>{};
            }

            const int NUMBER_OF_PHOTOS_PER_PHOTO = PHOTOS_HORIZONTAL*PHOTOS_VERTICAL;

            if(INPUT.size() < NUMBER_OF_PHOTOS_PER_PHOTO){
                cout << "\tCannot create label for mash photo preprocessing with an input size smaller than the total number of photos " << endl
                    << "\tdemanded please increase the input size to " << NUMBER_OF_PHOTOS_PER_PHOTO << " even if it is an empty string" << endl;
                return vector<string>{};
            }

            else if(PHOTOS_HORIZONTAL < RESOLUTIONS_HORIZONTAL){
                cout << "\tCannot create label for mash photo preprocessing because of invalid number of photos to resolution." << endl
                    << "\tSpecifically the number of horizontal photos are smaller than the horizontal resolution." << endl;
                return vector<string>{};
            }

            else if(PHOTOS_VERTICAL < RESOLUTIONS_VERTICAL){
                cout << "\tCannot create label for mash photo preprocessing because of invalid number of photos to resolution." << endl
                    << "\tSpecifically the number of vertical photos are smaller than the vertical resolution." << endl;
                return vector<string>{};
            }
                    
            for(int Index = 0;Index < INPUT.size();Index += 1){
                if(INPUT[Index].empty()){
                    continue;
                }

            }

            for(int Index = 0;Index < INPUT.size();Index += 1){
                int Grid_X = Index % PHOTOS_HORIZONTAL;
                int Grid_Y = Index / PHOTOS_HORIZONTAL;

                for(const vector<string>& LABEL : INPUT) for(const string& LINE : LABEL){
                    std::stringstream ss(LINE);
                    int Class_Id;
                    float X_Center, Y_Center, Width, Height;

                    if (ss >> Class_Id >> X_Center >> Y_Center >> Width >> Height){
                        float new_X_Center = (X_Center + Grid_X) / PHOTOS_HORIZONTAL;
                        float new_Y_Center = (Y_Center + Grid_Y) / PHOTOS_VERTICAL;
                        float new_Width = Width / PHOTOS_HORIZONTAL;
                        float new_Height = Height / PHOTOS_VERTICAL;

                        std::stringstream New_String_Stream;
                        New_String_Stream << Class_Id << " " << new_X_Center << " " << new_Y_Center << " " << 
                                            new_Width << " " << new_Height << "\n";
                    }
                }
            }
        }
    };

    namespace resize_photo{
        std::vector<std::string> Create_Label_YOLO26(const std::vector<string> INPUT, 
                                                    const utils::create_label::Pair RESOLUTIONS_HORIZONTAL, 
                                                    const utils::create_label::Pair RESOLUTIONS_VERTICAL){
            vector<string> Output;
            
            if (INPUT.empty()){
                cout << "\tInput label list is empty. Returning empty labels." << endl;
                return vector<string>{};
            }

            // Calculate scaling factors based on resolutions (new / old)
            double Scale_X = static_cast<double>(RESOLUTIONS_HORIZONTAL.second) / static_cast<double>(RESOLUTIONS_HORIZONTAL.first);
            double Scale_Y = static_cast<double>(RESOLUTIONS_VERTICAL.second) / static_cast<double>(RESOLUTIONS_VERTICAL.first);

            vector<string> Output;

            for (const string& LABEL_LINE : INPUT){
                std::stringstream ss(LABEL_LINE);
                int Class_Id;
                double x, y, Width, Height;

                // Assuming format: Class_Id x y Width Height (adjust if your format differs, e.g., x1 y1 x2 y2)
                if (ss >> Class_Id >> x >> y >> Width >> Height){
                    // Apply resolution scaling
                    double Final_X = x * Scale_X;
                    double Final_Y = y * Scale_Y;
                    double Final_Width = Width * Scale_X;
                    double Final_Height = Height * Scale_Y;

                    // Reconstruct the label line
                    std::stringstream New_String_Stream;
                    New_String_Stream << Class_Id << " " << Final_X << " " << Final_Y << " " << Final_Width << " " << Final_Height;
                    Output.push_back(New_String_Stream.str());
                } else{
                    // If the string format doesn't match standard numeric boxes, keep it as-is or log
                    Output.push_back(LABEL_LINE);
                }
            }

            return Output;
        }
    };

    namespace flip_photo{
        std::vector<std::string> Create_Label_YOLO26(const std::vector<string> INPUT, const create_label::Pair RESOLUTIONS_HORIZONTAL, 
                                                    const create_label::Pair RESOLUTIONS_VERTICAL){
            vector<string> Output;
            
            if (INPUT.empty()){
                cout << "\tInput label list is empty. Returning empty labels." << endl;
                return vector<string>{};
            }

            // Calculate scaling factors based on resolutions (new / old)
            double Scale_X = static_cast<double>(RESOLUTIONS_HORIZONTAL.second) / static_cast<double>(RESOLUTIONS_HORIZONTAL.first);
            double Scale_Y = static_cast<double>(RESOLUTIONS_VERTICAL.second) / static_cast<double>(RESOLUTIONS_VERTICAL.first);

            vector<string> Output;

            for (const string& LABEL_LINE : INPUT){
                std::stringstream ss(LABEL_LINE);
                int Class_Id;
                double x, y, Width, Height;

                // Assuming format: Class_Id x y Width Height (adjust if your format differs, e.g., x1 y1 x2 y2)
                if (ss >> Class_Id >> x >> y >> Width >> Height){
                    // Apply resolution scaling
                    double Final_X = x * Scale_X;
                    double Final_Y = y * Scale_Y;
                    double Final_Width = Width * Scale_X;
                    double Final_Height = Height * Scale_Y;

                    // Reconstruct the label line
                    std::stringstream New_String_Stream;
                    New_String_Stream << Class_Id << " " << Final_X << " " << Final_Y << " " << Final_Width << " " << Final_Height;
                    Output.push_back(New_String_Stream.str());
                } else{
                    // If the string format doesn't match standard numeric boxes, keep it as-is or log
                    Output.push_back(LABEL_LINE);
                }
            }

            return Output;
        }
    };

    namespace rotate_photo{
        std::vector<std::string> Create_Label_YOLO26(const std::vector<string> INPUT, const create_label::Pair RESOLUTIONS_HORIZONTAL, 
                                                    const create_label::Pair RESOLUTIONS_VERTICAL){
            vector<string> Output;
            
            if (INPUT.empty()){
                cout << "\tInput label list is empty. Returning empty labels." << endl;
                return vector<string>{};
            }

            // Calculate scaling factors based on resolutions (new / old)
            double Scale_X = static_cast<double>(RESOLUTIONS_HORIZONTAL.second) / static_cast<double>(RESOLUTIONS_HORIZONTAL.first);
            double Scale_Y = static_cast<double>(RESOLUTIONS_VERTICAL.second) / static_cast<double>(RESOLUTIONS_VERTICAL.first);

            vector<string> Output;

            for (const string& LABEL_LINE : INPUT){
                std::stringstream ss(LABEL_LINE);
                int Class_Id;
                double x, y, Width, Height;

                // Assuming format: Class_Id x y Width Height (adjust if your format differs, e.g., x1 y1 x2 y2)
                if(ss >> Class_Id >> x >> y >> Width >> Height){
                    // Apply resolution scaling
                    double Final_X = x * Scale_X;
                    double Final_Y = y * Scale_Y;
                    double Final_Width = Width * Scale_X;
                    double Final_Height = Height * Scale_Y;

                    // Reconstruct the label line
                    std::stringstream New_String_Stream;
                    New_String_Stream << Class_Id << " " << Final_X << " " << Final_Y << " " << Final_Width << " " << Final_Height;
                    Output.push_back(New_String_Stream.str());
                }

                else{
                    // If the string format doesn't match standard numeric boxes, keep it as-is or log
                    Output.push_back(LABEL_LINE);
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
//         cout << "\tCreating labels." << endl;

//         if(VALID_LABEL_PATHS.empty() || VALID_LABEL_PATHS.front().empty()){
//             cout << "\tNo valid label paths were provided." << endl;
//             return 1;
//         }
                    
//         for(int Row = 0; Row < VALID_LABEL_PATHS.size(); Row += 1){
            
//             // Derive a new filename based on the first valid photo in this mash row
//             string Base_Name = "Mashed_Labels_" + std::to_string(Row);
//             for (int Column = 0;Column < VALID_LABEL_PATHS[Row].size();Column += 1){
//                 if (!VALID_LABEL_PATHS[Row][Column].empty()){
//                     Base_Name = "Mashed_" + std::to_string(Row + 1);
//                     break;
//                 }
//             }

//             fs::path Out_Filepath = fs::path(OUT_LABELS_PATH) / (Base_Name + ".txt");
//             std::ofstream outfile(Out_Filepath);

//             if(!outfile.is_open()){
//                 cout << "\tFailed to create label output for row " << Row << endl;
//                 continue;
//             }

//             for(int Column = 0; Column < VALID_LABEL_PATHS[Row].size(); Column += 1){
//                 if(VALID_LABEL_PATHS[Row][Column].empty()){
//                     continue;
//                 }

//                 // Read the label text file corresponding to the current sub-image
//                 vector<string> Label = Read_Txt_File(VALID_LABEL_PATHS[Row][Column].string(), read_txt_file::Read_Txt_File_Mode::LABEL_TXT);

//                 // Determine X and Y placement in the grid based on the 1D index (Column)
//                 int Grid_X = Column % PHOTOS_HORIZONTAL;
//                 int Grid_Y = Column / PHOTOS_HORIZONTAL;

//                 // Parse each line, scale, and save
//                 for (const string& line : Label){
//                     std::stringstream ss(line);
//                     int Class_Id;
//                     float X_Center, Y_Center, Width, Height;

//                     if (ss >> Class_Id >> X_Center >> Y_Center >> Width >> Height){
//                         float new_X_Center = (X_Center + Grid_X) / PHOTOS_HORIZONTAL;
//                         float new_Y_Center = (Y_Center + Grid_Y) / PHOTOS_VERTICAL;
//                         float new_Width = Width / PHOTOS_HORIZONTAL;
//                         float new_Height = Height / PHOTOS_VERTICAL;

//                         outfile << Class_Id << " " << new_X_Center << " " << new_Y_Center << " " 
//                                 << new_Width << " " << new_Height << "\n";
//                     }
//                 }
//             }
            
//             outfile.close();
//         }
        
//         return 0;
//     }
// };