#include "../../include/libs/core.hpp"
#include <iostream>
#include "../../include/src/utils/Gaussian_Blur.hpp"

#include "../../include/src/utils/Grayscale.hpp"

using cv::Mat;
using std::cout;
using std::endl;

namespace utils{
    Mat Grayscale(const Mat IMAGE) {
        // Check for empty images.
        if (IMAGE.empty()) {
            cout << "Error: Could not apply grayscale preprocessing to empty image file." <<  endl;
            return Mat{};
        }

        // Convert the image to grayscale.
        cv::Mat Grayed_Image;
        cv::cvtColor(IMAGE, Grayed_Image, cv::COLOR_BGR2GRAY);

        cout << "Applied grayscale preprocessing to image file." << endl;

        return Grayed_Image;
    }

    Mat Grayscale_With_Gaussian(const Mat IMAGE, int Size1 = 3, int Size2 = 3, int Sigma_X = 0, int Sigma_Y = 0, const grayscale::Grayscale_Setting SETTING) {
        // Check for empty images.
        if (IMAGE.empty()) {
            cout << "Error: Could not apply grayscale preprocessing to empty image file." <<  endl;
            return Mat{};
        }

        // Convert the image to grayscale.
        cv::Mat Grayed_Image;
        cv::cvtColor(IMAGE, Grayed_Image, cv::COLOR_BGR2GRAY);

        cout << "Applied grayscale preprocessing to image file." << endl;

        if(SETTING == grayscale::GAUSSIAN_DEFAULT){
            Grayed_Image = Apply_Gaussian_Blur(Grayed_Image);
        }
        else if(SETTING == grayscale::GAUSSIAN_CUSTOM){
            Grayed_Image = Apply_Gaussian_Blur(Grayed_Image, Size1, Size2, Sigma_X, Sigma_Y);
        }

        cout << "Applied grayscale preprocessing to image file." << endl;

        return Grayed_Image;
    }
};