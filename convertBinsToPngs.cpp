#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <filesystem>
#include<string>
#include<vector>
#include"convertBinsToPngs.h"
#include "stb_image_write.h"
#include"look_pict_channel.h"
namespace fs = std::filesystem;

void convertBinsToPngs(const std::string& sourceFolderPath, const std::string& destinationFolderPath)
{

    if (!fs::exists(destinationFolderPath)) {
        fs::create_directory(destinationFolderPath);//查看是否有目标文件夹
    }
    for (const auto& file : fs::directory_iterator(sourceFolderPath)) {
        if (fs::is_regular_file(file) && file.path().extension() == ".bin") {
            std::ifstream inFile(file.path(), std::ios::binary);
            if (!inFile) {
                std::cerr << "Failed to open file: " << file.path() << std::endl;
                continue;
            }
            const std::string file_name = file.path().c_str();
            int num_channels = look_pict_channel(file_name);


            inFile.seekg(0, std::ios::end);//将文件指针放到文件尾部
            const auto fileSize = inFile.tellg();//通过计算文件偏移量获取文件大小
            inFile.seekg(0, std::ios::beg);//文件指针放回开头
            const auto imageSize = static_cast<int>(std::sqrt(fileSize / num_channels));//获取图片尺寸
            //图片尺寸为整数，使用强制类型转换
           /* auto imageData = new unsigned char[imageSize * imageSize * 3];
            inFile.read(reinterpret_cast<char*>(imageData), imageSize * imageSize * 3);
            auto image = stbi_write_png(destinationFolderPath+ "/" + file.path().stem().string() + ".png", imageSize, imageSize, 3, imageData, 0);
            if (!image) {
                std::cerr << "Failed to write image: " << file.path() << std::endl;
            }*/
            // 分配足够大的内存用于存储图像数据
            std::vector<unsigned char> imageData(imageSize * imageSize * 3);
            // 读取图像数据到内存中
            inFile.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
            // 拼接目标PNG文件路径
            std::string pngFilePath = destinationFolderPath + "/" + file.path().stem().string() + ".png";
            // 将图像数据转换为PNG格式并写入文件
            int result = stbi_write_png(pngFilePath.c_str(), imageSize, imageSize, num_channels, imageData.data(), 0);
            if (result == 0) {
                // 写入失败
                std::cerr << "Failed to write image: " << pngFilePath << std::endl;
            }
            std::cout << "Converted file: " << file.path() << std::endl;
            
        }
    }
}

