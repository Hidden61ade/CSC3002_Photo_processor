#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include<iostream>
#include<math.h>
#include <string>
#include<fstream>


using namespace cv;
using namespace std;

class Grab_simple_change{
private:
    cv::Mat image, Mask;
    cv::Rect rectangle;
    cv::Mat bgModel, fgModel, result;
public:


    void set_image(cv::Mat im){
        image = im;

    }
    void mirror() {

           flip(image, image, 1);
           cv::namedWindow("mirror_image1");
           cv::imshow("mirror_image1",image);
           cout << "Image mirrored (horizontally)." << endl;
       }

    void mirror_vertical() {

            flip(image, image, 0);
            cv::namedWindow("mirror_image0");
            cv::imshow("mirror_image0",image);
            cout << "Image mirrored vertically (up-down)." << endl;
        }

};

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
//    Grab_simple_change grabchange;
//    grabchange.set_image(image);

//    grabchange.mirror();
//    grabchange.mirror_vertical();
//    cv::waitKey();
//    return 0;
//};
