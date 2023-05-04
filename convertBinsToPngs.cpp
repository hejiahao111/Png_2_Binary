#include <iostream>
#include <fstream>
#include <filesystem>
#include<string>
#include "stb_image.h"
#include "stb_image_write.h"
#include"convertBinsToPngs.h"
namespace fs = std::filesystem;

void convertBinsToPngs(const std::string& sourceFolderPath, const std::string& destinationFolderPath)
{
    // Create the destination folder if it doesn't exist
    if (!fs::exists(destinationFolderPath)) {
        fs::create_directory(destinationFolderPath);
    }

    // Loop through the source folder and convert each bin file to png
    for (const auto& file : fs::directory_iterator(sourceFolderPath)) {
        if (fs::is_regular_file(file) && file.path().extension() == ".bin") {
            std::ifstream inFile(file.path(), std::ios::binary);
            if (!inFile) {
                std::cerr << "Failed to open file: " << file.path() << std::endl;
                continue;
            }

            // Determine the dimensions of the image from the size of the file
            inFile.seekg(0, std::ios::end);
            const auto fileSize = inFile.tellg();
            inFile.seekg(0, std::ios::beg);
            const auto imageSize = static_cast<int>(std::sqrt(fileSize / 3));

            // Read the binary data from the file into memory
            auto imageData = new unsigned char[imageSize * imageSize * 3];
            inFile.read(reinterpret_cast<char*>(imageData), imageSize * imageSize * 3);

            // Convert the binary data to an image
             
            auto image = stbi_write_png(destinationFolderPath.c_str()+ "/" + file.path().stem().string() + ".png", imageSize, imageSize, 3, imageData, 0);
            if (!image) {
                std::cerr << "Failed to write image: " << file.path() << std::endl;
            }

            // Clean up the memory
            delete[] imageData;

            std::cout << "Converted file: " << file.path() << std::endl;
        }
    }
}

