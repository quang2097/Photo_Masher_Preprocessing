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

namespace utils{
    cv::Mat Get_Photo(const std::string PATH){
        const Mat Photo = imread(PATH);

        if(Photo.empty()){
            cout << "Failed to input file \'" << PATH << "\'." << endl;
            return Mat{};
        }

        return Photo;
    }
};