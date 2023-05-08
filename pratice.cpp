#include<iostream>
#include<filesystem>
#include<fstream>
#include<vector>
#include"stb_image_write.h"
namespace fs = std::filesystem;
void pratice(const std::string &in_path,const std::string &out_path) {
	if (!fs::exists()) {
		std::cout << "图片文件夹路径不存在，请检查一下" << std::endl;
		return;
	}
	if (!fs::exists()){
		std::cout<<"输出文件夹不存在"<< std::endl;
        fs::create_directory(out_path);
		return;
	}
	for (const auto &file : fs::directory_iterator(in_path)) {
		if (file.is_regular_file() && file.path().extension() == ".bin") {//判断文件是不是正常文件以及文件扩展名对不对，做一个筛选
			std::ifstream inFile(file.path(), std::ios::binary);//以二进制打开文件
			if (!inFile) {
				std::cerr << "Failed to open file: " << file.path() << std::endl;
				continue;
			}
			inFile.seekg(0, std::ios::ate);//将文件指针移到最后一位
			const auto& file_size = inFile.tellg();//获取偏移量然后得到文件大小
			inFile.seekg(0, std::ios::beg);//将将文件指针移动到文件的开头，从文件开头读取文件内容。
			const auto &image_size= static_cast<int>(std::sqrt(file_size / 3));//图片尺寸

			std::vector<unsigned char>image_data(image_size * image_size * 3);
			inFile.read(reinterpret_cast<char*>(image_data.data()), image_data.size());
            //表示将指向无符号字符的指针强制转换为指向字符的指针，以便向inFile.read()函数传递正确的参数类型。
			std::string png_path = out_path + "/" + file.path().stem().string() + ".png";
			int result = stbi_write_png(png_path.c_str(),image_size,image_size,3, image_data.data(), 0);
			if (result == 0) {
				std::cerr << "png写入失败" << std::endl;
				return;
			}
			std::cout << "png写入成功" << std::endl;
			
		}
	}
}