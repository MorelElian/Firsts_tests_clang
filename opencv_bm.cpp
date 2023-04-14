#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>

void applyFilter(cv::Mat& image, int maskSize) {
    cv::Mat kernel = cv::Mat::ones(maskSize, maskSize, CV_32F) / (float)(maskSize * maskSize);
    cv::filter2D(image, image, -1, kernel);
}

int main(int argc, char** argv) {
    // Vérifier si l'utilisateur a fourni suffisamment d'arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <image_file> <mask_size>" << std::endl;
        return 1;
    }

    // Lire l'image à partir du fichier
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Could not read image file " << argv[1] << std::endl;
        return 1;
    }

    // Convertir la taille du masque à un entier
    int maskSize = std::atoi(argv[2]);

    // Appliquer le filtre à l'image
    applyFilter(image, maskSize);

    // Afficher l'image filtrée
    cv::imshow("Filtered Image", image);
    cv::waitKey(0);

    return 0;
}
