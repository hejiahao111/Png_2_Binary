#define PY_SSIZE_T_CLEAN
#include <iostream>
#include <fstream>
#include <filesystem>
#include"convertPngToBin.h"
#include"convertPngsToBins.h"
#include"convertBinsToPngs.h"

// ��PNG�ļ�ת��ΪBIN�ļ�
int main()
{
     std::string pict_path = "D:/newpict/";
     std::string bin_path = "D:/111/";
     //convertPngsToBins(pict_path,bin_pathh);//pngתΪ������
     convertBinsToPngs(bin_path, pict_path);//��������תΪpng
     
     return 0;
}
