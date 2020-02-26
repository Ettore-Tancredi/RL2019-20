#include <opencv2/opencv.hpp>
#include "Camera/Camera.h"

int main()
{
    bool camera_opened = true;
    Camera camera(camera_opened, 30, 400, 400);
    cv::Mat frame;

    cv::namedWindow("test");

    if (!camera_opened)
        std::cout << "Camera unavailable" << std::endl;
    else
    {
        int img_number = 0;
        while (camera_opened)
        {
            try
            {
                camera.fillFrame(frame, ++img_number);
            }
            catch (const char *msg)
            {
                std::cout << msg << std::endl;
                break;
            }
            cv::imshow("test", frame);
        }
    }

    return 0;
}
