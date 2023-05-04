#include<iostream>
#include"stb_image.h"
#include<fstream>
#include <filesystem>
#include"convertPngToBin.h"

bool convertPngToBin(const std::string& pngFilePath, const std::string& binFilePath)
{
    // 使用stb_image库加载PNG文件
    int width, height, numChannels;//宽度，长度，图片
    unsigned char* imageData = stbi_load(pngFilePath.c_str(), &width, &height, &numChannels, 0);
    if (!imageData) {
        std::cerr << "Failed to load image: " << pngFilePath << std::endl; //判断
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



