#include<iostream>
#include<fstream>
#include <filesystem>
#include"convertPngToBin.h"
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