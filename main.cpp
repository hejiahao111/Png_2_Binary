#include <iostream>
#include <fstream>
#include <filesystem>
#include"convertPngToBin.h"
#include"convertPngsToBins.h"
#include "stb_image.h"
#include"convertBinsToPngs.h"
// ��PNG�ļ�ת��ΪBIN�ļ�
int main()
{
      std::string sourceFolderPath = "D:/image/";
      std::string destinationFolderPath = "D:/111/";
     convertPngsToBins(sourceFolderPath,destinationFolderPath);
     //convertBinsToPngs(destinationFolderPath, sourceFolderPath);//��������תΪpng
    return 0;
}
