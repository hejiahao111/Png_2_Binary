#include<iostream>
#include<string>
#include<filesystem>
#include<opencv2/opencv.hpp>
#include<fstream>
namespace fs = std::filesystem;
int look_pict_channel(const std::string &pict_name) {
    // ��ȡͼ��
            cv::Mat img = cv::imread(pict_name, cv::COLOR);
            if (img.empty()) {
                std::cerr << "Failed to read image" << std::endl;
                return -1;
            }
   //cv::Mat��OpenCV��һ���ǳ����õ��࣬���ڱ�ʾһ��������߶�ά���顣
   // ��ͼ�����У�����ͨ����ʹ��cv::Mat����ȡ���洢�ʹ���ͼ��
   // cv::Mat���Դ洢��ͬ���͵����ݣ�����8λ�޷���������32λ�������ȡ�
   // ��OpenCV�У���ͼ��Ĳ���ͨ�����ǻ���cv::Mat���еġ�
   // ���磬���ǿ���ʹ��cv::imread������ȡһ��ͼ���ļ�������洢Ϊcv::Mat���ͣ�
   // Ȼ����и��ִ���������ʹ��cv::imwrite����������������Ϊһ��ͼ���ļ���
            // ��ȡͨ����
            int num_channels = img.channels();
            std::cout << "ͼƬͨ�����ǣ�" << num_channels << std::endl;
            return num_channels;
        }
    } 
}