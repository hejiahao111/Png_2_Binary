#define PY_SSIZE_T_CLEAN
#include <iostream>
#include <fstream>
#include <filesystem>
#include"convertPngToBin.h"
#include"convertPngsToBins.h"
#include"convertBinsToPngs.h"

// 将PNG文件转换为BIN文件
int main()
{
     std::string pict_path = "D:/newpict/";
     std::string bin_path = "D:/111/";
     //convertPngsToBins(pict_path,bin_pathh);//png转为二进制
     convertBinsToPngs(bin_path, pict_path);//将二进制转为png
     
     return 0;
}
