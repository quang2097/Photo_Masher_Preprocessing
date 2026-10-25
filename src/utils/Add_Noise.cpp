#include "../../include/libs/core.hpp"
#include <random>
#include <iostream>

using std::cout;
using std::endl;
using cv::Mat;

namespace utils{
    namespace noise_preprocessor{
        enum Noise_Type{
            SALT_AND_PEPPER, GAUSSIAN
        };
    };

    /**
     * Adds Noise to an image based on a given PERCENTAGE.
     * 
     * @param INPUT Image to be processed (Modified in-place or returned as new)
     * @param TYPE NoiseTYPE (SALT_AND_PEPPER or GAUSSIAN)
     * @param PERCENTAGE For Salt-and-Pepper: PERCENTAGE of Pixels affected (0.0 to 100.0).
     *                   For Gaussian: intensity PERCENTAGE relative to max Pixel value 255 (0.0 to 100.0).
     * @return Processed Mat
     */
    static Mat Add_Noise(const Mat& INPUT, const noise_preprocessor::Noise_Type TYPE, const double PERCENTAGE){
        if(PERCENTAGE <= 0){
            cout << "Add noise percentage was set to 0%. Failed to process photo." << endl;
            return Mat{};
        }

        // Check for empty images.
        if(INPUT.empty()){
            cout << "Error: Could not add noise to empty image file." <<  endl;
            return Mat{};
        }

        Mat Output;
        INPUT.copyTo(Output);

        if (PERCENTAGE <= 0.0) return Output;

        if (TYPE == noise_preprocessor::SALT_AND_PEPPER) {
            Add_Salt_And_Pepper(Output, PERCENTAGE);
        } else if (TYPE == noise_preprocessor::GAUSSIAN) {
            Add_Gaussian(Output, PERCENTAGE);
        }

        return Output;
    }

// Private functions not included in Add_Noise.hpp file.
    static void Add_Salt_And_Pepper(Mat& Img, const double PERCENTAGE) {
        int Total_Pixels = Img.rows * Img.cols;
        int Num_Pixels = static_cast<int>(Total_Pixels * (PERCENTAGE / 100.0));

        // Random number Generators for cooRdinates
        std::random_device Rd;
        std::mt19937 Gen(Rd());
        std::uniform_int_distribution<> Dis_Row(0, Img.rows - 1);
        std::uniform_int_distribution<> Dis_Col(0, Img.cols - 1);
        std::uniform_int_distribution<> Dis_Val(0, 1);

        for (int i = 0; i < Num_Pixels; ++i) {
            int r = Dis_Row(Gen);
            int c = Dis_Col(Gen);
            uchar Noise_Val = (Dis_Val(Gen) == 0) ? 0 : 255;

            if (Img.channels() == 1) {
                Img.at<uchar>(r, c) = Noise_Val;
            } else if (Img.channels() == 3) {
                cv::Vec3b& Pixel = Img.at<cv::Vec3b>(r, c);
                Pixel[0] = Noise_Val;
                Pixel[1] = Noise_Val;
                Pixel[2] = Noise_Val;
            }
        }
    }

    static void Add_Gaussian(Mat& Img, const double PERCENTAGE) {
        // StandaRd deviation proportional to the PERCENTAGE of max Pixel range (255)
        double Sigma = (PERCENTAGE / 100.0) * 255.0;

        Mat Noise(Img.size(), Img.type());
        cv::randn(Noise, 0.0, Sigma);

        // cv::add automatically handles saturation (clamping to 0-255 for 8-bit images)
        cv::add(Img, Noise, Img, cv::noArray(), Img.type());
    }
};