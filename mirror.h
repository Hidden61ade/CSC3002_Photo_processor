#ifndef MIRROR_H
#define MIRROR_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include<iostream>
#include<math.h>
#include <string>
#include<fstream>




class Grab_simple_change_mirror{
private:
    cv::Mat image, Mask;
    cv::Rect rectangle;
    cv::Mat bgModel, fgModel, result;
public:


    void set_image(cv::Mat im);

    void mirror() ;

    void mirror_vertical() ;

};



#endif // MIRROR_H
