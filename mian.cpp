#include <iostream>
#include <fstream>
#include <filesystem>
#include"convertPngToBin.h"
#include"convertPngsToBins.h"
#include "stb_image.h"
// ��PNG�ļ�ת��ΪBIN�ļ�
int main()
{
    std::string sourceFolderPath = "D:/image/";
    std::string destinationFolderPath = "D:/data";
    convertPngsToBins(sourceFolderPath, destinationFolderPath);
    return 0;
}
