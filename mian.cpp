#include <iostream>
#include <fstream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
namespace fs = std::filesystem;
// 将PNG文件转换为BIN文件
bool convertPngToBin(const std::string& pngFilePath, const std::string& binFilePath)
{
    // 使用stb_image库加载PNG文件
    int width, height, numChannels;//宽度，长度，图片
    unsigned char* imageData = stbi_load(pngFilePath.c_str(), &width, &height, &numChannels, 0);
    if (!imageData) {
        std::cerr << "Failed to load image: " << pngFilePath << std::endl;
        return false;
    }

    // 计算图像数据的字节数
    int imageSize = width * height * numChannels;

    // 将图像数据写入BIN文件
    std::ofstream outFile(binFilePath, std::ios::out | std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to create binary file: " << binFilePath << std::endl;
        stbi_image_free(imageData);
        return false;
    }
    outFile.write(reinterpret_cast<char*>(imageData), imageSize);
    outFile.close();

    // 释放图像数据内存
    stbi_image_free(imageData);

    return true;
}

// 批量将PNG文件转换为BIN文件
void convertPngsToBins(const std::string& sourceFolderPath, const std::string& destinationFolderPath)
{
    // 确认源文件夹和目标文件夹都存在
    if (!std::filesystem::exists(sourceFolderPath)) {
        std::cerr << "Source folder does not exist: " << sourceFolderPath << std::endl;
        return;
    }
    if (!std::filesystem::exists(destinationFolderPath)) {
        std::cerr << "Destination folder does not exist: " << destinationFolderPath << std::endl;
        return;
    }

    // 遍历源文件夹中的PNG文件并转换为BIN文件
    for (auto& file : std::filesystem::directory_iterator(sourceFolderPath)) {
        if (file.path().extension() == ".png") {
            // 构建BIN文件路径
            std::filesystem::path binFilePath = std::filesystem::path(destinationFolderPath) /
                (file.path().stem().string() + ".bin");

            // 将PNG文件转换为BIN文件
            if (!convertPngToBin(file.path().string(), binFilePath.string())) {
                std::cerr << "Failed to convert PNG file: " << file.path().string() << std::endl;
            }
        }
    }
}

int main()
{
    std::string sourceFolderPath = "path/to/source/folder";
    std::string destinationFolderPath = "path/to/destination/folder";

    convertPngsToBins(sourceFolderPath, destinationFolderPath);

    return 0;
}
