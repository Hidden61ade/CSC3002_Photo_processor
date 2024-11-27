#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include"simplerotate.h"
#include<iostream>
#include<math.h>
#include <string>
#include<fstream>






void Grab_simple_change_rotate ::set_image(cv::Mat im){
        image = im;

}


void Grab_simple_change_rotate :: rotate(){
            // 获取图像的中心点
            Point center(image.cols / 2, image.rows / 2);

            // 生成旋转矩阵：旋转 90 度，中心旋转
            Mat rotMat = getRotationMatrix2D(center, 90, 1.0);

            // 执行旋转操作，使用 warpAffine
            warpAffine(image, image, rotMat, image.size(), INTER_LINEAR, BORDER_CONSTANT);
            cv::namedWindow("rotate_image");
            cv::imshow("rotate_image",image);
}


//int main() {
//    // 加载原始图像
//    Mat image = imread("D:/11111.jpg");
//    cv::namedWindow("");
//    cv::imshow("",image);
//    // 检查图像是否加载成功
//    if (image.empty()) {
//        cout << "Failed to load image!" << endl;
//        return -1;
//    }

//    // 创建 Grabcut 对象
//    class Grab_simple_change_rotate grabchange;
//    grabchange.set_image(image);


//    // 旋转图像
//    grabchange.rotate();
//    cv::waitKey();//敲一下键盘退出
//    grabchange.rotate();
//    cv::waitKey();//敲一下键盘退出
//    grabchange.rotate();
//    cv::waitKey();//敲一下键盘退出
//    return 0;
//};
