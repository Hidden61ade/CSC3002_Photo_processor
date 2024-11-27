#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include"mirror.h"
#include<iostream>
#include<math.h>
#include <string>
#include<fstream>


using namespace cv;
using namespace std;



void Grab_simple_change_mirror:: set_image(cv::Mat im){
        image = im;

    }
void Grab_simple_change_mirror:: mirror() {

           flip(image, image, 1);
           cv::namedWindow("mirror_image1");
           cv::imshow("mirror_image1",image);
           cout << "Image mirrored (horizontally)." << endl;
       }

void Grab_simple_change_mirror:: mirror_vertical() {

            flip(image, image, 0);
            cv::namedWindow("mirror_image0");
            cv::imshow("mirror_image0",image);
            cout << "Image mirrored vertically (up-down)." << endl;
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
//    class Grab_simple_change_mirror grabchange;
//    grabchange.set_image(image);

//    grabchange.mirror();
//    grabchange.mirror_vertical();
//    cv::waitKey();//敲一下键盘退出
//    return 0;
//};
