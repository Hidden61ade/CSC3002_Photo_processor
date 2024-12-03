#include "grabcut.h"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include<iostream>
#include<math.h>
#include <string>
#include<fstream>
void Grabcut::set_image(cv::Mat im){
        image = im;
}

void Grabcut::set_rectangle(int x1, int y1, int x2, int y2){
        rectangle.x = x1+20;
        rectangle.y = y1+20;
        rectangle.width = (x2-x1-20);
        rectangle.height = (y2-y1-20);
}

void Grabcut::runGrabcut(){
        cv::namedWindow("Image");
        cv::imshow("Image",image);
        grabCut(image, Mask, rectangle, bgModel, fgModel, 1, cv::GC_INIT_WITH_RECT);
        cv::compare(Mask,cv::GC_PR_FGD,Mask,cv::CMP_EQ);
        cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
        image.copyTo(foreground,Mask);
        cv::rectangle(image, rectangle, cv::Scalar(200,0,200),4);
        cv::namedWindow("Rectangle");
        cv::imshow("Rectangle",image);
        cv::namedWindow("Foreground");
        cv::imshow("Foreground",foreground);
}
QImage *Grabcut::GetImage() {
    // 确保 this->image 是一个有效的 cv::Mat 图像
    if (this->image.empty()) {
        return new QImage(); // 如果 image 为空，则返回一个空的 QImage
    }

    // 获取 cv::Mat 的宽度、高度和通道数
    int width = this->image.cols;
    int height = this->image.rows;
    int channels = this->image.channels();

    // 如果图像是灰度图（单通道），则需要转换成 3 通道的 RGB 格式
    if (channels == 1) {
        cv::Mat rgbImage;
        cv::cvtColor(this->image, rgbImage, cv::COLOR_GRAY2RGB);
        // 返回转换后的 QImage
        return new QImage(rgbImage.data, width, height, rgbImage.step, QImage::Format_RGB888);
    }

    // 如果图像已经是彩色的（3 通道），直接返回 QImage
    if (channels == 3) {
        // 由于 OpenCV 使用 BGR 格式，需要转换为 RGB
        cv::Mat rgbImage;
        cv::cvtColor(this->image, rgbImage, cv::COLOR_BGR2RGB);
        return new QImage(rgbImage.data, width, height, rgbImage.step, QImage::Format_RGB888);
    }

    // 如果图像是 4 通道（RGBA），直接返回 QImage
    if (channels == 4) {
        return new QImage(this->image.data, width, height, this->image.step, QImage::Format_RGBA8888);
    }

    // 如果是其他类型的图像，可以考虑处理或返回一个空的 QImage
    return new QImage();
}
//int main()
//{
//    cv::Mat src = cv::imread(R"(D:/a.jpg)");
//    Grabcut a;
//    a.set_image(src);
//    a.set_rectangle(30, 30, 500, 500);
//    a.runGrabcut();
//    std::cout << "1" << std::endl;
//    cv::waitKey();
//    return 0;
//}
