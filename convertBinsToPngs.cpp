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
        fs::create_directory(destinationFolderPath);//�鿴�Ƿ���Ŀ���ļ���
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


            inFile.seekg(0, std::ios::end);//���ļ�ָ��ŵ��ļ�β��
            const auto fileSize = inFile.tellg();//ͨ�������ļ�ƫ������ȡ�ļ���С
            inFile.seekg(0, std::ios::beg);//�ļ�ָ��Żؿ�ͷ
            const auto imageSize = static_cast<int>(std::sqrt(fileSize / num_channels));//��ȡͼƬ�ߴ�
            //ͼƬ�ߴ�Ϊ������ʹ��ǿ������ת��
           /* auto imageData = new unsigned char[imageSize * imageSize * 3];
            inFile.read(reinterpret_cast<char*>(imageData), imageSize * imageSize * 3);
            auto image = stbi_write_png(destinationFolderPath+ "/" + file.path().stem().string() + ".png", imageSize, imageSize, 3, imageData, 0);
            if (!image) {
                std::cerr << "Failed to write image: " << file.path() << std::endl;
            }*/
            // �����㹻����ڴ����ڴ洢ͼ������
            std::vector<unsigned char> imageData(imageSize * imageSize * 3);
            // ��ȡͼ�����ݵ��ڴ���
            inFile.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
            // ƴ��Ŀ��PNG�ļ�·��
            std::string pngFilePath = destinationFolderPath + "/" + file.path().stem().string() + ".png";
            // ��ͼ������ת��ΪPNG��ʽ��д���ļ�
            int result = stbi_write_png(pngFilePath.c_str(), imageSize, imageSize, num_channels, imageData.data(), 0);
            if (result == 0) {
                // д��ʧ��
                std::cerr << "Failed to write image: " << pngFilePath << std::endl;
            }
            std::cout << "Converted file: " << file.path() << std::endl;
            
        }
    }
}

