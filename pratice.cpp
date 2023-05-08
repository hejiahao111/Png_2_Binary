#include<iostream>
#include<filesystem>
#include<fstream>
#include<vector>
#include"stb_image_write.h"
namespace fs = std::filesystem;
void pratice(const std::string &in_path,const std::string &out_path) {
	if (!fs::exists()) {
		std::cout << "ͼƬ�ļ���·�������ڣ�����һ��" << std::endl;
		return;
	}
	if (!fs::exists()){
		std::cout<<"����ļ��в�����"<< std::endl;
        fs::create_directory(out_path);
		return;
	}
	for (const auto &file : fs::directory_iterator(in_path)) {
		if (file.is_regular_file() && file.path().extension() == ".bin") {//�ж��ļ��ǲ��������ļ��Լ��ļ���չ���Բ��ԣ���һ��ɸѡ
			std::ifstream inFile(file.path(), std::ios::binary);//�Զ����ƴ��ļ�
			if (!inFile) {
				std::cerr << "Failed to open file: " << file.path() << std::endl;
				continue;
			}
			inFile.seekg(0, std::ios::ate);//���ļ�ָ���Ƶ����һλ
			const auto& file_size = inFile.tellg();//��ȡƫ����Ȼ��õ��ļ���С
			inFile.seekg(0, std::ios::beg);//�����ļ�ָ���ƶ����ļ��Ŀ�ͷ�����ļ���ͷ��ȡ�ļ����ݡ�
			const auto &image_size= static_cast<int>(std::sqrt(file_size / 3));//ͼƬ�ߴ�

			std::vector<unsigned char>image_data(image_size * image_size * 3);
			inFile.read(reinterpret_cast<char*>(image_data.data()), image_data.size());
            //��ʾ��ָ���޷����ַ���ָ��ǿ��ת��Ϊָ���ַ���ָ�룬�Ա���inFile.read()����������ȷ�Ĳ������͡�
			std::string png_path = out_path + "/" + file.path().stem().string() + ".png";
			int result = stbi_write_png(png_path.c_str(),image_size,image_size,3, image_data.data(), 0);
			if (result == 0) {
				std::cerr << "pngд��ʧ��" << std::endl;
				return;
			}
			std::cout << "pngд��ɹ�" << std::endl;
			
		}
	}
}