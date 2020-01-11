#include <opencv2/opencv.hpp> 
#include <string>
#include "../Log/Log.h"

using namespace std;
using namespace cv;

int main()
{
	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"
	Mat frame;
	VideoCapture cap(0);

	cap.set(CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(CAP_PROP_FPS, 30);

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);   //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    while (true)
    {
        
        bool bSuccess = cap.read(frame);

        

        

        cvtColor(frame, frame, COLOR_BGR2GRAY);

        medianBlur(frame, frame, 5);

        std::vector<cv::Vec3f> circles;
        HoughCircles(frame, circles, cv::HOUGH_GRADIENT, 1,
                     20,      // change this value to detect circles with different distances to each other
                     100, 30, // change the last two parameters
                     0, 0     // (min_radius & max_radius) to detect larger circles
        );

        for (size_t i = 0; i < circles.size(); i++)
        {
            cv::Vec3i c = circles[i];
            cv::Point center = cv::Point(c[0], c[1]);
            // circle center
            cv::circle(frame, center, 1, cv::Scalar(0, 100, 100), 3, cv::LINE_AA);
            // circle outline
            int radius = c[2];
            cv::circle(frame, center, radius, cv::Scalar(255, 0, 255), 3, cv::LINE_AA);
        }

        //show the frame in the created window
        imshow(window_name, frame);

        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
}
