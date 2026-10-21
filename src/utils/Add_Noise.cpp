#include "../../include/libs/core.hpp"
#include <random>

using cv::Mat;

class Noise_Preprocessor {
public:
    enum Noise_Type {
        SALT_AND_PEPPER,
        GAUSSIAN
    };

    /**
     * Adds Noise to an image based on a given PERCENTAGE.
     * 
     * @param input Image to be processed (Modified in-place or returned as new)
     * @param TYPE NoiseTYPE (SALT_AND_PEPPER or GAUSSIAN)
     * @param PERCENTAGE For Salt-and-Pepper: PERCENTAGE of Pixels affected (0.0 to 100.0).
     *                   For Gaussian: intensity PERCENTAGE relative to max Pixel value 255 (0.0 to 100.0).
     * @return Processed Mat
     */
    static Mat applyNoise(const Mat& INPUT, const Noise_Type TYPE, const double PERCENTAGE) {
        Mat Output;
        INPUT.copyTo(Output);

        if (PERCENTAGE <= 0.0) return Output;

        if (TYPE == SALT_AND_PEPPER) {
            Add_Salt_And_Pepper(Output, PERCENTAGE);
        } else if (TYPE == GAUSSIAN) {
            Add_Gaussian(Output, PERCENTAGE);
        }

        return Output;
    }

private:
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