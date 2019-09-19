#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

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

    cap.set(cv::CAP_PROP_FRAME_WIDTH, W);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, H);
    cap.set(cv::CAP_PROP_FPS, framerate);
}


void Camera::fillFrame(cv::Mat &frame, int temp)
{
   // bool b = cap.read(frame);
   bool b = true;
   frame = cv::imread("/home/luigi/source/repos/rl_2019-20/runs/3-3-12_56/" + std::to_string(temp) + ".png", cv::IMREAD_COLOR);  
    if (!b)
        std::cout << "CAZZO" << std::endl;


    bool isSuccess = cv::imwrite("MyImage.jpg", frame);
}

