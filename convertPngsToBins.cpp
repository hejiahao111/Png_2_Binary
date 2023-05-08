#include<iostream>
#include<fstream>
#include <filesystem>
#include"convertPngToBin.h"
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