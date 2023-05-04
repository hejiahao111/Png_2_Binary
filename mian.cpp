#include <iostream>
#include <fstream>
#include <filesystem>
#include"convertPngToBin.h"
#include"convertPngsToBins.h"
#include "stb_image.h"
// 将PNG文件转换为BIN文件
int main()
{
    std::string sourceFolderPath = "D:/image/";
    std::string destinationFolderPath = "D:/data";
    convertPngsToBins(sourceFolderPath, destinationFolderPath);
    return 0;
}
