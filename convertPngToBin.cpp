#include<iostream>
#include"stb_image.h"
#include<fstream>
#include <filesystem>
#include"convertPngToBin.h"

bool convertPngToBin(const std::string& pngFilePath, const std::string& binFilePath)
{
    // ʹ��stb_image�����PNG�ļ�
    int width, height, numChannels;//��ȣ����ȣ�ͼƬ
    unsigned char* imageData = stbi_load(pngFilePath.c_str(), &width, &height, &numChannels, 0);
    if (!imageData) {
        std::cerr << "Failed to load image: " << pngFilePath << std::endl; //�ж�
        return false;
    }

    // ����ͼ�����ݵ��ֽ���
    int imageSize = width * height * numChannels;

    // ��ͼ������д��BIN�ļ�
    std::ofstream outFile(binFilePath, std::ios::out | std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to create binary file: " << binFilePath << std::endl;
        stbi_image_free(imageData); 
        return false;
    }
    outFile.write(reinterpret_cast<char*>(imageData), imageSize);
    outFile.close();
    // �ͷ�ͼ�������ڴ�
    stbi_image_free(imageData);
    return true;
}



