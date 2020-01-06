#include <iostream>
#include <opencv2/opencv.hpp>
#include "Parameters.h"


#ifndef CAMERA_H
#define CAMERA_H


class Camera 
{
    private:
        cv::VideoCapture cap;
    public:
        Camera(bool &); //flag
        Camera(bool &, double, double, double); //flag, framerate, H, W
        void fillFrame(cv::Mat &, int );
};




#endif
