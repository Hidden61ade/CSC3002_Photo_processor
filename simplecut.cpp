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
    void set_rectangle(int x1, int y1, int x2, int y2){
        rectangle.x = x1+20;
        rectangle.y = y1+20;
        rectangle.width = (x2-x1-20);
        rectangle.height = (y2-y1-20);
    }

    void set_image(cv::Mat im){
        image = im;

    }
    void crop_and_save() {
            cv::Mat cropped_image = image(rectangle);  // 使用矩形区域裁剪图像
            cv::Mat image = cropped_image;
            cv::namedWindow("cut_image");
            cv::imshow("cut_image",image);
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

//    // 设置矩形区域 (x1, y1, x2, y2)
//    grabchange.set_rectangle(50, 50, 250, 250);  // 这里的坐标需要根据你的需求设置
//    // 裁剪并保存图像
//    grabchange.crop_and_save();
//    cv::waitKey();
//    return 0;
//};
