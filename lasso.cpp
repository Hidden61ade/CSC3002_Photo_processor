#include "lasso.h"

Lasso* Lasso::instance = nullptr;

Lasso::Lasso() : isDrawing(false) {
    // 默认构造函数
}

void Lasso::set_image(const std::string& imagePath) {
    image = cv::imread(imagePath);
    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        exit(-1);
    }
    originalImage = image.clone();
}

void Lasso::mouseCallback(int event, int x, int y, int flags, void* userdata) {
    if (instance) {
        instance->processMouseCallback(event, x, y, flags, userdata);
    }
}

void Lasso::processMouseCallback(int event, int x, int y, int flags, void* userdata) {
    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            points.clear(); // 清空点集
            points.push_back(cv::Point(x, y));
            isDrawing = true;
            break;
        case cv::EVENT_MOUSEMOVE:
            if (isDrawing) {
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
                cv::Mat mask = cv::Mat::zeros(originalImage.size(), CV_8UC1);
                cv::drawContours(mask, std::vector<std::vector<cv::Point>>{points}, -1, cv::Scalar(255), cv::FILLED);
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

void Lasso::start() {
    instance = this;  // 设置静态指针为当前实例
    cv::namedWindow("Image", 1);
    cv::setMouseCallback("Image", Lasso::mouseCallback, nullptr);
    cv::imshow("Image", originalImage);
    cv::waitKey(0);
}
//#include "lasso.h"

//Lasso* Lasso::instance = nullptr;

//Lasso::Lasso(const std::string& imagePath) {
//    image = cv::imread(imagePath);
//    if (image.empty()) {
//        std::cout << "Could not open or find the image!" << std::endl;
//        exit(-1);
//    }
//    originalImage = image.clone();
//    isDrawing = false;
//}

//void Lasso::mouseCallback(int event, int x, int y, int flags, void* userdata) {
//    if (instance) {
//        instance->processMouseCallback(event, x, y, flags, userdata);
//    }
//}

//void Lasso::processMouseCallback(int event, int x, int y, int flags, void* userdata) {
//    switch (event) {
//        case cv::EVENT_LBUTTONDOWN:
//            points.clear(); // 清空点集
//            points.push_back(cv::Point(x, y));
//            isDrawing = true;
//            break;
//        case cv::EVENT_MOUSEMOVE:
//            if (isDrawing) {
//                cv::line(originalImage, points.back(), cv::Point(x, y), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
//                points.push_back(cv::Point(x, y));
//                cv::imshow("Image", originalImage);
//            }
//            break;
//        case cv::EVENT_LBUTTONUP:
//            if (isDrawing) {
//                // 自动首尾连接
//                cv::line(originalImage, points.back(), points.front(), cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
//                points.push_back(points.front()); // 确保路径闭合
//                cv::Mat mask = cv::Mat::zeros(originalImage.size(), CV_8UC1);
//                cv::drawContours(mask, std::vector<std::vector<cv::Point>>{points}, -1, cv::Scalar(255), cv::FILLED);
//                cv::Mat result;
//                cv::bitwise_and(image, image, result, mask);

//                // 创建新窗口显示截取的部分
//                cv::imshow("Cropped", result);
//                cv::imwrite("cropped_image.jpg", result);

//                // 重置用于显示的图像和点集以绘制新的轮廓
//                originalImage = image.clone();
//                points.clear();
//                isDrawing = false;
//            }
//            break;
//    }
//}

//void Lasso::start() {
//    instance = this;  // 设置静态指针为当前实例
//    cv::namedWindow("Image", 1);
//    cv::setMouseCallback("Image", Lasso::mouseCallback, nullptr);
//    cv::imshow("Image", originalImage);
//    cv::waitKey(0);
//}

