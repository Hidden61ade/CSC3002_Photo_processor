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
        //cv::namedWindow("Rectangle");
        //cv::imshow("Rectangle",image);
        cv::namedWindow("Foreground");
        cv::imshow("Foreground",foreground);
}

//int main()
//{
//    cv::Mat src = cv::imread("D:/apple.jpg");
//    Grabcut a;
//    a.set_image(src);
//    a.set_rectangle(30, 30, 500, 500);
//    a.runGrabcut();

//    cv::waitKey();
//    return 0;
//}
