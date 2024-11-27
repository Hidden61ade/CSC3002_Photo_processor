#ifndef GRABCUT2_H
#define GRABCUT2_H

#include <QMainWindow>

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
class Grabcut2{
private:
    cv::Mat image, Mask, image2;
    cv::Rect rectangle;
    cv::Mat bgModel, fgModel, result;

public:
    void set_rectangle(int x1, int y1, int x2, int y2);

    void set_image(cv::Mat im, cv::Mat im2);

    void runGrabcut();






};
#endif // GRABCUT2_H
