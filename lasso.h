#ifndef LASSO_H
#define LASSO_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

class Lasso {
public:
    Lasso(const std::string& imagePath);
    void start();

private:
    cv::Mat image, originalImage;
    std::vector<cv::Point> points;
    bool isDrawing;

    static Lasso* instance;  // 静态指针用于存储类实例

    static void mouseCallback(int event, int x, int y, int flags, void* userdata);

    void processMouseCallback(int event, int x, int y, int flags, void* userdata);
};

#endif // LASSO_H
//#ifndef LASSO_H
//#define LASSO_H



//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include<vector>

//// 鼠标回调函数
//void mouseCallback(int event, int x, int y, int flags, void* userdata);

//#endif // MAIN_H
