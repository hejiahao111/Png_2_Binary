#include <iostream>
#include <fstream>
#include <filesystem>
#include"convertPngToBin.h"
#include"convertPngsToBins.h"
#include "stb_image.h"
#include"convertBinsToPngs.h"
// 将PNG文件转换为BIN文件
int main()
{
     std::string sourceFolderPath = "D:/image/";
     std::string destinationFolderPath = "D:/data/";
    convertPngsToBins(sourceFolderPath,destinationFolderPath);


    const std::string sourceFolderPath = "path/to/source/folder";
    const std::string destinationFolderPath = "path/to/destination/folder";

    convertBinsToPngs(sourceFolderPath, destinationFolderPath);

    return 0;
    return 0;
}
