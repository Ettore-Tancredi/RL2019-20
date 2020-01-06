#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Read the image file
    string path = "/home/luigi/source/repos/rl_2019-20/src/testing/open_img/";
    Mat image = imread(path + "28.png");
    // Check for failure
    if (image.empty()) 
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }

    string windowName = "finestra"; //Name of the window

    namedWindow(windowName); // Create a window

    int i = 28;
    while ( waitKey(0) != int('0'))
    {
        image =  imread(path + to_string(i) + ".png");
        imshow(windowName, image);
        ++i;
    }
    

    // Wait for any keystroke in the window

    imshow(windowName, image);


    destroyWindow(windowName); //destroy the created window

    return 0;
}