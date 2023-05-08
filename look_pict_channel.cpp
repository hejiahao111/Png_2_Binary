#include<iostream>
#include<string>
#include<filesystem>
#include<opencv2/opencv.hpp>
#include<fstream>
namespace fs = std::filesystem;
int look_pict_channel(const std::string &pict_name) {
    // 读取图像
            cv::Mat img = cv::imread(pict_name, cv::COLOR);
            if (img.empty()) {
                std::cerr << "Failed to read image" << std::endl;
                return -1;
            }
   //cv::Mat是OpenCV中一个非常常用的类，用于表示一个矩阵或者多维数组。
   // 在图像处理中，我们通常会使用cv::Mat来读取、存储和处理图像。
   // cv::Mat可以存储不同类型的数据，比如8位无符号整数、32位浮点数等。
   // 在OpenCV中，对图像的操作通常都是基于cv::Mat进行的。
   // 例如，我们可以使用cv::imread函数读取一张图像文件，将其存储为cv::Mat类型，
   // 然后进行各种处理，最终再使用cv::imwrite函数将处理结果保存为一张图像文件。
            // 获取通道数
            int num_channels = img.channels();
            std::cout << "图片通道数是：" << num_channels << std::endl;
            return num_channels;
        }
    } 
}