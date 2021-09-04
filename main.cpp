#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    // Make sure the commandline arguments are correct
    if (argc < 5)
    {
        std::cout << "Usage:\n\t./gray2binary input_grayscale_image_filename output_binary_image_filename threshold_value input_ground_truth_image" << std::endl;
        return 1;
    }
    std::string inpImagePath = argv[1];
    std::string outImagePath = argv[2];
    uint8_t threshold = std::stoi(argv[3]);
    std::string gtImagePath = argv[4];

    // Read the image
    cv::Mat image = cv::imread(inpImagePath, 0);
    cv::Mat gtImage = cv::imread(gtImagePath, 0);
    int H = image.size[0];
    int W = image.size[1];
    
    // Initialize an empty grayscale image (8-bit unsigned integer matrix with one channel)
    cv::Mat imageBinary(H, W, CV_8UC1);

    int TP = 0, TN = 0, FP = 0, FN = 0;

    // Loop through the pixels of the image
    for (int r = 0; r < H; r++)
    {
        for (int c = 0; c < W; c++)
        {
            // Retrieve the pixel from location (r, c)
            cv::uint8_t pix = image.at<cv::uint8_t>(r, c);
            // Apply formula to get the grayscale value and assign it to imageBinary
            uint8_t res = pix > threshold ? 255 : 0;
            TP += (gtImage.at<cv::uint8_t>(r, c) > 0) && (res > 0);
            TN += (gtImage.at<cv::uint8_t>(r, c) == 0) && (res == 0);
            FP += (gtImage.at<cv::uint8_t>(r, c) == 0) && (res > 0);
            FN += (gtImage.at<cv::uint8_t>(r, c) > 0) && (res == 0);
            imageBinary.at<uint8_t>(r, c) = res;
        }
    }
    
    // Show original and grayscale images
    cv::imshow("Image", image);
    cv::imshow("ImageBinary", imageBinary);
    
    // Save the image to the output location
    cv::imwrite(outImagePath, imageBinary);
    std::cout << "Statistics" << TP << std::endl;
    std::cout << "TP: " << TP << std::endl;
    std::cout << "TN: " << TN << std::endl;
    std::cout << "FP: " << FP << std::endl;
    std::cout << "FN: " << FN << std::endl;

    // Wait for keyboard input to close imshow windows
    cv::waitKey(0);
    return 0;
}
