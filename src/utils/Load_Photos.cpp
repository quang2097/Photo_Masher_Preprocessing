#include "../../include/libs/core.hpp"
#include <iostream>
#include <string>
#include <vector>

using cv::Mat;
using cv::imread;
using std::string;
using std::vector;
using std::cout;
using std::endl;

Mat Get_Photo(const string PATH){
    Mat Photo;
    Photo = imread(PATH);

    if(Photo.empty()){
        cout << "Failed to input file \'" << PATH << "\'." << endl;
        return {};
    }

    return Photo;
}

// vector<Mat> Load_Photos(const int NUMBER_OF_PHOTOS){
//     vector<Mat> Photos;

//     return Photos;
// }

// vector<Mat> Load_Photos(const int NUMBER_OF_PHOTOS, const string PHOTO_DIRECTORY_PATH){
//     vector<Mat> Photos;

//     return Photos;
// }