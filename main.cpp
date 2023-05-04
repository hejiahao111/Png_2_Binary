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
      std::string destinationFolderPath = "D:/111/";
     convertPngsToBins(sourceFolderPath,destinationFolderPath);
     //convertBinsToPngs(destinationFolderPath, sourceFolderPath);//将二进制转为png
    return 0;
}
