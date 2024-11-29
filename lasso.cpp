#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;


cv::Mat image, originalImage; // 原始图像和用于显示的图像
std::vector<cv::Point> points;

bool isDrawing = false;

// 鼠标回调函数
void mouseCallback(int event, int x, int y, int flags, void* userdata) {
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            points.clear(); // 清空点集
            points.push_back(cv::Point(x, y));
            isDrawing = true;
            break;
        case cv::EVENT_MOUSEMOVE:
            if (isDrawing) {
                // 在用于显示的图像上绘制红线
                cv::line(originalImage, points.back(), cv::Point(x, y), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
                points.push_back(cv::Point(x, y));
                cv::imshow("Image", originalImage);
            }
            break;
        case cv::EVENT_LBUTTONUP:
            if (isDrawing) {
                // 自动首尾连接
                cv::line(originalImage, points.back(), points.front(), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
                points.push_back(points.front()); // 确保路径闭合

                // 创建掩模并绘制轮廓
                cv::Mat mask = cv::Mat::zeros(originalImage.size(), CV_8UC1);
                cv::drawContours(mask, std::vector<std::vector<cv::Point>>{points}, -1, cv::Scalar(255), cv::FILLED);

                // 使用掩模提取轮廓内的图像
                cv::Mat result;
                cv::bitwise_and(image, image, result, mask);

                // 创建新窗口显示截取的部分
                cv::imshow("Cropped", result);
                cv::imwrite("cropped_image.jpg", result);

                // 重置用于显示的图像和点集以绘制新的轮廓
                originalImage = image.clone();
                points.clear();
                isDrawing = false;
            }
            break;
    }
}

//int main() {
//    image = cv::imread("D:/11111.jpg"); // 用户可以替换为你的图片路径
//    if (image.empty()) {
//        std::cout << "Could not open or find the image!" << std::endl;
//        return -1;
//    }

//    // 复制图像以用于显示
//    originalImage = image.clone();

//    // 创建窗口
//    cv::namedWindow("Image", 1);
//    cv::setMouseCallback("Image", mouseCallback);
//    cv::imshow("Image", originalImage);
//    cv::waitKey(0);

//    return 0;
//}
