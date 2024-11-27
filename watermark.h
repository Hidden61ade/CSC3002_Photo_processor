#ifndef WATERMARK_H
#define WATERMARK_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include<iostream>
#include<math.h>
#include <string>
#include<fstream>


using namespace cv;
using namespace std;

class Grab_simple_change_watermark{
private:
    cv::Mat image, Mask;
    cv::Rect rectangle;
    cv::Mat bgModel, fgModel, result;
public:


    void set_image(cv::Mat im);

    void add_watermark(const string& text, Point position,
                       int fontFace ,
                       double fontScale ,
                       Scalar color ,
                       int thickness );




};

#endif // WATERMARK_H
