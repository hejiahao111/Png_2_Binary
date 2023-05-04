#include <iostream>
#include <fstream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
namespace fs = std::filesystem;
// ��PNG�ļ�ת��ΪBIN�ļ�
bool convertPngToBin(const std::string& pngFilePath, const std::string& binFilePath)
{
    // ʹ��stb_image�����PNG�ļ�
    int width, height, numChannels;//��ȣ����ȣ�ͼƬ
    unsigned char* imageData = stbi_load(pngFilePath.c_str(), &width, &height, &numChannels, 0);
    if (!imageData) {
        std::cerr << "Failed to load image: " << pngFilePath << std::endl;
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

// ������PNG�ļ�ת��ΪBIN�ļ�
void convertPngsToBins(const std::string& sourceFolderPath, const std::string& destinationFolderPath)
{
    // ȷ��Դ�ļ��к�Ŀ���ļ��ж�����
    if (!std::filesystem::exists(sourceFolderPath)) {
        std::cerr << "Source folder does not exist: " << sourceFolderPath << std::endl;
        return;
    }
    if (!std::filesystem::exists(destinationFolderPath)) {
        std::cerr << "Destination folder does not exist: " << destinationFolderPath << std::endl;
        return;
    }

    // ����Դ�ļ����е�PNG�ļ���ת��ΪBIN�ļ�
    for (auto& file : std::filesystem::directory_iterator(sourceFolderPath)) {
        if (file.path().extension() == ".png") {
            // ����BIN�ļ�·��
            std::filesystem::path binFilePath = std::filesystem::path(destinationFolderPath) /
                (file.path().stem().string() + ".bin");

            // ��PNG�ļ�ת��ΪBIN�ļ�
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
