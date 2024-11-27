#ifndef SIMPLECUT_H
#define SIMPLECUT_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include<iostream>
#include<math.h>
#include <string>
#include<fstream>


using namespace cv;
using namespace std;

class Grab_simple_change_cut{
private:
    cv::Mat image, Mask;
    cv::Rect rectangle;
    cv::Mat bgModel, fgModel, result;
public:
    void set_rectangle(int x1, int y1, int x2, int y2);

    void set_image(cv::Mat im);


    void crop_and_save();

};



#endif // SIMPLECUT_H
