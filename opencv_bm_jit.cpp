#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
template<int maskSize>
[[clang::jit]]
    void applyFilter(cv::Mat& image) {
    cv::Mat kernel = cv::Mat::ones(maskSize, maskSize, CV_32F) / (float)(maskSize * maskSize);
    cv::filter2D(image, image, -1, kernel);
}

int main(int argc, char** argv) {

    // Lire l'image à partir du fichier
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Could not read image file " << argv[1] << std::endl;
        return 1;
    }
    int maskSize = std::atoi(argv[2]);

    
    applyFilter(image, maskSize);

    cv::imshow("Filtered Image", image);
    cv::waitKey(0);

    return 0;
}
