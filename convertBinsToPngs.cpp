#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <fstream>
#include <iostream>
#include <string>

void convertBinToPng(const std::string& binFilePath, const std::string& pngFilePath) {
    std::ifstream inFile(binFilePath, std::ios::in | std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open bin file: " << binFilePath << std::endl;
        return;
    }

    // Determine the size of the file
    inFile.seekg(0, std::ios::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    // Allocate a buffer to hold the file data
    char* fileData = new char[fileSize];

    // Read the file data into the buffer
    inFile.read(fileData, fileSize);

    // Decode the image data from the buffer
    int width, height, channels;
    unsigned char* imageData = stbi_load_from_memory((stbi_uc*)fileData, fileSize, &width, &height, &channels, 0);

    // Write the image data to a PNG file
    stbi_write_png(pngFilePath.c_str(), width, height, channels, imageData, width * channels);

    // Free the allocated memory
    stbi_image_free(imageData);
    delete[] fileData;

    std::cout << "Successfully converted " << binFilePath << " to " << pngFilePath << std::endl;
}

int main() {
    convertBinToPng("image.bin", "image.png");
    return 0;
}
