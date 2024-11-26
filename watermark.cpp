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
    void add_watermark(const string& text, Point position, int fontFace = FONT_HERSHEY_SIMPLEX, double fontScale = 1, Scalar color = Scalar(255, 255, 255), int thickness = 2) {
            // 使用 putText 函数添加水印
        putText(image, text, position, fontFace, fontScale, color, thickness, LINE_AA);
        cv::namedWindow("mirror_image0");
        cv::imshow("mirror_image0",image);
        cout << "Watermark added: " << text << " at position (" << position.x << ", " << position.y << ")" << endl;
        }



};

//int main() {
//    // 创建 Grabcut 对象
//    Grab_simple_change grabchange;
//    // 加载原始图像
//    Mat image = imread("D:/11111.jpg");
//    cv::namedWindow("");
//    cv::imshow("",image);
//    // 检查图像是否加载成功
//    if (image.empty()) {
//        cout << "Failed to load image!" << endl;
//        return -1;
//    }

//    grabchange.set_image(image);
//    string watermark = "Sample Watermark";
//    Point position(100, 100);  // 水印位置
//    grabchange.add_watermark(watermark, position, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2); // 红色水印，粗细为2


//    cv::waitKey();
//    return 0;
//};
