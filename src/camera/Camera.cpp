#include <iostream>
#include <opencv2/opencv.hpp>


#include "Camera.h"

Camera::Camera(bool &flag)
{
    cap.open(0);
    
    flag = cap.isOpened();
}

Camera::Camera(bool &flag, const double framerate, const double H, const double W)
{
    cap.open(0);
    
    flag = cap.isOpened();

    cap.set(CV_CAP_PROP_FRAME_WIDTH, W);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, H);
    cap.set(CAP_PROP_FPS, framerate);
}

