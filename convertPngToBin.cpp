
#include<iostream>
#include<fstream>
#include <filesystem>
#include"convertPngToBin.h"
#include"stb_image.h"

bool convertPngToBin(const std::string& pngFilePath, const std::string& binFilePath)
{
    // 使用stb_image库加载PNG文件
    int width, height, numChannels;//宽度，长度，图片
    unsigned char* imageData = stbi_load(pngFilePath.c_str(), &width, &height, &numChannels, 0);//加载图像文件到内存中，并返回图像的像素数据、宽、高和通道数等信息；
    if (!imageData) { //c_str()将const string转换为const char*
        std::cerr << "Failed to load image: " << pngFilePath << std::endl; //判断
        return false;
    }

    // 计算图像数据的字节数
    int imageSize = width * height * numChannels;

    // 将图像数据写入BIN文件
    std::ofstream outFile(binFilePath, std::ios::out | std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to create binary file: " << binFilePath << std::endl;
        stbi_image_free(imageData); //释放通过 stbi_load 加载的图像数据内存
        return false;
    }
    outFile.write(reinterpret_cast<char*>(imageData), imageSize);
    outFile.close();
    // 释放图像数据内存
    stbi_image_free(imageData);
    return true;
}



