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

void Camera::fillFrame(cv::Mat &frame, int img_number)
{
        bool b = cap.read(frame);
        if (!b)
             throw "Unable to take photo";
        else
            cv::imwrite(std::to_string(img_number) + ".png", frame );
}
