#include "grabcut2.h"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
#include <string>
#include<fstream>
void Grabcut2::set_image(cv::Mat im, cv::Mat im2){
        image = im;
        image2 = im2;
}

void Grabcut2::set_rectangle(int x1, int y1, int x2, int y2){
        rectangle.x = x1+20;
        rectangle.y = y1+20;
        rectangle.width = (x2-x1-20);
        rectangle.height = (y2-y1-20);
}

void Grabcut2::runGrabcut(){
    cv::namedWindow("Image");
            cv::imshow("Image",image);
            grabCut(image, Mask, rectangle, bgModel, fgModel, 1, cv::GC_INIT_WITH_RECT);
            cv::Mat foreground = cv::Mat::zeros(image.size(), image.type());
            cv::Mat foreground_roi = cv::Mat::zeros(image.size(), CV_8UC3);
            for (int row = 0; row < image.rows; row++)
            {
                for (int col = 0; col < image.cols; col++)
                {
                    if (Mask.at<uchar>(row, col) == 1 || Mask.at<uchar>(row, col) == 3)
                    {
                        foreground_roi.at<cv::Vec3b>(row, col) = cv::Vec3b(255,255,255);
                    }
                }
            }
            bitwise_and(foreground_roi, image, foreground);
            imshow("foreground", foreground);
            cv::Mat background = image2;
                resize(background, background, image.size());
                cv::Mat new_background = background.clone();
                for (int row = 0; row < background.rows; row++)
                {
                    for (int col = 0; col < background.cols; col++)
                    {
                        if (foreground.at<cv::Vec3b>(row, col) != cv::Vec3b(0, 0, 0))
                        {
                            new_background.at<cv::Vec3b>(row, col) = image.at<cv::Vec3b>(row, col);
                        }
                    }
                }
                imshow("new_background", new_background);
        }

//int main()
//{
//    cv::Mat src = cv::imread("D:/apple.jpg");
//    cv::Mat src2 = cv::imread("D:/apple2.jpg");
//    Grabcut a;
//    a.set_image(src, src2);
//    a.set_rectangle(30, 30, 500, 500);

//    a.runGrabcut();

//    cv::waitKey();
//    return 0;
//}
