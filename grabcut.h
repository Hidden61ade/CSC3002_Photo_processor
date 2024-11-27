#ifndef GRABCUT_H
#define GRABCUT_H


#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
class Grabcut{
private:
    cv::Mat image, Mask;
    cv::Rect rectangle;
    cv::Mat bgModel, fgModel, result;

public:
    void set_rectangle(int x1, int y1, int x2, int y2);

    void set_image(cv::Mat im);

    void runGrabcut();






};

#endif // GRABCUT_H
